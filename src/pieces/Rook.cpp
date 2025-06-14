#include "Rook.h"

Rook::Rook(const char& file, const char& rank, const char& col) 
: Piece(file, rank, col) {

}

Rook::Rook(const std::string& loc, const char& col) 
: Piece(loc, col) {

}

Rook::Rook(const Location& loc, const char& col)
: Piece(loc, col) {

}

std::unique_ptr<Piece> Rook::clone() const {
  return std::make_unique<Rook>(location, colour);
}

Rook::~Rook() {
  Piece::~Piece();
}

std::string Rook::get_symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♖" : "♜"};
}

char Rook::get_char() const {
  return 'R';
}

std::string Rook::get_hollow_symbol() const {
  return {"♖"};
}

std::string Rook::get_filled_symbol() const {
  return {"♜"};
}


void Rook::print() const {
  std::cout<<"Type: Rook"<<std::endl;
  Piece::print();
}

bool Rook::can_move_to(const Location& destination, const BoardView& board) const {
  if(!Piece::can_move_to(destination, board)) return false;

  int file_diff = destination.get_file() - location.get_file();
  int rank_diff = destination.get_rank() - location.get_rank();

  // Ensure movement is straight
  if(file_diff != 0 && rank_diff != 0) return false;

  int file_step = (file_diff == 0) ? 0 : file_diff / abs(file_diff);
  int rank_step = (rank_diff == 0) ? 0 : rank_diff / abs(rank_diff);

  return check_sliding_move(destination, file_step, rank_step, board);
}

std::vector<Location> Rook::legal_moves(const BoardView& board) const {
  std::vector<Location> moves;
  moves.reserve(14);
  add_sliding_moves(1, 0, moves, board);
  add_sliding_moves(-1, 0, moves, board);
  add_sliding_moves(0, 1, moves, board);
  add_sliding_moves(0, -1, moves, board);
  return filter_legal_moves(moves, board);
}
