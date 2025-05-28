#include "Knight.h"

Knight::Knight(const char& file, const char& rank, const char& col) 
: Piece(file, rank, col) {

}

Knight::Knight(const std::string& loc, const char& col) 
: Piece(loc, col) {

}

Knight::Knight(const Location& loc, const char& col)
: Piece(loc, col) {

}

std::string Knight::symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♘" : "♞"};
}

std::string Knight::hollow_symbol() const {
  return {"♘"};
}

std::string Knight::filled_symbol() const {
  return {"♞"};
}

void Knight::print() const {
  std::cout<<"Type: Knight"<<std::endl;
  Piece::print();
}

bool Knight::can_move_to(const Location& destination, const BoardView& board) const {
  if(!Piece::can_move_to(destination, board)) {return false;}
  std::pair<int, int> difference = location.diff(destination);
  if((abs(difference.first) == 2 && abs(difference.second) == 1) || (abs(difference.first) == 1 && abs(difference.second) == 2)) {return true;}
  return false;
}

std::vector<Location> Knight::legal_moves(const BoardView& board) const {
  static const int dx[8] = {1,  1,  2,  2, -1, -1, -2, -2};
  static const int dy[8] = {2, -2,  1, -1,  2, -2,  1, -1};
 
  std::vector<Location> moves;

  for (int i = 0; i < 8; ++i) {
    Location candidate = location.add(dx[i], dy[i]);
    if(candidate.is_valid() && board.get_colour_at(candidate) != colour) {moves.push_back(candidate);}
  }

  return moves;
}
