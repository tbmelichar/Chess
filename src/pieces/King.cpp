#include "King.h"

King::King(const char& file, const char& rank, const char& col) 
: Piece(file, rank, col) {

}

King::King(const std::string& loc, const char& col) 
: Piece(loc, col) {

}

King::King(const Location& loc, const char& col)
: Piece(loc, col) {

}

King::~King() {
  Piece::~Piece();
}

std::string King::symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♔" : "♚"};
}

std::string King::get_hollow_symbol() const {
  return {"♔"};
}

std::string King::get_filled_symbol() const {
  return {"♚"};
}


void King::print() const {
  std::cout<<"Type: King"<<std::endl;
  Piece::print();
}

bool King::can_move_to(const Location& destination, const BoardView& board) const {
  if(!Piece::can_move_to(destination, board)) {return false;}

  int file_diff = destination.get_file() - location.get_file();
  int rank_diff = destination.get_rank() - location.get_rank();
  
  if(std::abs(file_diff) > 1 || std::abs(rank_diff) > 1) {return false;}

  return true;
}

std::vector<Location> King::legal_moves(const BoardView& board) const {
  static const int dx[8] = { 1, 1, 1, 0, -1, -1, -1,  0};
  static const int dy[8] = {-1, 0, 1, 1,  1,  0, -1, -1};
 
  std::vector<Location> moves;

  for (int i = 0; i < 8; ++i) {
    Location candidate = location.add(dx[i], dy[i]);
    if(candidate.is_valid() && board.get_colour_at(candidate) != colour) {moves.push_back(candidate);}
  }

  return moves;
}

bool King::in_check_from_rook(const BoardView& board) const {

}
