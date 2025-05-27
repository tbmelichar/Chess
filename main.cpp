#include "Board.h"
#include "Location.h"
#include "Knight.h"
#include "Rook.h"
#include <memory>

int main() {
  Board b;

  b.add_piece(std::make_unique<Knight>(Location("g4"), 'b'));
  b.add_piece(std::make_unique<Knight>(Location("g5"), 'w'));
  b.add_piece(std::make_unique<Knight>(Location("g6"), 'b'));
  b.add_piece(std::make_unique<Knight>(Location("g7"), 'b'));
  b.add_piece(std::make_unique<Knight>(Location("d2"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("d6"), 'b'));
  b.add_piece(std::make_unique<Rook>(Location("a1"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a2"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a3"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a4"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a1"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("a2"), 'w'));
  b.add_piece(std::make_unique<Rook>(Location("b3"), 'b'));
  b.add_piece(std::make_unique<Rook>(Location("c4"), 'w'));
  b.print_legal_moves(Location("d2"));

  //std::cout<<std::boolalpha<<b.get_piece_at(Location("d6"))->can_move_to(Location("h6"), b)<<std::endl;
  //std::cout<<std::boolalpha<<b.get_piece_at(Location("d6"))->can_move_to(Location("d1"), b)<<std::endl;
  Piece* r = b.get_piece_at(Location("d6"));
  for(int i = 7; i >= 0; i--) {
    for(size_t j = 0; j < 8; j++) {
      std::cout<<r->can_move_to(Location(j, i), b);
    }
    std::cout<<std::endl;
  }
  //b.print();

}