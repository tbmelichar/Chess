#ifndef BOARD_H
#define BOARD_H

#include "BoardView.h"
#include "Piece.h"
#include <memory>
#include <iostream>
#include <iomanip>

class Board : public BoardView {
private:
  std::unique_ptr<Piece> squares[8][8];
  static const std::string reset;
  static const std::string white_background;
  static const std::string white;
  static const std::string black_background;
  static const std::string black;
  static const std::string selected;
  static const std::string capturable;

public:
  Board();
  ~Board() = default;

  void show() const;

  // Functions available to pieces
  Piece* get_piece_at(const Location& loc) const override;
  bool is_occupied(const Location& loc) const override;
  bool is_enemy_at(const Location& loc, char my_colour) const override;
  char get_colour_at(const Location& loc) const override;

  // Game logic
  bool move_piece(const Location& from, const Location& to);
  std::vector<Location> legal_moves(const Location& loc) const override;
  void show_legal_moves(const Location& loc) const;
  void print_legal_moves(const Location& loc) const;

  // Setup
  void add_piece(std::unique_ptr<Piece> piece);
};

#endif