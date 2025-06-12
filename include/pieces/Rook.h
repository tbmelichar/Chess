#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
  Rook() = default;
  Rook(const char& file, const char& rank, const char& col);
  Rook(const std::string& loc, const char& col);
  Rook(const Location& loc, const char& col);
  std::unique_ptr<Piece> clone() const override;
  ~Rook() override;

  std::string get_symbol() const override;
  char get_char() const override;
  std::string get_hollow_symbol() const override;
  std::string get_filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif