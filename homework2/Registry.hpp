#pragma once

#include <memory>
#include <ostream>
#include <vector>

#include "Errors.hpp"
#include "Inventory.hpp"

template <class T, int Cap>
class Reg {
 public:
  int Size() const { return static_cast<int>(items_.size()); }

  void Add(const T& x) {
    if (Size() >= Cap) throw BadArg("registry is full");
    items_.push_back(x);
  }

  const T& operator[](int i) const { return items_[i]; }
  T& operator[](int i) { return items_[i]; }

  void Print(std::ostream& os) const {
    for (const auto& x : items_) os << x << '\n';
  }

 private:
  std::vector<T> items_;
};

template <int Cap>
class Reg<std::shared_ptr<Spec>, Cap> {
 public:
  int Size() const { return static_cast<int>(items_.size()); }

  void Add(const std::shared_ptr<Spec>& x) {
    if (Size() >= Cap) throw BadArg("registry is full");
    items_.push_back(x);
  }

  const std::shared_ptr<Spec>& operator[](int i) const {
    return items_[i];
  }

  std::shared_ptr<Spec>& operator[](int i) {
    return items_[i];
  }

  void Print(std::ostream& os) const {
    for (const auto& s : items_) os << s->Name() << '\n';
  }

 private:
  std::vector<std::shared_ptr<Spec>> items_;
};

template <class T, int Cap>
std::ostream& operator<<(std::ostream& os, const Reg<T, Cap>& r) {
  r.Print(os);
  return os;
}

template <class C>
double TotalEnergy(const C& items) {
  double sum = 0.0;
  for (const auto& p : items) {
    if (auto e = dynamic_cast<const Powered*>(p.get())) {
      sum += e->Energy();
    }
  }
  return sum;
}
