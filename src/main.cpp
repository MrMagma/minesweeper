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
save {file name} - Saves the current game\n\
saves - Lists all saves in the current directory\n\
load - Loads a saved game\n\
exit - Exits minesweeper.exe\n\
reveal {row} {column} - Reveals a cell at a specific row and column\n\
";

bool shouldExit = false;

void renderState()
{
    int w = state->getWidth(),
        h = state->getHeight();
    for (int x = 0; x < w; ++x) {
        cout << endl;
        for (int y = 0; y < h; ++y) {
            if (!state->getTileRevealed(x, y)) {
                cout << "*"; 
            } else {
                cout << +state->getTileAdjacent(x, y);
            }
        }
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

void saveGame(stringstream* args)
{
    cout << "Saving games is not implemented yet. Please come back later." << endl;
}

void listSaves(stringstream* args)
{
    cout << "Listing saves is useless if you can't make them in the first place!" << endl;
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
        state->revealTile(x, y);
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
    view.addCommand("save", &saveGame);
    view.addCommand("saves", &listSaves);
    view.addCommand("exit", &exitGame);
    view.addCommand("reveal", &revealCell);
    
    while (!shouldExit) {
        view.readInput(out);
    }
    
    return 0;
}
