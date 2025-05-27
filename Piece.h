#ifndef PIECE_H
#define PIECE_H

#include "Location.h"
#include "BoardView.h"

#include<iostream>
#include<vector>

class Piece {
protected:
  Location location;
  char colour{'w'};

public:
  Piece() = default;
  Piece(const char& file, const char& rank, const char& col);
  Piece(const std::string& loc, const char& col);
  Piece(const Location& loc, const char& col);

  //virtual void move_to(const Location& destination) = 0;
  virtual void print() const;
  virtual std::string symbol() const = 0;
  virtual std::string hollow_symbol() const = 0;
  virtual std::string filled_symbol() const = 0;
  virtual bool can_move_to(const Location& loc, const BoardView& board) const = 0;
  virtual std::vector<Location> legal_moves(const BoardView& board) const = 0; 
  
  Location get_location() const;
  char get_colour() const;
  
  void set_location(const char& file, const char& rank);
  void set_location(const Location& loc);
  void set_colour(const char& col);
  
  virtual ~Piece() = default;
};

#endif