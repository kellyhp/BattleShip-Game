#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

#include "game.h"
#include "input.h"
#include "board.h"

void read_file(char *argv[], int &numCols, int &numRows, std::vector<Ships> &shipList) {
    std::string filename = argv[1];
    std::ifstream myFile;
    myFile.open(filename);

    int numShips;
    myFile >> numRows >> numCols >> numShips;

    shipList.resize(numShips, Ships());

    for (int i = 0; i < numShips; i++) {
        char a;
        int b;
        myFile >> a >> b;
        shipList[i].setLength(b);
        shipList[i].setName(a);
    }

}