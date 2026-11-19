#pragma once

#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"

class Helmet : public Item {
 public:
  Helmet(const std::string& id, const std::string& name)
      : id_(id), name_(name) {
    if (id_.empty()) throw BadArg("empty id");
  }

  const std::string& Id() const override { return id_; }
  const std::string& Name() const override { return name_; }
  void SetName(const std::string& name) override { name_ = name; }

  std::string Info() const override {
    return "helmet " + id_ + " (" + name_ + ")";
  }

 private:
  std::string id_;
  std::string name_;
};

class Dock : public Item, public Powered {
 public:
  Dock(const std::string& id, const std::string& name, double e)
      : id_(id), name_(name), energy_(e) {
    if (id_.empty()) throw BadArg("empty id");
    if (energy_ < 0) throw BadArg("energy is below 0");
  }

  const std::string& Id() const override { return id_; }
  const std::string& Name() const override { return name_; }
  void SetName(const std::string& name) override { name_ = name; }

  double Energy() const override { return energy_; }

  std::string Info() const override {
    return "dock station " + id_ + " (" + name_ + ")";
  }

 private:
  std::string id_;
  std::string name_;
  double energy_;
};
