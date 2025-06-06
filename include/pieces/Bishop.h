#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
  Bishop() = default;
  Bishop(const char& file, const char& rank, const char& col);
  Bishop(const std::string& loc, const char& col);
  Bishop(const Location& loc, const char& col);
  ~Bishop() override;

  std::string get_symbol() const override;
  char get_char() const override;
  std::string get_hollow_symbol() const override;
  std::string get_filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;
};

#endif