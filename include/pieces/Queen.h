#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
  Queen() = default;
  Queen(const char& file, const char& rank, const char& col);
  Queen(const std::string& loc, const char& col);
  Queen(const Location& loc, const char& col);

  std::string symbol() const override;
  std::string hollow_symbol() const override;
  std::string filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif