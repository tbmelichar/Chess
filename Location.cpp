#include "Location.h"
#include <stdexcept>
#include <iostream>

Location::Location(const char& f, const char& r) : file(f), rank(r) {}

Location::Location(const size_t& f, const size_t& r) : file(f + 97), rank(r + 49) {}

Location::Location(const std::string& loc) {
  if(loc.length() != 2) {
    std::cerr << "Invalid location: " << loc << "\n";
    std::exit(EXIT_FAILURE);
  }
  file = loc[0];
  rank = loc[1];
}

bool Location::is_valid() const {
  return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
}

Location Location::add(const size_t& dx, const size_t& dy) const {
  Location new_loc(get_file() + dx, get_rank() + dy);
  return new_loc;
}

char Location::get_square_colour() const {
  size_t sum = (get_file() + get_rank()) % 2;
  return {(sum == 1) ? 'w' : 'b'};
}

std::string Location::to_string() const {
  return {file, rank};
}

size_t Location::get_file() const {
  return file - 97;
}

size_t Location::get_rank() const {
  return rank - 49;
}

void Location::set_file(const char& f) {
  file = f;
}

void Location::set_rank(const char& r) {
  rank = r;
}

bool Location::operator==(const Location& other) const {
  return file == other.file && rank == other.rank;
}

std::ostream& operator<<(std::ostream& os, const Location& loc) {
  return os << loc.to_string();
}
