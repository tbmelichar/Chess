#include "Board.h"
#include "Location.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include <memory>

int main() {
  Board b;

  b.add_piece(std::make_unique<Knight>(Location("g4"), 'b'));
  b.add_piece(std::make_unique<Knight>(Location("g5"), 'w'));
  b.add_piece(std::make_unique<Knight>(Location("g6"), 'b'));
  b.add_piece(std::make_unique<Knight>(Location("g7"), 'b'));
  b.add_piece(std::make_unique<Rook>(Location("d6"), 'b'));
  b.add_piece(std::make_unique<Rook>(Location("a1"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a2"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a3"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a4"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a1"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a2"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("b3"), 'b'));
  b.add_piece(std::make_unique<Rook>(Location("c4"), 'w'));
  b.add_piece(std::make_unique<Queen>(Location("d2"), 'w'));
  b.print_legal_moves(Location("d2"));

  Piece* queen = b.get_piece_at(Location("d2"));

  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      Location test(i, j);
      if(queen->can_move_to(test, b)) {std::cout<<test<<", ";}
    }
  }

}