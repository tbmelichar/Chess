#include "Board.h"

#include <algorithm>

const std::string Board::reset = "\033[0m";            // full reset
const std::string Board::white_background = "\033[47m";
const std::string Board::black_background = "\033[40m";

const std::string Board::white = "\033[37m";            // just white foreground
const std::string Board::black = "\033[30m";            // just black foreground
const std::string Board::selected = "\033[32m";         // just green foreground
const std::string Board::capturable = "\033[31m";       // just red foreground

Piece* Board::get_piece_at(const Location& loc) const {
  return squares[loc.get_file()][loc.get_rank()].get();  // Return raw pointer
}

bool Board::is_occupied(const Location& loc) const {
  return get_piece_at(loc) != nullptr;
}

bool Board::is_enemy_at(const Location& loc, char my_colour) const {
  Piece* p = get_piece_at(loc);
  return p && p->get_colour() != my_colour;
}

char Board::get_colour_at(const Location& loc) const {
  Piece* p = get_piece_at(loc);
  if(p) {return p->get_colour();}
  return 'n';
}

void Board::add_piece(std::unique_ptr<Piece> piece) {
  Location loc = piece->get_location();
  int f = loc.get_file();
  int r = loc.get_rank();
  squares[f][r] = std::move(piece);  // Transfer ownership
}

bool Board::move_piece(const Location& from, const Location& to) {
  int fx = from.get_file(), fy = from.get_rank();
  int tx = to.get_file(), ty = to.get_rank();

  if (!squares[fx][fy]) return false;

  // Capture: just overwrite the destination square
  squares[tx][ty] = std::move(squares[fx][fy]);
  squares[tx][ty]->set_location(to);
  squares[fx][fy].reset();

  return true;
}

void Board::print() const {
  for (int rank = 7; rank >= 0; --rank) {
    std::cout<<rank + 1<<" ";
    for (size_t file = 0; file < 8; ++file) {
      Location current(file, rank);
      Piece* p = squares[file][rank].get();  // Access raw pointer
      std::string piece_colour(white); 
      std::string square_colour(black_background);
      if(current.get_square_colour() == 'w') {piece_colour = black; square_colour = white_background;}
      
      std::cout<<square_colour<<piece_colour<<" "<<(p ? p->symbol() : " ")<<" "<<reset;
    }
    std::cout<<'\n';
  }
  std::cout<<"   a  b  c  d  e  f  g  h\n";
}

std::vector<Location> Board::legal_moves(const Location& loc) const {
  Piece* p = get_piece_at(loc);
  if(!p) {return {};}
  return p->legal_moves(*this);
}

void Board::print_legal_moves(const Location& loc) const {
  if(!is_occupied(loc)) return print();
  std::vector<Location> moves = legal_moves(loc);

  for (int rank = 7; rank >= 0; rank--) {
    std::cout<<rank + 1<<" ";
    for (size_t file = 0; file < 8; ++file) {
      Location current(file, rank);
      Piece* p = squares[file][rank].get();
      std::string symbol(p ? p->symbol() : " ");
      std::string piece_colour(white); 
      std::string square_colour(black_background);
      if(current.get_square_colour() == 'w') {piece_colour = black; square_colour = white_background;}

      if(loc == current) {symbol = p->filled_symbol(); piece_colour = selected;} // Selected piece
      else if(std::find(moves.begin(), moves.end(), current) != moves.end()) {
        if(p) {symbol = p->filled_symbol(); piece_colour = capturable;} // Capturable piece
        else {symbol = "•";} // Legal empty square
      }
      std::cout<<square_colour<<piece_colour<<" "<<symbol<<" "<<reset;
    }
    std::cout<<std::endl;
  }
  std::cout<<"   a  b  c  d  e  f  g  h\n";
}