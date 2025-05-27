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

char Knight::symbol() const {
  return 'k';
}

void Knight::print() const {
  std::cout<<"Type: Knight"<<std::endl;
  Piece::print();
}

std::vector<Location> Knight::legal_moves(const BoardView& board) const {
  static const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
  static const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

  std::vector<Location> moves;

  Location current = this->get_location();
  char my_colour = this->get_colour();

  for (int i = 0; i < 8; ++i) {
    Location candidate = location.add(dx[i], dy[i]);
    if (!candidate.is_valid()) continue;

    char target_colour = board.get_colour_at(candidate);
    if (target_colour == 'n' || target_colour != my_colour) {
      moves.push_back(candidate);
    }
  }

  return moves;
}
