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
  b.add_piece(std::make_unique<King>(Location('e', '5'), 'w'));
  b.add_piece(std::make_unique<Pawn>(Location('e', '6'), 'k'));
  b.add_piece(std::make_unique<Pawn>(Location('d', '6'), 'w'));
  b.show_legal_moves(Location("e5"));
  b.print_legal_moves(Location("e5"));
  //std::cout<<std::boolalpha<<b.get_piece_at(Location("f7"))->can_move_to(Location("f6"), b)<<std::endl;
  //b.show();

}