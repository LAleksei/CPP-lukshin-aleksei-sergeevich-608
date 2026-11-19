#pragma once

#include <algorithm>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include "Transport.hpp"

class Park {
 public:
  void AddTransport(std::unique_ptr<Transport> t) {
    service_.Check(t->Name());

    if (HasItem(*t)) {
      throw BadArg("same id: " + t->Id());
    }

    t->SetSpec(GetSpec(t->Name()));
    items_.push_back(std::move(t));
  }

  void AddItem(std::unique_ptr<Item> p) {
    if (HasItem(*p)) {
      throw BadArg("same id: " + p->Id());
    }
    items_.push_back(std::move(p));
  }

  int Size() const { return static_cast<int>(items_.size()); }

  double Energy() const { return TotalEnergy(items_); }

  void List(std::ostream& os) const {
    auto v = items_;
    std::sort(v.begin(), v.end(),
              [](const auto& a, const auto& b) { return *a < *b; });

    for (auto& p : v) os << *p << '\n';
  }

  void Novice(std::ostream& os) const {
    for (auto& p : items_) {
      if (p->Novice()) os << *p << '\n';
    }
  }

  void Focus(const std::string& id) {
    if (id.empty()) throw BadArg("empty id");
    for (auto& p : items_) {
      if (p->Id() == id) {
        focus_ = p;
        return;
      }
    }
    throw NotFound(id);
  }

  void ShowFocus(std::ostream& os) const {
    if (auto p = focus_.lock()) {
      os << *p << '\n';
    } else {
      os << "removed\n";
    }
  }

  void Remove(const std::string& id) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
      if ((*it)->Id() == id) {
        items_.erase(it);
        return;
      }
    }
    throw NotFound(id);
  }

  void PrintSpecs(std::ostream& os) const { os << specs_; }

  void Info(const std::string& id, std::ostream& os) const {
    for (auto& p : items_) {
      if (p->Id() == id) {
        os << p->Info() << '\n';
        return;
      }
    }
    throw NotFound(id);
  }

  void Rename(const std::string& id, const std::string& new_name) {
    for (auto& p : items_) {
      if (p->Id() == id) {
        p->SetName(new_name);
        return;
      }
    }
    throw NotFound(id);
  }

  double AvgEnergy() const {
    double sum = 0.0;
    int cnt = 0;
    for (auto& p : items_) {
      if (auto e = dynamic_cast<const Powered*>(p.get())) {
        sum += e->Energy();
        ++cnt;
      }
    }
    return cnt == 0 ? 0.0 : sum / static_cast<double>(cnt);
  }

 private:
  bool HasItem(const Item& item) const {
    for (auto& p : items_) {
      if (*p == item) return true;
    }
    return false;
  }

  std::shared_ptr<Spec> GetSpec(const std::string& name) {
    for (int i = 0; i < specs_.Size(); ++i) {
      if (specs_[i]->Name() == name) return specs_[i];
    }

    auto s = std::make_shared<Spec>(name);
    specs_.Add(s);
    return s;
  }

  std::vector<std::shared_ptr<Item>> items_;
  Reg<std::shared_ptr<Spec>, 100> specs_;
  std::weak_ptr<Item> focus_;
  ServiceCenter service_;
};
