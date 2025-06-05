#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
  King() = default;
  King(const char& file, const char& rank, const char& col);
  King(const std::string& loc, const char& col);
  King(const Location& loc, const char& col);
  ~King() override;

  std::string symbol() const override;
  std::string hollow_symbol() const override;
  std::string filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif