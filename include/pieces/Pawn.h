#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
private:
  bool has_moved{false};
  bool can_en_passent_left{false};
  bool can_en_passent_right{false};
public:
  Pawn() = default;
  Pawn(const char& file, const char& rank, const char& col);
  Pawn(const std::string& loc, const char& col);
  Pawn(const Location& loc, const char& col);
  ~Pawn() override;

  std::string symbol() const override;
  std::string hollow_symbol() const override;
  std::string filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif