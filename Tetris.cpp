#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <array>
#include <chrono>
#include <thread>

using namespace std;

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

class TetrisGame {
public:
    TetrisGame();
    void run();

private:
    char board[BOARD_HEIGHT][BOARD_WIDTH];
    int score;
    bool gameover;

    struct Point {
        int x, y;
    };

    struct Tetromino {
        Point blocks[4];
    };

    Tetromino currentTetromino;
    int currentRotation;

    vector<Tetromino> tetrominos;

    void initBoard();
    void drawBoard();
    void drawTetromino();
    void clearTetromino();
    bool isValidMove(int offsetX, int offsetY, int rotation);
    void placeTetromino();
    void checkLines();
    void spawnTetromino();
    void handleInput();
};

TetrisGame::TetrisGame() : score(0), gameover(false), currentRotation(0) {
    srand(static_cast<unsigned>(time(0)));

    initBoard();

    tetrominos.push_back({{{0, 1}, {1, 1}, {2, 1}, {3, 1}}}); // I
    tetrominos.push_back({{{1, 0}, {0, 1}, {1, 1}, {2, 1}}}); // J
    tetrominos.push_back({{{0, 1}, {1, 1}, {2, 1}, {2, 0}}}); // L
    tetrominos.push_back({{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}); // O
    tetrominos.push_back({{{1, 0}, {2, 0}, {0, 1}, {1, 1}}}); // S
    tetrominos.push_back({{{0, 1}, {1, 1}, {2, 1}, {1, 0}}}); // T
    tetrominos.push_back({{{0, 0}, {1, 0}, {1, 1}, {2, 1}}}); // Z

    spawnTetromino();
}

void TetrisGame::initBoard() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            board[i][j] = ' ';
        }
    }
}

void TetrisGame::drawBoard() {
    system("cls"); // Clear the console

    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            cout << board[i][j];
        }
        cout << endl;
    }

    cout << "Score: " << score << endl;
}

void TetrisGame::drawTetromino() {
    for (int i = 0; i < 4; ++i) {
        int x = currentTetromino.blocks[i].x;
        int y = currentTetromino.blocks[i].y;
        board[y][x] = '*';
    }
}

void TetrisGame::clearTetromino() {
    for (int i = 0; i < 4; ++i) {
        int x = currentTetromino.blocks[i].x;
        int y = currentTetromino.blocks[i].y;
        board[y][x] = ' ';
    }
}

bool TetrisGame::isValidMove(int offsetX, int offsetY, int rotation) {
    clearTetromino();

    for (int i = 0; i < 4; ++i) {
        int x = currentTetromino.blocks[i].x + offsetX;
        int y = currentTetromino.blocks[i].y + offsetY;

        // Check if the new position is within the board bounds
        if (x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT) {
            return false;
        }

        // Check if the new position is occupied by another block
        if (board[y][x] != ' ') {
            return false;
        }
    }

    return true;
}

void TetrisGame::placeTetromino() {
    for (int i = 0; i < 4; ++i) {
        int x = currentTetromino.blocks[i].x;
        int y = currentTetromino.blocks[i].y;
        board[y][x] = '*';
    }
}

void TetrisGame::checkLines() {
    for (int i = BOARD_HEIGHT - 1; i >= 0; --i) {
        bool lineFull = true;

        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (board[i][j] == ' ') {
                lineFull = false;
                break;
            }
        }

        if (lineFull) {
            // Remove the line
            for (int k = i; k > 0; --k) {
                for (int j = 0; j < BOARD_WIDTH; ++j) {
                    board[k][j] = board[k - 1][j];
                }
            }

            // Increment the score
            score += 10;
        }
    }
}

void TetrisGame::spawnTetromino() {
    currentTetromino = tetrominos[rand() % tetrominos.size()];
    currentRotation = 0;

    if (!isValidMove(0, 0, currentRotation)) {
        gameover = true;
    }
}

void TetrisGame::handleInput() {
    int newRotation;  // Di chuyển khai báo ra ngoài switch-case

    if (_kbhit()) {
        char key = _getch();

        switch (key) {
            case 'a':
                if (isValidMove(-1, 0, currentRotation)) {
                    clearTetromino();
                    --currentTetromino.blocks[0].x;
                    --currentTetromino.blocks[1].x;
                    --currentTetromino.blocks[2].x;
                    --currentTetromino.blocks[3].x;
                    drawTetromino();
                }
                break;

            case 'd':
                if (isValidMove(1, 0, currentRotation)) {
                    clearTetromino();
                    ++currentTetromino.blocks[0].x;
                    ++currentTetromino.blocks[1].x;
                    ++currentTetromino.blocks[2].x;
                    ++currentTetromino.blocks[3].x;
                    drawTetromino();
                }
                break;

            case 's':
                if (isValidMove(0, 1, currentRotation)) {
                    clearTetromino();
                    ++currentTetromino.blocks[0].y;
                    ++currentTetromino.blocks[1].y;
                    ++currentTetromino.blocks[2].y;
                    ++currentTetromino.blocks[3].y;
                    drawTetromino();
                }
                break;

            case 'w':
                // Di chuyển khởi tạo vào đây
                newRotation = (currentRotation + 1) % 4;
                if (isValidMove(0, 0, newRotation)) {
                    clearTetromino();
                    currentRotation = newRotation;
                    drawTetromino();
                }
                break;

            case 'q':
                gameover = true;
                break;
        }
    }
}

void TetrisGame::run() {
    while (!gameover) {
        drawBoard();
        handleInput();

        if (isValidMove(0, 1, currentRotation)) {
            clearTetromino();
            ++currentTetromino.blocks[0].y;
            ++currentTetromino.blocks[1].y;
            ++currentTetromino.blocks[2].y;
            ++currentTetromino.blocks[3].y;
            drawTetromino();
        } else {
            placeTetromino();
            checkLines();
            spawnTetromino();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Delay 100 milliseconds
    }

    cout << "Game Over! Your score: " << score << endl;
}

int main() {
    TetrisGame game;
    game.run();

    return 0;
}