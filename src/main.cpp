#include "Board.h"
#include "Location.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"
#include <memory>

int main() {
  Board b;
  b.add_piece(std::make_unique<Pawn>(Location('e', '3'), 'b'));
  b.show_legal_moves(Location("f2"));
  b.print_legal_moves(Location("f2"));
  //std::cout<<std::boolalpha<<b.get_piece_at(Location("f7"))->can_move_to(Location("f6"), b)<<std::endl;
  //b.show();

}