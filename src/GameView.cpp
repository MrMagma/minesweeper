#include <map>
#include <string>
#include <sstream>
#include <iostream>

#include "GameView.hpp"

using namespace std;

GameView::GameView()
{
    
}

void GameView::addCommand(string name, void (*cb)(stringstream*))
{
    commands.insert(pair<string, void (*)(stringstream*)>(name, cb));
}

void GameView::readInput()
{
    readInput("");
}

void GameView::readInput(string message)
{
    cout << message << endl << "> ";
    string cmd;
    getline(cin, cmd);
    cout << endl;
    stringstream args(cmd);
    args >> cmd;
    activateCommand(cmd, &args);
}

void GameView::activateCommand(string name, stringstream* args)
{
    map<string, void (*)(stringstream*)>::iterator it = commands.find(name);
    if (it != commands.end()) {
        it->second(args);
    } else {
        cout << "Command \"" << name << "\" does not exist." << endl;
    }
}
