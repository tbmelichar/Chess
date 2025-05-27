#ifndef BOARD_H
#define BOARD_H

#include "BoardView.h"
#include "Piece.h"
#include <memory>
#include <iostream>
#include <iomanip>

class Board : public BoardView {
private:
  std::unique_ptr<Piece> squares[8][8];  // Now using smart pointers

public:
  Board() = default;
  ~Board() = default;  // No manual deletes needed

  void print() const;

  // Implement BoardView interface
  Piece* get_piece_at(const Location& loc) const override;
  bool is_occupied(const Location& loc) const override;
  bool is_enemy_at(const Location& loc, char my_colour) const override;

  // Game logic
  bool move_piece(const Location& from, const Location& to);

  // Setup
  void add_piece(std::unique_ptr<Piece> piece);
};

#endif