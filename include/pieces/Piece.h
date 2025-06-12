#ifndef PIECE_H
#define PIECE_H

#include "Location.h"
#include "BoardView.h"

#include <iostream>
#include <vector>
#include <memory>

class Piece {
protected:
  Location location;
  char colour{'w'};

public:
  Piece() = default;
  Piece(const char& file, const char& rank, const char& col);
  Piece(const std::string& loc, const char& col);
  Piece(const Location& loc, const char& col);
  virtual std::unique_ptr<Piece> clone() const = 0;
  virtual ~Piece() {};

  virtual bool move_to(const Location& destination, const BoardView& board);
  virtual void print() const;
  virtual std::string get_symbol() const = 0;
  virtual char get_char() const = 0;
  virtual std::string get_hollow_symbol() const = 0;
  virtual std::string get_filled_symbol() const = 0;
  virtual std::vector<Location> legal_moves(const BoardView& board) const = 0; 
  
  virtual bool can_move_to(const Location& destination, const BoardView& board) const;
  void add_sliding_moves(const int& dx, const int& dy, std::vector<Location>& moves, const BoardView& board) const;
  bool check_sliding_move(const Location& destination, const int& dx, const int& dy, const BoardView& board) const;

  Location get_location() const;
  char get_colour() const;
  
  void set_location(const char& file, const char& rank);
  void set_location(const Location& loc);
  void set_colour(const char& col);
  
};

#endif