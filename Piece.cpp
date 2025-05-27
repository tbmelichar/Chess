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