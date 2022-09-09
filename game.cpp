#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include "game.h"
#include "input.h"
#include "board.h"
bool ascii_sort(Ships a, Ships b) { return a.getName() < b.getName(); }

bool check_board(Player &p, char check) {
    // functions that checks whether there was a ship destroyed
    std::vector<std::vector<char>> board = p.get_board();
    int answer = 0;
    for(int i = 0; i < board.size(); i++) {
        for (int n = 0; n < board.at(0).size(); n++) {
            if (board[i][n] == check) {
                answer += 1;
            }
        }
    }
    if (answer != 0) {
        return false;
    } else {
        return true;
    }
}

void turn(Player &fire, Player &shot, int numRows, int numCols) {
    //function used per player as a firing board 
    std::string firing = fire.getName();
    std::string shotAt = shot.getName();
    std::vector<std::vector<char>>& board = shot.get_board();
    std::string line;
    char check;
    int x, y;
    bool case1 = true;
    bool destroy;
    do {
        Round curr;
        curr.disp_board(fire, shot, numRows, numCols);
        bool case2 = false;
        do {
            std::cout << firing << ", where would you like to fire?" << std::endl
                      << "Enter your attack coordinate in the form row col: ";
            std::getline(std::cin, line);
            std::stringstream line2parse(line);
            line2parse >> x >> y;
            if(line2parse && is_stream_empty(line2parse)) {
                case2 = true;
            }
            else {
                case2 = false;
            }
            if (case2) {
                case1 = true;
            }
        } while (!case2);

        if (case1 == true) { // valid boundaries check
            if ((x > numRows - 1) || (y > numCols - 1) ||
                (x < 0) || (y < 0)) {
                case1 = false;
            }
        }
        if (case1 == true) {
            if (board[x][y] == 'X' || board[x][y] == 'O') {
                case1 = false;
            }
        }

        if(case1 == true) {
            check = shot.check_board(x, y);  // calls shot checker(check_board) and checks if a whole ship is gone
            if (check == '*') {
                shot.edit_board(x, y, 'O');
                curr.disp_board(fire, shot, numRows, numCols);
                std::cout << "Missed." << std::endl << std::endl;
            } else {
                shot.edit_board(x, y, 'X');
                curr.disp_board(fire, shot, numRows, numCols);
                std::cout << firing << " hit " << shotAt << "'s " << check << "!";
                destroy = check_board(shot, check);
                if (destroy) {
                    std::cout << std::endl << firing << " destroyed " << shotAt << "'s " << check << "!" << std::endl;
                }
                std::cout << std::endl;
            }
        }
    } while (!case1);
}


void play_game(char *argv[]) {
    int numCols, numRows;
    Player pOne;
    Player pTwo;
    std::vector<Ships> shipList;
    read_file(argv, numCols, numRows, shipList);
    sort(shipList.begin(), shipList.end(), ascii_sort);
    // set up cols, rows, ship list, everything set up to build board and set up

    pOne.setShips(shipList);
    pOne.setName("Player 1 please enter your name: ");
    pOne.build_board(numCols, numRows);

    pTwo.setShips(shipList);
    pTwo.setName("Player 2 please enter your name: ");
    pTwo.build_board(numCols, numRows);

    bool gameState;
    Round curr;
    do {
        //pTwo.fire (function that takes in input and edits the pTwo board to have an X or O at the desired coordinates, prints if hit or missed
        turn(pOne, pTwo, numRows, numCols);
        gameState = curr.check_game(pTwo, numRows,
                                    numCols); // checks pTwo's board to see if there are any ships left (if not exits)
        if (!gameState) {
            turn(pTwo, pOne, numRows, numCols);
            gameState = curr.check_game(pOne, numRows,
                                        numCols); // checks pOne's board to see if there are any ships left
        }

    } while (!gameState); // exits if pOne's board is dead
    bool win_1 = curr.check_game(pTwo, numRows, numCols);
    bool win_2 = curr.check_game(pOne, numRows, numCols);
    if (win_1) {
        std::cout << pOne.getName() << " won the game!" << std::endl;
    }
    if (win_2) {
        std::cout << pTwo.getName() << " won the game!" << std::endl;
    }

    //Implement curr.check_game again, check both boards and if true, print that player's name into winning, do for both (brute force)
}
