#ifndef BATTLESHIP__BOARD_H_
#define BATTLESHIP__BOARD_H_

#include "game.h"
#include "board.h"

void print_board(std::vector<std::vector<char>> board, int numRows, int numCols);
char setChoice();
void add_ship_to_board(class Ships& ship, class Player* player, int numRows, int numCols);
bool is_stream_empty(std::istream& in);

#endif //BATTLESHIP__BOARD_H_