#include "Board.h"
#include "Location.h"
#include <memory>

int main() {
  Board b;
  b.add_piece(std::make_unique<Piece>("b3", 'w'));
  b.print();

  std::cout<<std::endl;

  b.move_piece(Location("b3"), Location("b5"));
  b.print();
}