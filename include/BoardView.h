#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Location.h"
#include <vector>

class Piece;

class BoardView {
public:
  virtual Piece* get_piece_at(const Location& loc) const = 0;
  virtual bool is_occupied(const Location& loc) const = 0;
  virtual bool is_friend_at(const Location& loc, const char& my_colour) const = 0;
  virtual bool is_enemy_at(const Location& loc, const char& my_colour) const = 0;
  virtual char get_colour_at(const Location& loc) const = 0;
  virtual std::vector<Location> legal_moves(const Location&) const = 0;
  virtual size_t get_move_number() const = 0;

  virtual bool is_specific_enemy_at(const Location& loc, const char& my_colour, const char& piece_char) const = 0;
  virtual bool is_specific_enemy_at(const Location& loc, const char& my_colour, const std::string& piece_chars) const = 0;

  virtual ~BoardView() = default;
};

#endif