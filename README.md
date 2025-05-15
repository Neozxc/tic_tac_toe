# Tic Tac Toe AI (C++)

A simple command-line Tic Tac Toe game in C++ where you play as `X` against an unbeatable AI (`O`) powered by the **Minimax algorithm**.

## Features

- Classic 3x3 Tic Tac Toe board
- Turn-based gameplay
- AI uses the Minimax algorithm to always play optimally
- Detects wins, losses, and draws
- Undo and scoring logic handled internally

## Build Instructions

Compile using a C++17-compatible compiler:

```bash
g++ -std=c++17 -o tictactoe main.cpp