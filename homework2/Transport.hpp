#pragma once

#include <memory>
#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"

class Transport : public Item {
 public:
  Transport(const std::string& id, const std::string& name, int simp)
      : id_(id), name_(name), simp_(simp) {
    if (id_.empty()) throw BadArg("empty id");
    if (simp_ < 1 || simp_ > 10) {
      throw BadArg("simplicity must be 1..10");
    }
  }

  const std::string& Id() const override { return id_; }
  const std::string& Name() const override { return name_; }

  int Simplicity() const { return simp_; }
  bool Novice() const override { return simp_ >= 6; }

  void SetSpec(const std::shared_ptr<Spec>& s) { spec_ = s; }
  void SetName(const std::string& name) override { name_ = name; }

 protected:
  std::string SpecInfo() const {
    if (!spec_) return {};
    return " model: " + spec_->Name();
  }

 private:
  std::string id_;
  std::string name_;
  int simp_;
  std::shared_ptr<Spec> spec_;
};

class Bike : public Transport {
 public:
  Bike(const std::string& id, const std::string& name, int simp)
      : Transport(id, name, simp) {}

  std::string Info() const override {
    return "bike " + Id() + " (" + Name() + ")" + SpecInfo();
  }
};

class EBike : public Transport, public Powered {
 public:
  EBike(const std::string& id, const std::string& name,
        double e, int simp)
      : Transport(id, name, simp), energy_(e) {
    if (energy_ < 0) throw BadArg("energy is below 0");
  }

  double Energy() const override { return energy_; }

  std::string Info() const override {
    return "e-bike " + Id() + " (" + Name() + ")" + SpecInfo();
  }

 private:
  double energy_;
};

class Scooter : public Transport, public Powered {
 public:
  Scooter(const std::string& id, const std::string& name,
          double e, int simp)
      : Transport(id, name, simp), energy_(e) {
    if (energy_ < 0) throw BadArg("energy is below 0");
  }

  double Energy() const override { return energy_; }

  std::string Info() const override {
    return "scooter " + Id() + " (" + Name() + ")" + SpecInfo();
  }

 private:
  double energy_;
};
