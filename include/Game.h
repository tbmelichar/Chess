#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"

class Game {
private:
  Board board;

public:
  Game() = default;
  ~Game() {};

  void show_board() const;

  void user_move();
};

#endif