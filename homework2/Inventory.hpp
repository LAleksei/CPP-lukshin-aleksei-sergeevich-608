#pragma once

#include <ostream>
#include <string>

class Spec {
 public:
  explicit Spec(const std::string& n) : name_(n) {}

  const std::string& Name() const { return name_; }

 private:
  std::string name_;
};

class Item {
 public:
  virtual ~Item() = default;

  virtual const std::string& Id() const = 0;
  virtual const std::string& Name() const = 0;
  virtual std::string Info() const = 0;

  virtual bool Novice() const { return false; }
  virtual void SetName(const std::string& name) = 0;

  bool operator<(const Item& other) const {
    return Id() < other.Id();
  }

  bool operator==(const Item& other) const {
    return Id() == other.Id();
  }
};

class Powered {
 public:
  virtual ~Powered() = default;
  virtual double Energy() const = 0;
};

inline std::ostream& operator<<(std::ostream& os, const Item& it) {
  return os << it.Id() << ' ' << it.Name();
}
