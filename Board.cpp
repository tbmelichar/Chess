#include "Board.h"


void Board::print() const {
  for (int rank = 7; rank >= 0; --rank) {
    std::cout << rank + 1 << " ";
    for (int file = 0; file < 8; ++file) {
      Piece* p = squares[file][rank].get();  // Access raw pointer
      std::cout << (p ? p->symbol() : '.') << " ";
    }
    std::cout << '\n';
  }
  std::cout << "  a b c d e f g h\n";
}

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

std::vector<Location> Board::legal_moves(const Location& loc) const {
  Piece* p = get_piece_at(loc);
  p->print();
  return p->legal_moves(*this);
}