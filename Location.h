#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <ostream>

class Location {
private:
  char file{'a'};
  char rank{'1'};

public:
  Location() = default;
  Location(const char& f, const char& r);
  Location(const size_t& f, const size_t& r);
  Location(const std::string& loc);

  bool is_valid() const;

  Location add(const size_t& dx, const size_t& dy) const;
  char get_square_colour() const;

  std::string to_string() const;
  size_t get_file() const;
  size_t get_rank() const;
  void set_file(const char& f);
  void set_rank(const char& r);
  bool operator==(const Location& other) const;
};

std::ostream& operator<<(std::ostream& os, const Location& loc);

#endif