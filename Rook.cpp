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

std::string Rook::symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♖" : "♜"};
}

std::string Rook::hollow_symbol() const {
  return {"♖"};
}

std::string Rook::filled_symbol() const {
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

  Location current(location.get_file() + file_step, location.get_rank() + rank_step);

  // Check each square along the path for obstructions
  while(current != destination) {
    if(board.is_occupied(current)) return false;
    current.add_in_place(file_step, rank_step);
  }

  return true;
}

std::vector<Location> Rook::legal_moves(const BoardView& board) const {
  std::vector<Location> moves;
  add_sliding_moves(1, 0, moves, board);
  add_sliding_moves(-1, 0, moves, board);
  add_sliding_moves(0, 1, moves, board);
  add_sliding_moves(0, -1, moves, board);
  return moves;
}
