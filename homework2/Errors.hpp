#pragma once

#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
 public:
  explicit FleetError(const std::string& msg) : std::runtime_error(msg) {}
};

class InspectionRejected : public FleetError {
 public:
  InspectionRejected() : FleetError("inspection rejected") {}
};

class BadArg : public FleetError {
 public:
  explicit BadArg(const std::string& msg)
      : FleetError("invalid argument: " + msg) {}
};

class NotFound : public FleetError {
 public:
  explicit NotFound(const std::string& id)
      : FleetError("not found: " + id) {}
};
