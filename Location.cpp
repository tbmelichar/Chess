#include "Location.h"
#include <stdexcept>
#include <iostream>

Location::Location(const char& f, const char& r) : file(f), rank(r) {
  if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
    std::cerr << "Invalid location: " << file << rank << "\n";
    std::exit(EXIT_FAILURE);
  }
}

Location::Location(const std::string& loc) {
  if(loc.length() != 2) {
    std::cerr << "Invalid location: " << loc << "\n";
    std::exit(EXIT_FAILURE);
  }
  file = loc[0];
  rank = loc[1];
  if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
    std::cerr << "Invalid location: " << file << rank << "\n";
    std::exit(EXIT_FAILURE);
  }
}

std::string Location::to_string() const {
  return {file, rank};
}

int Location::get_file() const {
  return file - 97;
}

int Location::get_rank() const {
  return rank - 49;
}

void Location::set_file(const char& f) {
  file = f;
}

void Location::set_rank(const char& r) {
  rank = r;
}

std::ostream& operator<<(std::ostream& os, const Location& loc) {
  return os << loc.to_string();
}
