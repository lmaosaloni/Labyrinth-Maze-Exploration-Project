#include <string>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

// Define your full name here. Once set, avoid changing this value to ensure consistency in maze exploration.
const string kYourName = "Saloni Mhatre";

// Define the escape paths for your mazes here.
const string kPathOutOfRegularMaze = "ESWEENEWSWWENSWEESSWW";
const string kPathOutOfTwistyMaze = "SWENNSWNSWWWEE";

// Function to determine if a given path leads to freedom by collecting all necessary items.
bool isPathToFreedom(MazeCell* start, const string& moves) {
    bool hasSpellBook = false, hasPotion = false, hasWand = false; // Track the collection of items.
    MazeCell* currentCell = start;

    // Initial check at the starting cell.
    if (currentCell && !currentCell->whatsHere.empty()) {
        hasSpellBook = currentCell->whatsHere == "Spellbook";
        hasPotion = currentCell->whatsHere == "Potion";
        hasWand = currentCell->whatsHere == "Wand";
    }

    // Traverse the maze according to the moves sequence.
    for (char move : moves) {
        if (!currentCell) return false; // Exit if encountered a null cell.

        switch (move) {
            case 'N': currentCell = currentCell->north; break;
            case 'S': currentCell = currentCell->south; break;
            case 'E': currentCell = currentCell->east; break;
            case 'W': currentCell = currentCell->west; break;
            default: return false; // Invalid move.
        }

        // Check and collect items at the new cell location.
        if (currentCell) {
            if (currentCell->whatsHere == "Spellbook") hasSpellBook = true;
            else if (currentCell->whatsHere == "Potion") hasPotion = true;
            else if (currentCell->whatsHere == "Wand") hasWand = true;
        } else {
            return false; // Path leads to a dead end.
        }
    }

    // Verify if all items have been collected.
    return hasSpellBook && hasPotion && hasWand;
}
