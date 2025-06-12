#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
  King() = default;
  King(const char& file, const char& rank, const char& col);
  King(const std::string& loc, const char& col);
  King(const Location& loc, const char& col);
  std::unique_ptr<Piece> clone() const override;
  ~King() override;

  std::string get_symbol() const override;
  char get_char() const override;
  std::string get_hollow_symbol() const override;
  std::string get_filled_symbol() const override;
  void print() const override;

  bool can_move_to(const Location& destination, const BoardView& board) const override;
  std::vector<Location> legal_moves(const BoardView& board) const override;

  bool in_check_from_sliding_piece(const int& dx, const int& dy, const char& enemy_char, const BoardView& board) const;
  bool in_check_from_sliding_piece(const int& dx, const int& dy, const std::string& enemy_chars, const BoardView& board) const;
  bool in_check(const BoardView& board) const;
  bool in_check_from_knight(const BoardView& board) const;
  bool in_check_from_king(const BoardView& board) const;
  bool in_check_from_pawn(const BoardView& board) const;
};

#endif