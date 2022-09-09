#ifndef BATTLESHIP__GAME_H_
#define BATTLESHIP__GAME_H_
#include <string>
#include <vector>
#include <iostream>
#include <string>
#include "board.h"

void play_game(char *argv[]);

class Ships {
public:
    // ship name and size
    //Ships(char name, int length): name(name), length(length) {}
    Ships(): name(0), length(0) {};
    void setName (char a) {
        name = a;
    }
    void setLength (int b) {
        length = b;
    }
    char getName() {
        return name;
    }
    int getLength() {
        return length;
    }
private:
    char name ;
    int length ;

};
///////////////////////////////////////////////////////////
class Player { // each player has access to their own individual board with all the ships included
public:

    void setName(std::string a) {
        std::cout << a;
        std::cin >> name;
    }

    std::string getName() {
        return name;
    }
    void setShips(std::vector<Ships> shipList) { // to include ship list into player
        this->shipList = shipList;
    }

    void build_board(int numRows, int numCols) {
        board = std::vector<std::vector<char>>(numRows, std::vector<char>(numRows, '*'));

        print_board(board, numRows, numCols);

        for (int i = 0; i < shipList.size(); i++) {
            add_ship_to_board(shipList.at(i), this, numRows, numCols);
            print_board(board, numRows, numCols);
        }
    }

    std::vector<std::vector<char>>& get_board() {
        return board;
    }

    char check_board(int i, int j) {
        char found;
        found = board[i][j];
        return found;
    }

    void edit_board(int i, int j, char a) {
        board[i][j] = a;
    }

private:
    std::string name;
    std::vector<std::vector<char>> board;
    std::vector<Ships> shipList;

};
/////////////////////////////////////////////////////////
class Round {
public:

    void disp_board(Player &p1, Player &p2, int numRows, int numCols) {
        std::vector<std::vector<char>> boardP = p1.get_board();
        std::vector<std::vector<char>> boardF = p2.get_board();
        std::string name = p1.getName();
        int i, n;

        //FIRING BOARD AKA ENEMY BOARD W/O LETTERS OTHER THAN X and O
        std::cout << name << "'s Firing Board" << std::endl;
        std::cout << "  ";
        for(n = 0; n < numCols; n++) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
        for(i = 0; i < numRows; i++) {
            std::cout << i << " ";
            for (n = 0; n < numCols; n++) {
                if (boardF[i][n] != 'X' && boardF[i][n] != 'O' && boardF[i][n] != '*') {
                    std::cout << "* ";
                } else {
                    std::cout << boardF[i][n] << " ";
                }
            }
            std::cout << std::endl;
        }

        //PLACEMENT BOARD AKA OWN PLAYER'S BOARD EVERYTHING
        std::cout << std::endl << std::endl << name << "'s Placement Board" << std::endl;
        std::cout << "  ";
        for(n = 0; n < numCols; n++) {
            std::cout << n << " ";
        }
        std::cout << std::endl;
        for(i = 0; i < numRows; i++) {
            std::cout << i << " ";
            for (n = 0; n < numCols; n++) {
                std::cout << boardP[i][n] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool check_game(Player &p, int numRows, int numCols) {
        std::vector<std::vector<char>> board = p.get_board();
        int answer = 0;
        for(int i = 0; i < numRows; i++) {
            for (int n = 0; n < numCols; n++) {
                if (board[i][n] != 'X' && board[i][n] != 'O' && board[i][n] != '*') {
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

private:
};

#endif //BATTLESHIP__GAME_H_
