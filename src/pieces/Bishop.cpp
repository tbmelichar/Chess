#include "Bishop.h"

Bishop::Bishop(const char& file, const char& rank, const char& col) 
: Piece(file, rank, col) {

}

Bishop::Bishop(const std::string& loc, const char& col) 
: Piece(loc, col) {

}

Bishop::Bishop(const Location& loc, const char& col)
: Piece(loc, col) {

}

Bishop::~Bishop() {
  Piece::~Piece();
}

std::string Bishop::symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♗" : "♝"};
}

std::string Bishop::hollow_symbol() const {
  return {"♗"};
}

std::string Bishop::filled_symbol() const {
  return {"♝"};
}


void Bishop::print() const {
  std::cout<<"Type: Bishop"<<std::endl;
  Piece::print();
}

bool Bishop::can_move_to(const Location& destination, const BoardView& board) const {
  if(!Piece::can_move_to(destination, board)) {return false;}

  int file_diff = destination.get_file() - location.get_file();
  int rank_diff = destination.get_rank() - location.get_rank();

  if(abs(file_diff) != abs(rank_diff)) {return false;}

  int file_step = file_diff / abs(file_diff);
  int rank_step = rank_diff / abs(rank_diff);

  Location current(location.get_file() + file_step, location.get_rank() + rank_step);

  // Check each square along diagonal for obstructions
  while(current != destination) {
    if(board.is_occupied(current)) {return false;}
    current.add_in_place(file_step, rank_step);
  }

  return true;
}

std::vector<Location> Bishop::legal_moves(const BoardView& board) const {
  std::vector<Location> moves;
  add_sliding_moves(1, 1, moves, board);
  add_sliding_moves(-1, 1, moves, board);
  add_sliding_moves(-1, -1, moves, board);
  add_sliding_moves(1, -1, moves, board);
  return moves;
}