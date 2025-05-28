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
  Location(const int& f, const int& r);
  Location(const std::string& loc);

  bool is_valid() const;

  Location add(const int& dx, const int& dy) const;
  void add_in_place(const int& dx, const int& dy);
  std::pair<int, int> diff(const Location& loc) const;
  char get_square_colour() const;

  std::string to_string() const;
  int get_file() const;
  int get_rank() const;
  void set_file(const char& f);
  void set_rank(const char& r);
  bool operator==(const Location& other) const;
  bool operator!=(const Location& other) const;
};

std::ostream& operator<<(std::ostream& os, const Location& loc);

#endif