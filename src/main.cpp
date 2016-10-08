#include <iostream>
#include <string>
#include "GameState.hpp"
#include "GameView.hpp"
#include <sstream>

using namespace std;

GameState* state;

string out = "\nType a command and press enter when you're done.\n\
Use the \"help\" command to see the list of commands.";

string help = "HELP\nAvailable commands are:\n\
help - Shows information about available commands\n\
new - Starts a new game\n\
load - Loads a saved game\n\
exit - Exits minesweeper.exe\n\
";

bool shouldExit = false;

void giveHelp(stringstream* args)
{
    cout << help << endl;
}

void newGame(stringstream* args)
{
    cout << "Playing games is not implemented yet. Please come back later." << endl;
}

void loadGame(stringstream* args)
{
    cout << "Loading games is not implemented yet. Please come back later." << endl;
}

void exitGame(stringstream* args)
{
    cout << "Exiting minesweeper.exe . . . " << endl;
    shouldExit = true;
}

void makeMove(stringstream* args)
{
    if (state) {
        
    } else {
        cout << "You have to start a game before making a move, silly! " << endl;
    }
}

int main(int, char**)
{
    cout << "Welcome to minesweeper.exe!" << endl;
    GameView view;
    view.addCommand("help", &giveHelp);
    view.addCommand("new", &newGame);
    view.addCommand("load", &loadGame);
    view.addCommand("move", &makeMove);
    
    while (!shouldExit) {
        view.readInput(out);
    }
    
    return 0;
}
