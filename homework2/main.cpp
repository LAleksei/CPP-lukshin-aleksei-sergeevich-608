#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.hpp"
#include "Park.hpp"
#include "Things.hpp"
#include "Transport.hpp"

void DoAdd(std::istringstream& input, Park& p) {
  std::string kind;
  input >> kind;

  if (kind == "scooter") {
    std::string id, name;
    double e;
    int s;
    if (!(input >> id >> name >> e >> s)) {
      throw BadArg("bad scooter arguments");
    }
    p.AddTransport(std::make_unique<Scooter>(id, name, e, s));
  } else if (kind == "ebike" || kind == "e-bike") {
    std::string id, name;
    double e;
    int s;
    if (!(input >> id >> name >> e >> s)) {
      throw BadArg("bad e-bike arguments");
    }
    p.AddTransport(std::make_unique<EBike>(id, name, e, s));
  } else if (kind == "bike") {
    std::string id, name;
    int s;
    if (!(input >> id >> name >> s)) {
      throw BadArg("bad bike arguments");
    }
    p.AddTransport(std::make_unique<Bike>(id, name, s));
  } else if (kind == "helmet") {
    std::string id, name;
    if (!(input >> id >> name)) {
      throw BadArg("bad helmet arguments");
    }
    p.AddItem(std::make_unique<Helmet>(id, name));
  } else if (kind == "dock") {
    std::string id, name;
    double e;
    if (!(input >> id >> name >> e)) {
      throw BadArg("bad dock arguments");
    }
    p.AddItem(std::make_unique<Dock>(id, name, e));
  } else {
    throw BadArg("unknown type: " + kind);
  }
}

int main() {
  Park p;
  std::string line;

  while (std::getline(std::cin, line)) {
    std::istringstream in(line);
    std::string cmd;
    if (!(in >> cmd)) continue;

    try {
      if (cmd == "quit") {
        break;
      } else if (cmd == "add") {
        DoAdd(in, p);
      } else if (cmd == "energy") {
        std::cout << std::fixed << std::setprecision(1)
                  << p.Energy() << '\n';
      } else if (cmd == "novice") {
        p.Novice(std::cout);
      } else if (cmd == "list") {
        p.List(std::cout);
      } else if (cmd == "specs") {
        p.PrintSpecs(std::cout);
      } else if (cmd == "focus") {
        std::string id;
        if (!(in >> id)) throw BadArg("focus needs id");
        p.Focus(id);
      } else if (cmd == "show_focus") {
        p.ShowFocus(std::cout);
      } else if (cmd == "remove") {
        std::string id;
        if (!(in >> id)) throw BadArg("remove needs id");
        p.Remove(id);
      } else if (cmd == "info") {
        std::string id;
        if (!(in >> id)) throw BadArg("info needs id");
        p.Info(id, std::cout);
      } else if (cmd == "stats") {
        std::cout << "count: " << p.Size() << '\n';
        std::cout << std::fixed << std::setprecision(1)
                  << "energy: " << p.Energy() << '\n';
      } else if (cmd == "count") {
        std::cout << p.Size() << '\n';
      } else if (cmd == "rename") {
        std::string id, new_name;
        if (!(in >> id >> new_name)) {
          throw BadArg("bad rename arguments");
        }
        p.Rename(id, new_name);
      } else if (cmd == "avg_energy") {
        std::cout << std::fixed << std::setprecision(1)
                  << p.AvgEnergy() << '\n';
      } else {
        throw BadArg("unknown command");
      }
    } catch (const FleetError& e) {
      std::cout << "error: " << e.what() << '\n';
    }
  }

  return 0;
}
