#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "Location.h"

class Piece;

class BoardView {
public:
  virtual Piece* get_piece_at(const Location& loc) const = 0;
  virtual bool is_occupied(const Location& loc) const = 0;
  virtual bool is_enemy_at(const Location& loc, char my_colour) const = 0;

  virtual ~BoardView() = default;
};

#endif