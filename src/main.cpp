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
  Board b;
  b.show();
  b.move_piece(Location("e2"), Location("e4"));

  b.show();
  Board c(b);
  c.show();
  b.move_piece(Location("d2"), Location("d4"));
  b.show();
  c.show();
}