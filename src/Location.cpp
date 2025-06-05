#include "Location.h"
#include <stdexcept>
#include <iostream>

Location::Location(const char& f, const char& r) : file(f), rank(r) {}

Location::Location(const int& f, const int& r) : file(f + 97), rank(r + 49) {}

Location::Location(const std::string& loc) {
  if(loc.length() != 2) {
    std::cerr << "Invalid location: " << loc << "\n";
    std::exit(EXIT_FAILURE);
  }
  file = loc[0];
  rank = loc[1];
}

Location::Location(const Location& loc) {
  file = loc.file;
  rank = loc.rank;
}


bool Location::is_valid() const {
  return (file >= 'a' && file <= 'h' && rank >= '1' && rank <= '8');
}

Location Location::add(const int& dx, const int& dy) const {
  Location new_loc(get_file() + dx, get_rank() + dy);
  return new_loc;
}

void Location::add_in_place(const int& dx, const int& dy) {
  file += dx;
  rank += dy;
}

std::pair<int, int> Location::diff(const Location& loc) const {
  return {file-loc.file, rank-loc.rank};
}

char Location::get_square_colour() const {
  int sum = (get_file() + get_rank()) % 2;
  return {(sum == 1) ? 'w' : 'b'};
}

std::string Location::to_string() const {
  return {file, rank};
}

int Location::get_file() const {
  return file - 'a';
}

int Location::get_rank() const {
  return rank - '1';
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

bool Location::operator!=(const Location& other) const {
  return !(operator==(other));
}

void Location::operator=(const Location& other) {
  file = other.file;
  rank = other.rank;
}

std::ostream& operator<<(std::ostream& os, const Location& loc) {
  return os << loc.to_string();
}
