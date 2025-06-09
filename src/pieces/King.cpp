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

std::string King::get_symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♔" : "♚"};
}

char King::get_char() const {
  return 'K';
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
    if(candidate.is_valid() && !board.is_friend_at(candidate, colour)) {moves.push_back(candidate);}
  }

  return moves;
}

bool King::in_check_from_sliding_piece(const int& dx, const int& dy, const char& enemy_char, const BoardView& board) const {
  Location candidate(location.get_file() + dx, location.get_rank() + dy);
  while(candidate.is_valid()) {
    if(board.is_specific_enemy_at(candidate, colour, enemy_char)) {return true;}
    if(board.is_occupied(candidate)) {return false;}
    candidate.add_in_place(dx, dy);
  }
  return false;
}

bool King::in_check_from_sliding_piece(const int& dx, const int& dy, const std::string& enemy_chars, const BoardView& board) const {
  Location candidate(location.get_file() + dx, location.get_rank() + dy);
  while(candidate.is_valid()) {
    if(board.is_specific_enemy_at(candidate, colour, enemy_chars)) {return true;}
    if(board.is_occupied(candidate)) {return false;}
    candidate.add_in_place(dx, dy);
  }
  return false;
}

bool King::in_check_from_knight(const BoardView& board) const {
  static const int dx[8] = {1,  1,  2,  2, -1, -1, -2, -2};
  static const int dy[8] = {2, -2,  1, -1,  2, -2,  1, -1};
 
  for (int i = 0; i < 8; ++i) {
    Location candidate = location.add(dx[i], dy[i]);
    if(candidate.is_valid() && board.is_specific_enemy_at(candidate, colour, 'N')) {return true;}
  }
  return false;
}

bool King::in_check_from_pawn(const BoardView& board) const {
  int sign = (colour == 'w') ? 1 : -1;
  Location candidate = location.add(1, sign);
  if(candidate.is_valid() && board.is_specific_enemy_at(candidate, colour, 'P')) {return true;}
  candidate.add_in_place(-2, 0);
  if(candidate.is_valid() && board.is_specific_enemy_at(candidate, colour, 'P')) {return true;}
  return false;
}

bool King::in_check_from_king(const BoardView& board) const {
  static const int dx[8] = { 1, 1, 1, 0, -1, -1, -1,  0};
  static const int dy[8] = {-1, 0, 1, 1,  1,  0, -1, -1};
  for (int i = 0; i < 8; ++i) {
    Location candidate = location.add(dx[i], dy[i]);
    if(candidate.is_valid() && board.is_specific_enemy_at(candidate, colour, 'K')) {return true;}
  }
  return false;
}


bool King::in_check(const BoardView& board) const {
  if(in_check_from_sliding_piece(1,   0, "QR", board)) {return true;}
  if(in_check_from_sliding_piece(-1,  0, "QR", board)) {return true;}
  if(in_check_from_sliding_piece(0,   1, "QR", board)) {return true;}
  if(in_check_from_sliding_piece(0,  -1, "QR", board)) {return true;}
  if(in_check_from_sliding_piece(1,   1, "QB", board)) {return true;}
  if(in_check_from_sliding_piece(1,  -1, "QB", board)) {return true;}
  if(in_check_from_sliding_piece(-1,  1, "QB", board)) {return true;}
  if(in_check_from_sliding_piece(-1, -1, "QB", board)) {return true;}
  if(in_check_from_knight(board)) {return true;}
  if(in_check_from_pawn(board)) {return true;}
  if(in_check_from_king(board)) {return true;}
  return false;
}

