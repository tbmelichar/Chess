#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

#include <algorithm>

const std::string Board::reset = "\033[0m";            // full reset
const std::string Board::white_background = "\033[47m";
const std::string Board::black_background = "\033[40m";

const std::string Board::white = "\033[37m";            // just white foreground
const std::string Board::black = "\033[30m";            // just black foreground
const std::string Board::selected = "\033[32m";         // just green foreground
const std::string Board::capturable = "\033[31m";       // just red foreground

Board::Board(const bool& set_up) {
  if(!set_up) {return;}
  add_piece(std::make_unique<Rook>(Location("a1"), 'w'));
  add_piece(std::make_unique<Knight>(Location("b1"), 'w'));
  add_piece(std::make_unique<Bishop>(Location("c1"), 'w'));
  add_piece(std::make_unique<Queen>(Location("d1"), 'w'));
  add_piece(std::make_unique<King>(Location("e1"), 'w'));
  add_piece(std::make_unique<Bishop>(Location("f1"), 'w'));
  add_piece(std::make_unique<Knight>(Location("g1"), 'w'));
  add_piece(std::make_unique<Rook>(Location("h1"), 'w'));
  add_piece(std::make_unique<Rook>(Location("a8"), 'b'));
  add_piece(std::make_unique<Knight>(Location("b8"), 'b'));
  add_piece(std::make_unique<Bishop>(Location("c8"), 'b'));
  add_piece(std::make_unique<Queen>(Location("d8"), 'b'));
  add_piece(std::make_unique<King>(Location("e8"), 'b'));
  add_piece(std::make_unique<Bishop>(Location("f8"), 'b'));
  add_piece(std::make_unique<Knight>(Location("g8"), 'b'));
  add_piece(std::make_unique<Rook>(Location("h8"), 'b'));

  for(char file('a'); file <= 'h'; file++) {
    add_piece(std::make_unique<Pawn>(Location(file, '2'), 'w'));
    add_piece(std::make_unique<Pawn>(Location(file, '7'), 'b'));
  }
}

void Board::add_piece(std::unique_ptr<Piece> piece) {
  Location loc = piece->get_location();
  int f = loc.get_file();
  int r = loc.get_rank();
  squares[f][r] = std::move(piece);  // Transfer ownership
}

Piece* Board::get_piece_at(const Location& loc) const {
  if(loc.is_valid()) {return squares[loc.get_file()][loc.get_rank()].get();}
  return nullptr;
}

bool Board::is_occupied(const Location& loc) const {
  return get_piece_at(loc) != nullptr;
}

bool Board::is_friend_at(const Location& loc, const char& my_colour) const {
  Piece* p = get_piece_at(loc);
  return p && p->get_colour() == my_colour;
}

bool Board::is_enemy_at(const Location& loc, const char& my_colour) const {
  Piece* p = get_piece_at(loc);
  return p && p->get_colour() != my_colour;
}

char Board::get_colour_at(const Location& loc) const {
  Piece* p = get_piece_at(loc);
  if(p) {return p->get_colour();}
  return 'n';
}

size_t Board::get_move_number() const {
  return move_number;
}

bool Board::move_piece(const Location& from, const Location& to) {

  int fx = from.get_file(), fy = from.get_rank();
  int tx = to.get_file(), ty = to.get_rank();

  if(!squares[fx][fy]) {return false;}
  //std::cout<<"pllalaa ISSUE HERE\n";
  if(!squares[fx][fy]->can_move_to(to, *this)) {return false;}

  // Capture: just overwrite the destination square
  //std::cout<<"pllalaa\n";
  squares[tx][ty] = std::move(squares[fx][fy]);
  squares[tx][ty]->set_location(to);
  squares[fx][fy].reset();

  return true;
}

void Board::show() const {
  std::cout<<"       "<<((move_number % 2 == 1) ? "White" : "Black")<<" to move"<<std::endl;
  for (int rank = 7; rank >= 0; --rank) {
    std::cout<<rank + 1<<" ";
    for (int file = 0; file < 8; ++file) {
      Location current(file, rank);
      Piece* p = squares[file][rank].get();  // Access raw pointer
      std::string piece_colour(white); 
      std::string square_colour(black_background);
      if(current.get_square_colour() == 'w') {piece_colour = black; square_colour = white_background;}
      
      std::cout<<square_colour<<piece_colour<<" "<<(p ? p->get_symbol() : " ")<<" "<<reset;
    }
    std::cout<<'\n';
  }
  std::cout<<"   a  b  c  d  e  f  g  h\n";
}

bool Board::is_specific_enemy_at(const Location& loc, const char& my_colour, const char& piece_char) const {
  Piece* p = get_piece_at(loc);
  if(!p) {return false;}
  if(p->get_colour() == my_colour) {return false;}
  if(p->get_char() == piece_char) {return true;}
  return false;
}

bool Board::is_specific_enemy_at(const Location& loc, const char& my_colour, const std::string& piece_chars) const {
  Piece* p = get_piece_at(loc);
  if(!p) {return false;}
  if(p->get_colour() == my_colour) {return false;}
  for(size_t i = 0; i < piece_chars.length(); i++) {
    if(p->get_char() == piece_chars[i]) {return true;}
  }
  return false;
}

std::vector<Location> Board::legal_moves(const Location& loc) const {
  Piece* p = get_piece_at(loc);
  if(!p) {return {};}
  return p->legal_moves(*this);
}

void Board::show_legal_moves(const Location& loc) const {
  if(!is_occupied(loc)) return show();
  std::vector<Location> moves = legal_moves(loc);
  std::cout<<"       "<<((move_number % 2 == 1) ? "White" : "Black")<<" to move"<<std::endl;
  for (int rank = 7; rank >= 0; rank--) {
    std::cout<<rank + 1<<" ";
    for (int file = 0; file < 8; ++file) {
      Location current(file, rank);
      Piece* p = squares[file][rank].get();
      std::string symbol(p ? p->get_symbol() : " ");
      std::string piece_colour(white); 
      std::string square_colour(black_background);
      if(current.get_square_colour() == 'w') {piece_colour = black; square_colour = white_background;}

      if(loc == current) {symbol = p->get_filled_symbol(); piece_colour = selected;} // Selected piece
      else if(std::find(moves.begin(), moves.end(), current) != moves.end()) {
        if(p) {symbol = p->get_filled_symbol(); piece_colour = capturable;} // Capturable piece
        else {symbol = "•";} // Legal empty square
      }
      std::cout<<square_colour<<piece_colour<<" "<<symbol<<" "<<reset;
    }
    std::cout<<std::endl;
  }
  std::cout<<"   a  b  c  d  e  f  g  h\n";
}

void Board::print_legal_moves(const Location& loc) const {
  Piece* p = get_piece_at(loc);
  if(!p) {return;}
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      Location test(i, j);
      if(p->can_move_to(test, *this)) {std::cout<<test<<", ";}
    }
  }
}

void Board::set_move_number(const size_t& num) {move_number = num;}

void Board::increment_move_number() {move_number++;}