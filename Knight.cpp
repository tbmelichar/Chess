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

bool Knight::can_move_to(const Location& loc, const BoardView& board) const {
  if (!loc.is_valid()) {return false;}
  if (board.get_colour_at(loc) == colour) {return false;}
  return true;
}

std::vector<Location> Knight::legal_moves(const BoardView& board) const {
  static const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
  static const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

  std::vector<Location> moves;

  for (int i = 0; i < 8; ++i) {
    Location candidate = location.add(dx[i], dy[i]);
    if(can_move_to(candidate, board)) {moves.push_back(candidate);}
  }

  return moves;
}
