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
  Location(char f, char r);

  std::string to_string() const;
  char get_file() const;
  char get_rank() const;
  void set_file(const char& f);
  void set_rank(const char& r);
};

std::ostream& operator<<(std::ostream& os, const Location& loc);

#endif