#include "Board.h"
#include "Location.h"
#include "Knight.h"
#include <memory>

int main() {
  Board b;

  b.add_piece(std::make_unique<Knight>(Location("b1"), 'w'));
  b.add_piece(std::make_unique<Knight>(Location("d2"), 'w'));
  b.add_piece(std::make_unique<Knight>(Location("a3"), 'b'));

  std::vector<Location> locs = b.legal_moves(Location("b1"));

  for (const Location& loc : locs) {
    std::cout << loc << std::endl;
  }
}