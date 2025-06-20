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
  add_piece(std::make_unique<Bishop>(Location("f1"), 'w'));
  add_piece(std::make_unique<Knight>(Location("g1"), 'w'));
  add_piece(std::make_unique<Rook>(Location("h1"), 'w'));
  add_piece(std::make_unique<Rook>(Location("a8"), 'b'));
  add_piece(std::make_unique<Knight>(Location("b8"), 'b'));
  add_piece(std::make_unique<Bishop>(Location("c8"), 'b'));
  add_piece(std::make_unique<Queen>(Location("d8"), 'b'));
  add_piece(std::make_unique<Bishop>(Location("f8"), 'b'));
  add_piece(std::make_unique<Knight>(Location("g8"), 'b'));
  add_piece(std::make_unique<Rook>(Location("h8"), 'b'));

  for(char file('a'); file <= 'h'; file++) {
    add_piece(std::make_unique<Pawn>(Location(file, '2'), 'w'));
    add_piece(std::make_unique<Pawn>(Location(file, '7'), 'b'));
  }
  
  std::unique_ptr<King> wk = std::make_unique<King>(Location("e1"), 'w');
  white_king = wk.get();
  add_piece(std::move(wk));

  std::unique_ptr<King> bk = std::make_unique<King>(Location("e8"), 'b');
  black_king = bk.get();
  add_piece(std::move(bk));
}

Board::Board(const Board& other) : move_number(other.move_number) {
  for (int file = 0; file < 8; ++file) {
    for (int rank = 0; rank < 8; ++rank) {
      if (other.squares[file][rank]) {
        squares[file][rank] = other.squares[file][rank]->clone();
      } else {
        squares[file][rank] = nullptr;
      }
    }
  }
  int wk_file = other.white_king->get_location().get_file();
  int wk_rank = other.white_king->get_location().get_rank();
  white_king = static_cast<King*>(squares[wk_file][wk_rank].get());

  int bk_file = other.black_king->get_location().get_file();
  int bk_rank = other.black_king->get_location().get_rank();
  black_king = static_cast<King*>(squares[bk_file][bk_rank].get());
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

bool Board::would_cause_check(const Location& from, const Location& to) const {
  int fx = from.get_file(), fy = from.get_rank();
  int tx = to.get_file(), ty = to.get_rank();
  Board future(*this);
  future.squares[tx][ty] = std::move(future.squares[fx][fy]);
  future.squares[tx][ty]->set_location(to);
  future.squares[fx][fy].reset();

  if(move_number % 2 == 1) {
    if(future.white_king->in_check(future)) {return true;}
  }
  else if(future.black_king->in_check(future)) {return true;}
  return false;
}

bool Board::move_piece(const Location& from, const Location& to) {

  int fx = from.get_file(), fy = from.get_rank();
  int tx = to.get_file(), ty = to.get_rank();

  if(!squares[fx][fy]) {return false;}
  if(!squares[fx][fy]->can_move_to(to, *this)) {return false;}

  // Capture: just overwrite the destination square
  squares[tx][ty] = std::move(squares[fx][fy]);
  squares[tx][ty]->set_location(to);
  squares[fx][fy].reset();

  return true;
}

void Board::show() const {

  bool white_to_move = (move_number % 2 == 1);
  std::cout<<"       "<<(white_to_move ? "White" : "Black")<<" to move"<<std::endl;

  if(white_to_move) {
    for(int rank = 7; rank >= 0; rank--) {
      std::cout<<rank + 1<<" ";
      for(int file = 0; file <= 7; file++) {
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
  } else {
    for(int rank = 0; rank <= 7; rank++) {
      std::cout<<rank + 1<<" ";
      for(int file = 7; file >= 0; file--) {
        Location current(file, rank);
        Piece* p = squares[file][rank].get();  // Access raw pointer
        std::string piece_colour(white); 
        std::string square_colour(black_background);
        if(current.get_square_colour() == 'w') {piece_colour = black; square_colour = white_background;}
        
        std::cout<<square_colour<<piece_colour<<" "<<(p ? p->get_symbol() : " ")<<" "<<reset;
      }
      std::cout<<'\n';
    }
    std::cout<<"   h  g  f  e  d  c  b  a\n";
  }
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

  bool white_to_move = (move_number % 2 == 1);
  std::cout<<"       "<<(white_to_move ? "White" : "Black")<<" to move"<<std::endl;

  if(white_to_move) {
    for(int rank = 7; rank >= 0; rank--) {
      std::cout<<rank + 1<<" ";
      for(int file = 0; file <= 7; file++) {
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
  } else {
    for(int rank = 0; rank <= 7; rank++) {
      std::cout<<rank + 1<<" ";
      for(int file = 7; file >= 0; file--) {
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
    std::cout<<"   h  g  f  e  d  c  b  a\n";
  }
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