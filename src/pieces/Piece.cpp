#include "Piece.h"

Piece::Piece(const char& file, const char& rank, const char& col)
  : location(file, rank), colour(col) {}

Piece::Piece(const std::string& loc, const char& col)
  : location(loc[0], loc[1]), colour(col) {}

Piece::Piece(const Location& loc, const char& col)
  : location(loc), colour(col) {}


void Piece::print() const {
  std::string col{"Black"};
  if(colour == 'w') {col = "White";}
  std::cout<<"Location: "<<location<<"\nColour: "<<col<<std::endl;
}

bool Piece::can_move_to(const Location& destination, const BoardView& board) const {
  if(!destination.is_valid()) {return false;}
  if(board.get_colour_at(destination) == colour) {return false;}
  return true;
}

void Piece::add_sliding_moves(const int& dx, const int& dy, std::vector<Location>& moves, const BoardView& board) const {
  Location candidate(location.get_file() + dx, location.get_rank() + dy);
  while(candidate.is_valid()) {
    char candidate_colour = board.get_colour_at(candidate);
    if(candidate_colour == 'n') {moves.push_back(candidate);}
    else {
      if(candidate_colour != colour) {moves.push_back(candidate);}
      return;
    }
    candidate.add_in_place(dx, dy);
  }
}

Location Piece::get_location() const {
  return location;
}

char Piece::get_colour() const {
  return colour;
}

void Piece::set_location(const char& file, const char& rank) {
  location = Location(file, rank);
}

void Piece::set_location(const Location& loc) {
  location = loc;
}

void Piece::set_colour(const char& col) {
  colour = col;
}