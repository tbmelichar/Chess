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
  Board b(false);
  King k(Location('h', '8'), 'w');
  b.add_piece(std::make_unique<King>(k));
  b.add_piece(std::make_unique<Queen>(Location('a', '1'), 'b'));
  //b.show_legal_moves(Location("e5"));
  //b.print_legal_moves(Location("e5"));
  b.show();
  std::cout<<std::boolalpha<<k.in_check(b)<<std::endl;
  //b.show();

}