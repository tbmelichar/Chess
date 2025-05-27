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

bool Bishop::can_move_to(const Location& loc, const BoardView& board) const {
  if(!loc.is_valid()) {return false;}
  if(board.get_colour_at(loc) == colour) {return false;}
  return true;
}

std::vector<Location> Bishop::legal_moves(const BoardView& board) const {

  std::vector<Location> moves;

  for (int i = location.get_file()+1; i < 8; i++) {
    Location candidate(i, location.get_rank());
    char candidate_colour = board.get_colour_at(candidate);
    if(candidate_colour == 'n') {moves.push_back(candidate);}
    else {
      if(candidate_colour != colour) {moves.push_back(candidate);}
      break;
    }
  }
  for (int i = location.get_file()-1; i >= 0; i--) {
    Location candidate(i, location.get_rank());
    char candidate_colour = board.get_colour_at(candidate);
    if(candidate_colour == 'n') {moves.push_back(candidate);}
    else {
      if(candidate_colour != colour) {moves.push_back(candidate);}
      break;
    }
  }
  for (int i = location.get_rank()+1; i < 8; i++) {
    Location candidate(location.get_file(), i);
    char candidate_colour = board.get_colour_at(candidate);
    if(candidate_colour == 'n') {moves.push_back(candidate);}
    else {
      if(candidate_colour != colour) {moves.push_back(candidate);}
      break;
    }
  }
  for (int i = location.get_rank()-1; i >= 0; i--) {
    Location candidate(location.get_file(), i);
    char candidate_colour = board.get_colour_at(candidate);
    if(candidate_colour == 'n') {moves.push_back(candidate);}
    else {
      if(candidate_colour != colour) {moves.push_back(candidate);}
      break;
    }
  }
  
  return moves;
}
