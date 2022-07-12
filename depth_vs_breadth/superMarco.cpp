// B99292359FFD910ED13A7E6C7F9705B8742F0D79
//  main.cpp
//  p1-countess
//
//  Created by Mathieu Noguier on 2/3/21.
//
//
#include <iostream>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <string>
using namespace std;

//cmd line input / get opt
//read in
// cin resize cin
// 3d vector
// deque
// make struct
//search algoithm
//output
char whatSym = '\n';
bool stackMode = 0;


struct Tile {
    char last = '?';
    char symbol = '.';
    bool isDiscovered = 0;
    bool isValid = 1;
    
};
Tile outMap;

struct Location {
    uint32_t room = 0;
    uint32_t row = 0;
    uint32_t col = 0;
    
};
Location loc;
Location out;
Location start;
Location cnts;
Location check;

struct Squares {
    uint32_t numRooms = 0;
    uint32_t size = 0;
    uint32_t room = 0;
    uint32_t row = 0;
    uint32_t col = 0;
    uint32_t digit = 0;
    //uint32_t lineCount = 0;
    uint32_t numDisco = 0;
    
    vector<vector<vector<Tile>>> map;
    
    deque<Location> searchCon;
    deque<Tile> curLoc;
    deque<Location> bTrace;
    
    char modeType = '\0';
    char outType = '\0';
    bool stackMode = 0;
    bool isSolve = 0;
    bool noSolution = 0;
    void readData();
    void findRoute();
    void printMap();
    void getMode(int argc, char * argv[]);
    bool isDigit(char whatSym);
    
};
//Squares mode;




bool Squares::isDigit(char whatSym) {
    int temp = 0;
    digit = static_cast<uint32_t>(whatSym - '0');
    temp = static_cast<int>(digit);
    if (isdigit(temp)) {
        return 1;
    }
    else {
        return 0;
    }
}
void Squares::readData() {
    //Squares squares;
    char temp = '\n';
    string junk;
    string fileIn;
    Tile tile;
    
    
    // Read in the first number to find the mode
    
    // Also consume the new line after the integer.
    std::cin >> modeType >> std::ws;
    std::cin >> numRooms >> std::ws;
    // check valid amount rooms
    if (numRooms > 10) {
        cerr << "Invalid room number\n";
        exit(1);
    }
    std::cin >> size >> std::ws;
    // check valid size
    
    
    map.resize(numRooms, vector<vector<Tile>>(size,vector<Tile>(size)));
    
    if( modeType == 'L') {
        while ( cin >> temp) {
            if (temp == '/'){
                getline(cin, junk, '\n');
            }
            else {
                cin >> room >> temp >> row >> temp >> col >> temp >> whatSym >> temp;
                if (row >= size) {
                    cerr << "Invalid row number\n";
                    exit(1);
                }
                if (col >= size) {
                    cerr << "Invalid column number\n";
                    exit(1);
                }
                if (!isdigit(whatSym)) {
                    if (whatSym != '#' && whatSym != '.' && whatSym != '!' && whatSym != 'S' && whatSym != 'C' && whatSym != '.') {
                        cerr << "Unknown map character\n";
                        exit(1);
                    }
                }
                tile.symbol = whatSym;
                tile.isValid = true;
                tile.isDiscovered = 0;
                
                if (whatSym == '#') {
                    tile.isValid = 0;
                }
                if (whatSym == '!') {
                    tile.isValid = 0;
                }
                /**
                 if(isdigit(whatSym)) {
                 digit = static_cast<uint32_t>(whatSym - '0');
                 if (digit >= numRooms) {
                 tile.isValid = 0;
                 }
                 }
                 */
                if ( whatSym == 'S') {
                    tile.isDiscovered = 1;
                    numDisco++;
                    searchCon.push_back({room,row,col});
                    start = searchCon.back();
                }
                map[room][row][col] = tile;
                //lineCount++;
                
            }
        }//while
        
    }
    else {
        while (getline(cin,fileIn)) {
            if (fileIn.at(0) == '/') {
                
            }
            else {
                for(uint32_t i = 0; i < size; ++i) {
                    col = i;
                    whatSym = fileIn.at(i);
                    tile.symbol = whatSym;
                    tile.isValid = true;
                    tile.isDiscovered = 0;
                    if (whatSym == '#') {
                        tile.isValid = 0;
                    }
                    if (whatSym == '!') {
                        tile.isValid = 0;
                    }
                    
                    if (!isdigit(whatSym)) {
                        if (whatSym != '#' && whatSym != '.' && whatSym != '!' && whatSym != 'S' && whatSym != 'C' && whatSym != '.') {
                            exit(1);
                        }
                    }
                    if ( whatSym == 'S') {
                        tile.isDiscovered = 1;
                        numDisco++;
                        searchCon.push_back({room,row,col});
                        start = searchCon.back();
                        
                    }
                    if ( whatSym == 'C') {
                        // countess = map[room][row][col];
                        
                    }
                    map[room][row][col] = tile;
                }
                row++;
                if (row == size) {
                    room++;
                    row = 0;
                }
            }
        }
    }//Map
    row = 0;
    room = 0;
    col = 0;
}
void Squares::findRoute () {
    while (!searchCon.empty()) {
        if (stackMode) {
            loc = searchCon.back();
            searchCon.pop_back();
        }
        else {
            loc = searchCon.front();
            searchCon.pop_front();
        }
        
        if (isdigit(map[loc.room][loc.row][loc.col].symbol)){
            room = static_cast<uint32_t>(map[loc.room][loc.row][loc.col].symbol - '0');
            if (room < numRooms) {
                room = loc.room;
                loc.room = static_cast<uint32_t>(map[loc.room][loc.row][loc.col].symbol - '0');
                if(map[loc.room][loc.row][loc.col].isValid
                   && !map[loc.room][loc.row][loc.col].isDiscovered) {
                    map[loc.room][loc.row][loc.col].isDiscovered = 1;
                    numDisco++;
                    map[loc.room][loc.row][loc.col].last = static_cast<char>('0' + room);
                    
                    searchCon.push_back({loc.room,loc.row,loc.col});
                    if(map[loc.room][loc.row][loc.col].symbol == 'C') {
                        map[loc.room][loc.row][loc.col].last = static_cast<char>('0' + room);
                        cnts = loc;
                        check = loc;
                        break;
                    }
                }
            }
            else {
                map[loc.room][loc.row][loc.col].isDiscovered = 1;
            }
        }//check if pipe
        else { //NESW
            if(loc.row > 0) {
                if(map[loc.room][(loc.row - 1)][loc.col].isValid
                   && !map[loc.room][loc.row - 1][loc.col].isDiscovered) {
                    searchCon.push_back({loc.room, loc.row - 1, loc.col});
                    map[loc.room][loc.row - 1][loc.col].isDiscovered = 1;
                    numDisco++;
                    map[loc.room][loc.row - 1][loc.col].last = 'n';
                    //map[loc.room][loc.row][loc.col].last = 'n';
                    if(map[loc.room][loc.row - 1][loc.col].symbol == 'C') {
                        map[loc.room][loc.row - 1][loc.col].last = 'n';
                        cnts = searchCon.back();
                        check = searchCon.back();
                        break;
                    }
                }
            }//N
            if (loc.col < size - 1) {
                if(map[loc.room][loc.row][loc.col + 1].isValid
                   && !map[loc.room][loc.row][loc.col + 1].isDiscovered) {
                    searchCon.push_back({loc.room, loc.row, loc.col + 1});
                    map[loc.room][loc.row][loc.col + 1].isDiscovered = 1;
                    numDisco++;
                    map[loc.room][loc.row][loc.col + 1].last = 'e';
                    //map[loc.room][loc.row][loc.col].last = 'e';
                    if(map[loc.room][loc.row][loc.col + 1].symbol == 'C') {
                        map[loc.room][loc.row][loc.col + 1].last = 'e';
                        cnts = searchCon.back();
                        check = searchCon.back();
                        break;
                    }
                }
            }//E
            if (loc.row < size - 1){
                if(map[loc.room][loc.row + 1][loc.col].isValid
                   && !map[loc.room][loc.row + 1][loc.col].isDiscovered) {
                    searchCon.push_back({loc.room, loc.row + 1, loc.col});
                    map[loc.room][loc.row + 1][loc.col].isDiscovered = 1;
                    numDisco++;
                    map[loc.room][loc.row + 1][loc.col].last = 's';
                    //map[loc.room][loc.row][loc.col].last = 's';
                    if(map[loc.room][loc.row + 1][loc.col].symbol == 'C') {
                        map[loc.room][loc.row + 1][loc.col].last = 's';
                        cnts = searchCon.back();
                        check = searchCon.back();
                        break;
                    }
                }
            }//S
            if (loc.col > 0){
                if(map[loc.room][loc.row][loc.col - 1].isValid && !map[loc.room][loc.row][loc.col - 1].isDiscovered) {
                    searchCon.push_back({loc.room, loc.row, loc.col - 1});
                    map[loc.room][loc.row][loc.col - 1].isDiscovered = 1;
                    numDisco++;
                    map[loc.room][loc.row][loc.col - 1].last = 'w';
                    //map[loc.room][loc.row][loc.col].last = 'w';
                    if(map[loc.room][loc.row][loc.col - 1].symbol == 'C') {
                        map[loc.room][loc.row][loc.col - 1].last = 'w';
                        cnts = searchCon.back();
                        check = searchCon.back();
                        break;
                    }
                }
            }//W
        }
    }
    
}
void Squares::printMap(){
    if (searchCon.empty()) {
        cout << "No solution, " << numDisco << " tiles discovered.\n";
        exit(0);
    }
    
    
    
    while( map[cnts.room][cnts.row][cnts.col].last == 'n' || map[cnts.room][cnts.row][cnts.col].last == 'e' || map[cnts.room][cnts.row][cnts.col].last == 's' || map[cnts.room][cnts.row][cnts.col].last == 'w' || isdigit(map[cnts.room][cnts.row][cnts.col].last)) {
        //while(map[cnts.room][cnts.row][cnts.col].symbol != 'S') {
        
        if ( map[cnts.room][cnts.row][cnts.col].last == 'n' ){
            bTrace.push_back({cnts.room,cnts.row + 1,cnts.col});
            map[cnts.room][cnts.row + 1][cnts.col].symbol = 'n';
            cnts = bTrace.back();
            
        }
        else if (map[cnts.room][cnts.row][cnts.col].last == 'e' ){
            bTrace.push_back({cnts.room,cnts.row,cnts.col - 1});
            map[cnts.room][cnts.row][cnts.col - 1].symbol = 'e';
            cnts = bTrace.back();
        }
        else if (map[cnts.room][cnts.row][cnts.col].last == 's' ){
            bTrace.push_back({cnts.room,cnts.row - 1,cnts.col});
            map[cnts.room][cnts.row - 1][cnts.col].symbol = 's';
            cnts = bTrace.back();
        }
        else if (map[cnts.room][cnts.row][cnts.col].last == 'w' ){
            bTrace.push_back({cnts.room,cnts.row,cnts.col + 1});
            map[cnts.room][cnts.row][cnts.col + 1].symbol = 'w';
            cnts = bTrace.back();
        }
        else if (isdigit(map[cnts.room][cnts.row][cnts.col].last)){
            cnts.room = static_cast<uint32_t>(map[cnts.room][cnts.row][cnts.col].last - '0');
            bTrace.push_back({cnts.room,cnts.row,cnts.col});
            map[cnts.room][cnts.row][cnts.col].symbol = 'p';
            cnts = bTrace.back();
        }
        //if (map[cnts.room][cnts.row][cnts.col].symbol == 'S') {
        // break;
        //}
    }
    
    
    
    // M
    if (outType == 'M') {
        //check = bTrace.front();
        /**
         while (!bTrace.empty()) {
         out = bTrace.back();
         map[out.room][out.row][out.col].symbol = map[out.room][out.row][out.col].last;
         bTrace.pop_back();
         }
         */
        // map[countess.room][countess.row][countess.col].symbol = 'C';
        //map[check.room][check.row][check.col].symbol = 'C';
        cout << "Start in room " << start.room << ", row " << start.row << ", column " << start.col << "\n";
        
        for ( room = 0; room < numRooms; ++room) {
            cout << "//castle room " << room <<"\n";
            for (row = 0 ; row < size; ++row) {
                for (col = 0; col < size; ++col) {
                    cout << map[room][row][col].symbol;
                }
                cout << "\n";
            }
        }
    }
    //L
    else {
        cout << "Path taken: \n";
        while (!bTrace.empty()) {
            out = bTrace.back();
            cout << '(' << out.room << ',' << out. row <<  ','  << out. col << ',' << map[out.room][out.row][out.col].symbol << ")\n";
            bTrace.pop_back();
        }
    }// list output
    
    
}
void printHelp(char *argv[]) {
    cout << "Usage: " << argv[0] << " [-s | - q | -o [M|L] |-h" << endl;
    cout << "This program looks for possible paths to a endpoint," << endl;
    cout << "using stack or queue mode to search," << endl;
    cout << "then prints results." << endl;
} // printHelp()


// Finish this function, look for the individual TODO comments internally.
// Process the command line; the only thing we need to return is the mode
// when the user specifies the -m/--mode option.
// For p1, make class and getMode a memeber variable
// ie // void return type getMode
void Squares::getMode(int argc, char * argv[]) {
    bool modeSpecified = false;
    string mode;
    uint32_t errCheck = 0;
    // make class variable ^^
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        // ./project0 -m nosize
        // ./project0 --help
        // array of structures
        { "stack", no_argument, nullptr, 's' },
        { "queue", no_argument, nullptr, 'q' },
        { "output", required_argument, nullptr, 'o' },
        { "help", no_argument,       nullptr, 'h' },
        { nullptr, 0,                nullptr, '\0'}
        // always last ^^^^^
    };
    
    // Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "sqo:h", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp(argv);
                exit(0);
                break;
                
            case 's':
                stackMode = 1;
                errCheck++;
                modeSpecified = false;
                break;
                
            case 'q':
                stackMode = 0;
                errCheck++;
                modeSpecified = false;
                break;
            case 'o':
                outType = *optarg;
                if (outType != 'M' && outType != 'L') {
                    outType = 'M';
                    
                } // if
                modeSpecified = true;
                break;
                
            default:
                cerr << "Unknown command line option" << endl;
                exit(1);
                
        } // switch
    } // while
    
    if (!modeSpecified) {
        cerr << "Error: no mode specified" << endl;
        exit(1);
    } // if
    
    if (errCheck > 1) {
        cerr << "Stack or queue can only be specified once\n";
        exit(1);
    }
} // getMode()


int main(int argc, char * argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    Squares s;
    s.getMode(argc, argv);
    s.readData();
    s.findRoute();
    s.printMap();
    
    return 0;
}
