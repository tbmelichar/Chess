#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
  Knight() = default;
  Knight(const char& file, const char& rank, const char& col);
  Knight(const std::string& loc, const char& col);
  Knight(const Location& loc, const char& col);

  // Return symbol for printing (override if needed)
  char symbol() const override;
  void print() const override;

  // Return legal moves from this position using a board view
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif