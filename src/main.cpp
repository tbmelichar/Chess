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

  King k(Location(b), 'w');
  b.add_piece(std::make_unique<King>(k));

  b.add_piece(std::make_unique<Rook>(Location(b), 'b'));
  b.add_piece(std::make_unique<Knight>(Location(b), 'b'));
  b.add_piece(std::make_unique<Bishop>(Location(b), 'b'));
  b.add_piece(std::make_unique<Queen>(Location(b), 'b'));
  b.add_piece(std::make_unique<King>(Location(b), 'b'));
  b.add_piece(std::make_unique<Pawn>(Location(b), 'b'));
  b.add_piece(std::make_unique<Pawn>(Location(b), 'b'));

  b.show();


  //b.add_piece(std::make_unique<Pawn>(Location('c', '3'), 'b'));
  //b.add_piece(std::make_unique<Queen>(Location('a', '1'), 'b'));
  ////b.show_legal_moves(Location("e5"));
  ////b.print_legal_moves(Location("e5"));
  //b.show();
  std::cout<<std::boolalpha<<k.in_check(b)<<std::endl;
  //b.show();

}