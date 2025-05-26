#include "Piece.h"

Piece::Piece(char file, char rank, char col)
  : location(file, rank), colour(col) {}

Location Piece::get_location() const {
  return location;
}

char Piece::get_colour() const {
  return colour;
}

void Piece::set_location(char file, char rank) {
  location = Location(file, rank);
}

void Piece::set_colour(char col) {
  colour = col;
}