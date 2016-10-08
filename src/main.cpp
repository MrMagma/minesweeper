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
new {width} {height} {mines} - Starts a new game and specifies the size of the \
board and the number of mines in play\n\
load - Loads a saved game\n\
exit - Exits minesweeper.exe\n\
reveal {row} {column} - Reveals a cell at a specific row and column\n\
";

string instructions = "Use the reveal command to reveal a tile.";

bool shouldExit = false;

void renderState()
{
    int w = state->getWidth(),
        h = state->getHeight();
    char tileState;
    cout << endl;
    
    for (int y = 0; y < w; ++y) {
        cout << endl;
        for (int x = 0; x < h; ++x) {
            tileState = state->getTileState(x, y);
            cout << " ";
            switch (tileState) {
                // Unrevealed
                case -1:
                case -2:
                    cout << "*";
                    break;
                // Revealed mine
                case 9:
                    cout << "M";
                    break;
                // Revealed not mine
                default:
                    cout << +tileState;
            }
        }
        cout << endl;
    }
    
    switch (state->getVictoryState()) {
        case 1:
            cout << endl << "You won!" << endl;
            break;
        case -1:
            cout << endl << "You lost..." << endl;
            break;
        case 0:
            cout << endl << instructions << endl;
    }
}

void giveHelp(stringstream* args)
{
    cout << help << endl;
}

void newGame(stringstream* args)
{
    unsigned int width, height, mines;
    *args >> width >> height >> mines;
    
    state = new GameState(width, height, mines);
    
    cout << width << "x" << height << " game initialized with " << mines << " mines";
    renderState();
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

void revealCell(stringstream* args)
{
    if (state) {
        int x, y;
        *args >> x >> y;
        state->revealTile(x - 1, y - 1);
        renderState();
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
    view.addCommand("exit", &exitGame);
    view.addCommand("reveal", &revealCell);
    
    while (!shouldExit) {
        view.readInput(out);
    }
    
    return 0;
}
