#ifndef PIECE_H
#define PIECE_H

#include "Location.h"

class Piece {
protected:
  Location location;
  char colour{'w'};

public:
  Piece() = default;

  Piece(char file, char rank, char col);

  virtual ~Piece() = default;

  Location get_location() const;
  char get_colour() const;

  void set_location(char file, char rank);
  void set_colour(char col);

  virtual void move_to(const Location& destination) = 0;
};

#endif