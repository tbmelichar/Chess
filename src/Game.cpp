#include "Game.h"
#include <iostream>
#include <string>

void clear_last_lines(int n) {
  for(int i = 0; i < n; ++i) {
    std::cout<<"\033[A\033[2K";
  }
}

bool is_valid_square(const std::string& s) {
  return s.size() == 2 &&
         s[0] >= 'a' && s[0] <= 'h' &&
         s[1] >= '1' && s[1] <= '8';
}

void Game::show_board() const {
  board.show();
}


void Game::user_move() {
  std::string from_str, to_str;
  Location from, to;

  char user_colour = board.get_move_number() % 2 == 1 ? 'w' : 'b';

  // Phase 1: Choose piece to move
  std::cout<<std::endl;
  while(true) {
    std::cout<<"Select a piece to move: ";
    std::cin>>from_str;

    if(from_str.size() != 2) {
      std::cout<<"\033[A\033[2K\033[A\033[2KInvalid square\n";
      continue;
    }

    from = Location(from_str);


    if(!from.is_valid()) {
      std::cout<<"\033[A\033[2K\033[A\033[2KInvalid square\n";
      continue;
    }

    if(!board.is_friend_at(from, user_colour)) {
      std::cout<<"\033[A\033[2K\033[A\033[2KNo friendly piece at "<<from_str<<"\n";
      continue;
    }

    if(board.get_piece_at(from)->legal_moves(board).empty()) {
      std::cout<<"\033[A\033[2K\033[A\033[2KNo legal moves from "<<from_str<<"\n";
      continue;
    }

    break; // valid piece selected
  }
  std::cin.clear();
  std::cin.ignore(10000, '\n');
  clear_last_lines(12);
  board.show_legal_moves(from);

  // Phase 2: Choose destination
  std::cout<<std::endl;
  while(true) {
    std::cout<<"Select your move: ";
    std::cin>>to_str;

    if(!is_valid_square(to_str)) {
      std::cout<<"\033[A\033[2K\033[A\033[2KInvalid square\n";
      continue;
    }

    to = Location(to_str);
    if(board.move_piece(from, to)) break;
    //if(board.move_piece(Location("e2"), Location("e4"))) break;

    std::cout<<"\033[A\033[2K\033[A\033[2KIllegal move\n";
  }
  board.increment_move_number();
  clear_last_lines(12);
  board.show();
}