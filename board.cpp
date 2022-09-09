#include "game.h"
#include "board.h"
#include <iostream>
#include <cctype>
#include <string>
#include <sstream>
#include <algorithm>

bool is_stream_empty(std::istream& in) {
    std::string leftovers;
    in >> leftovers;
    return not in; //failing to read means that the stream is empty
}

void print_board(std::vector<std::vector<char>> board, int numRows, int numCols) {
    //  function that prints out the board after creating board
    int i, n;
    std::cout << "  ";
    for(n = 0; n < numRows; n++) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    for(i = 0; i < numCols; i++) {
        std::cout << i << " ";
        for (n = 0; n < numRows; n++) {
            std::cout << board[i][n] << " ";
        }
        std::cout << std::endl;
    }
}

char setChoice() {
    // function made to settle whether the ship will be placed horizontally or vertically but only takes two letters from user input
    // rejects any input that is not h or v (uppercase/lowercase)
    std::string c;
    std::cout << "Enter h for horizontal or v for vertical" << std::endl;
    std::cout << "Your choice: ";
    char choice;
    std::cin>>std::ws;
    std::getline(std::cin, c);
    c.erase(std::remove_if(c.begin(), c.end(), ::isspace), c.end());
    if (c.length() > 1) {
        choice = 'F';
    } else {
        choice = c[0];
    }
    return choice;
}


void add_ship_to_board(Ships& ship, Player* player, int numRows, int numCols) {
    // function is accessible for every player -> each player holds an individual board with all the ships available for placement
    std::vector<std::vector<char>>& board = player->get_board();
    std::string line;
    int placement, x, y;
    char choice;
    bool case1;
    do {
        std::cout << player->getName() << ", do you want to place " << ship.getName() << " horizontally or vertically?"
                  << std::endl;
        choice = setChoice();
        if (choice != 'v' && choice != 'V' && choice != 'H' && choice != 'h') {
            case1 = false; // continue
        } else {
            case1 = true;  // will repeat until user input is correct
        }

        if (case1 == true) {
            if (choice == 'v' || choice == 'V') {
                placement = 1;
            }
            if (choice == 'h' || choice == 'H') {
                placement = 2;
            }
            bool case2 = true;
            std::cout << player->getName() << ", enter the row and column you want to place " << ship.getName();
            std::cout << ", which is " << ship.getLength() << " long, at with a space in between row and col: ";
            std::getline(std::cin, line);
            std::stringstream line2parse(line);
            line2parse >> x >> y;
            if(line2parse && is_stream_empty(line2parse)) {
                case2 = true;
            }
            else {
                case2 = false;  // checks whether the boundaries from user input are numbers -> will continue to ask if invalid
            }
            if (!case2) {
                case1 = false;
            }
            else {
                case1 = true;
            }
        }
        bool case4 = true;
        bool case5 = true;
        bool case6 = true;
        if (case1 == true) {
            if (x < 0 || x > numRows) { // checks if out of bounds
                case4 = false;
            }
            if (y < 0 || y > numCols) {
                case4 = false;
            }
            if ((x + ship.getLength() - 1) > numRows || ((y + ship.getLength() - 1) > numCols)) {
                case4 = false;
            }
            if (case4 == false) {
                case1 = false;
            }
            if (case1 == true) {
                if (board[x][y] != '*') { // checks if board is not taken in all spaces 
                    case5 = false;
                }
                if (placement == 1) {
                    for (int k = 0; k < ship.getLength(); ++k) {
                        if (board[x + k][y] != '*') {
                            case6 = false;
                        }
                    }
                }
                if (placement == 2) {
                    for (int k = 0; k < ship.getLength(); ++k) {
                        if (board[x][y + k] != '*') {
                            case6 = false;
                        }
                    }
                }

                if (case4 && case5 && case6) {
                    case1 = true;
                    if (placement == 1) {
                        for (int k = 0; k < ship.getLength(); ++k) {
                            board[x + k][y] = ship.getName();
                        }
                    }
                    if (placement == 2) {
                        for (int k = 0; k < ship.getLength(); ++k) {
                            board[x][y + k] = ship.getName();
                        }
                    }
                } else {
                    case1 = false;
                }
            }
        }
    } while (!case1);  // will continue to ask for valid placement until user input is valid
}
