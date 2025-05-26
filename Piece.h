#ifndef PIECE_H
#define PIECE_H

#include "Location.h"

#include<iostream>

class Piece {
protected:
  Location location;
  char colour{'w'};

public:
  Piece() = default;
  Piece(const char& file, const char& rank, const char& col);
  Piece(const std::string& loc, const char& col);

  //virtual void move_to(const Location& destination) = 0;
  void print() const;
  
  Location get_location() const;
  char get_colour() const;
  
  void set_location(char file, char rank);
  void set_colour(char col);
  
  virtual ~Piece() = default;
};

#endif