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
  b.add_piece(std::make_unique<Rook>(Location("a4"), 'w'));
  b.print_legal_moves(Location("d3"));

  //b.print();

}