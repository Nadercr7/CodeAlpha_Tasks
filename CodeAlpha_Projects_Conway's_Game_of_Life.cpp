#include <iostream>
#include <vector>
#include <unistd.h> // For sleep function in Unix-based systems

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

// Constants for grid dimensions
const int ROWS = 20;
const int COLS = 40;

// Function to display the grid
void displayGrid(const vector<vector<bool>>& grid) {
    system(CLEAR_COMMAND); // Clear the terminal
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (grid[i][j]) {
                cout << "O";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}

// Function to count alive neighbors
int countAliveNeighbors(const vector<vector<bool>>& grid, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS) {
                if (grid[newX][newY]) count++;
            }
        }
    }
    return count;
}

// Function to evolve the grid to the next generation
void evolve(vector<vector<bool>>& grid) {
    vector<vector<bool>> newGrid = grid;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int aliveNeighbors = countAliveNeighbors(grid, i, j);
            if (grid[i][j]) {
                if (aliveNeighbors < 2 || aliveNeighbors > 3) {
                    newGrid[i][j] = false; // Cell dies
                }
            } else {
                if (aliveNeighbors == 3) {
                    newGrid[i][j] = true; // Cell becomes alive
                }
            }
        }
    }
    grid = newGrid;
}

// Function to set an initial state
void setInitialState(vector<vector<bool>>& grid) {
    int x, y;
    cout << "Enter the initial coordinates of live cells (end with -1 -1):" << endl;
    while (true) {
        cin >> x >> y;
        if (x == -1 && y == -1) break;
        if (x >= 0 && x < ROWS && y >= 0 && y < COLS) {
            grid[x][y] = true;
        } else {
            cout << "Invalid coordinates. Try again." << endl;
        }
    }
}

int main() {
    // Initial setup
    cout << "Welcome to Conway's Game of Life!" << endl;
    cout << "This program simulates the Game of Life, a cellular automaton devised by John Conway." << endl;
    cout << "Follow the instructions to set up the initial state and watch the simulation." << endl;

    // Prepare the grid
    vector<vector<bool>> grid(ROWS, vector<bool>(COLS, false));

    // Set the initial state
    setInitialState(grid);

    cout << " Once you are ready, press Enter to start the simulation." << endl;
    cin.ignore(); // Wait for the user to press Enter
    cin.get();

    // Run the simulation
    while (true) {
        displayGrid(grid);
        evolve(grid);
        usleep(200000); // Sleep for 200ms
    }

    return 0;
}
