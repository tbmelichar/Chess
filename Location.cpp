#include "Location.h"
#include <stdexcept>
#include <iostream>

Location::Location(char f, char r) : file(f), rank(r) {
  if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
    std::cerr << "Invalid location: " << file << rank << "\n";
    std::exit(EXIT_FAILURE);
  }
}

char Location::get_file() const {
  return file;
}

char Location::get_rank() const {
  return rank;
}

void Location::set_file(const char& f) {
  file = f;
}

void Location::set_rank(const char& r) {
  rank = r;
}
