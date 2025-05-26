#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
private:
  char file{'a'};
  char rank{'1'};

public:
  Location() = default;
  Location(char f = 'a', char r = '1');
  char get_file() const;
  char get_rank() const;
  void set_file(const char& f);
  void set_rank(const char& r);
};

#endif