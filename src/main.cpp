#include "Game.h"
#include "Board.h"
#include "Location.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"
#include "King.h"
#include <memory>

int main() {
  //Board b;
  //b.show();
  //b.move_piece(Location("e2"), Location("e5"));
  //b.show();
  for (int i = 0; i < 15; ++i) {std::cout << "\n";}
  for (int i = 0; i < 12; ++i) {std::cout << "\033[A\033[2K";}
  Game g;
  g.show_board();
  for(int i = 0; i < 50; i++) {g.user_move();}
}