#pragma once

#include <cctype>
#include <string>

#include "Errors.hpp"

class ServiceCenter {
 public:
  void Check(const std::string& name) const {
    std::string s = name;
    for (char& c : s) {
      c = static_cast<char>(
          std::tolower(static_cast<unsigned char>(c)));
    }

    if (s.find("broken") != std::string::npos) {
      throw InspectionRejected();
    }
  }
};
