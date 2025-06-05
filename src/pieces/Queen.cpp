#include "Queen.h"

Queen::Queen(const char& file, const char& rank, const char& col) 
: Piece(file, rank, col) {

}

Queen::Queen(const std::string& loc, const char& col) 
: Piece(loc, col) {

}

Queen::Queen(const Location& loc, const char& col)
: Piece(loc, col) {

}

Queen::~Queen() {
  Piece::~Piece();
}

std::string Queen::symbol() const {
  char square_colour = location.get_square_colour();
  return {(colour == square_colour) ? "♕" : "♛"};
}

std::string Queen::hollow_symbol() const {
  return {"♕"};
}

std::string Queen::filled_symbol() const {
  return {"♛"};
}


void Queen::print() const {
  std::cout<<"Type: Queen"<<std::endl;
  Piece::print();
}

bool Queen::can_move_to(const Location& destination, const BoardView& board) const {
  if(!Piece::can_move_to(destination, board)) {return false;}

  int file_diff = destination.get_file() - location.get_file();
  int rank_diff = destination.get_rank() - location.get_rank();

  if(abs(file_diff) != abs(rank_diff) && file_diff != 0 && rank_diff != 0) {return false;}

  int file_step = (file_diff == 0) ? 0 : file_diff / abs(file_diff);
  int rank_step = (rank_diff == 0) ? 0 : rank_diff / abs(rank_diff);
  //std::cout<<"("<<file_diff<<","<<rank_diff<<","<<destination<<")";

  Location current(location.get_file() + file_step, location.get_rank() + rank_step);

  // Check each square along diagonal for obstructions
  while(current != destination) {
    if(board.is_occupied(current)) {return false;}
    current.add_in_place(file_step, rank_step);
  }

  return true;
}

std::vector<Location> Queen::legal_moves(const BoardView& board) const {
  std::vector<Location> moves;
  add_sliding_moves(1, 1, moves, board);
  add_sliding_moves(-1, 1, moves, board);
  add_sliding_moves(-1, -1, moves, board);
  add_sliding_moves(1, -1, moves, board);
  add_sliding_moves(1, 0, moves, board);
  add_sliding_moves(-1, 0, moves, board);
  add_sliding_moves(0, 1, moves, board);
  add_sliding_moves(0, -1, moves, board);
  return moves;
}