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
  std::unique_ptr<Piece> clone() const override;
  ~Pawn() override;

  std::string get_symbol() const override;
  char get_char() const override;
  std::string get_hollow_symbol() const override;
  std::string get_filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif