#include "Pawn.h"

Pawn::Pawn(const char& file, const char& rank, const char& col) 
: Piece(file, rank, col) {

}

Pawn::Pawn(const std::string& loc, const char& col) 
: Piece(loc, col) {

}

Pawn::Pawn(const Location& loc, const char& col)
: Piece(loc, col) {

}

Pawn::~Pawn() {
  Piece::~Piece();
}

std::string Pawn::symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♙" : "♟"};
}

std::string Pawn::get_hollow_symbol() const {
  return {"♙"};
}

std::string Pawn::get_filled_symbol() const {
  return {"♟"};
}


void Pawn::print() const {
  std::cout<<"Type: Pawn"<<std::endl;
  Piece::print();
}

bool Pawn::can_move_to(const Location& destination, const BoardView& board) const {
  if(!Piece::can_move_to(destination, board)) {return false;}

  int file_diff = destination.get_file() - location.get_file();
  int rank_diff = destination.get_rank() - location.get_rank();

  int sign = (colour == 'w') ? 1 : -1;

  //if(abs(file_diff) == 1 && abs(rank_diff) == 1) {}

  if(file_diff == 0 && rank_diff*sign <= 2) { // Check it's moving forward 1 or 2 squares 
    if(board.is_occupied(location.add(0,sign))) {return false;} // Check square in front of pawn
    if(rank_diff == sign) {return true;} // If pawn's only moving one square thats all that needs checking  
    if(location.get_rank() == int(sign * -2.5 + 4.5) || board.is_occupied(location.add(0,2*sign))) {return false;} // Check square two in front of pawn
    return true;
  } else if(abs(file_diff) == 1 && rank_diff == sign) { // Check it's taking something
    if(board.is_occupied(destination)) {return true;}
    if(file_diff == sign && can_en_passent_right) {return true;} 
    if(file_diff == -sign && can_en_passent_left) {return true;} 
  }

  return false;
}

std::vector<Location> Pawn::legal_moves(const BoardView& board) const {
  int sign = (colour == 'w') ? 1 : -1;
  std::vector<Location> moves;
  if(!board.is_occupied(location.add(0,sign))) {
    moves.push_back(location.add(0,sign));
    if(!board.is_occupied(location.add(0,2*sign))) {moves.push_back(location.add(0,2*sign));}
  }
  if(board.is_enemy_at(location.add(1,sign), colour)) {moves.push_back(location.add(1,sign));}
  if(board.is_enemy_at(location.add(-1,sign), colour)) {moves.push_back(location.add(-1,sign));}

  if(can_en_passent_right) {moves.push_back(location.add(sign,sign));}
  if(can_en_passent_left) {moves.push_back(location.add(-sign,sign));}

  return moves;
}