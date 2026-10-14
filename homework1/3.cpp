#include <iostream>

const int kRows = 5;
const int kCols = 10;

bool Is(const char* a, const char* b) {
  while (*a && *b && *a == *b) {
    ++a;
    ++b;
  }
  return *a == *b;
}

void Clear(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      board[y][x] = ' ';
    }
  }
}

bool Put(char board[kRows][kCols], int x, int y, char c) {
  if (x < 0 || x >= kCols || y < 0 || y >= kRows) {
    return false;
  }
  board[y][x] = c;
  return true;
}

bool Text(char board[kRows][kCols], int x, int y, const char* word) {
  int len = 0;
  while (word[len] != '\0') {
    ++len;
  }
  if (x < 0 || y < 0 || y >= kRows || x + len > kCols) {
    return false;
  }
  for (int i = 0; i < len; ++i) {
    board[y][x + i] = word[i];
  }
  return true;
}

void Print(char board[kRows][kCols]) {
  for (int y = 0; y < kRows; ++y) {
    for (int x = 0; x < kCols; ++x) {
      std::cout << board[y][x];
    }
    std::cout << '\n';
  }
}

int main() {
  char board[kRows][kCols];
  Clear(board);

  char cmd[16];
  while (std::cin >> cmd) {
    if (Is(cmd, "quit")) {
      break;
    } else if (Is(cmd, "clear")) {
      Clear(board);
    } else if (Is(cmd, "put")) {
      int x, y;
      char c;
      std::cin >> x >> y >> c;
      if (!Put(board, x, y, c)) {
        std::cout << "error" << '\n';
      }
    } else if (Is(cmd, "text")) {
      int x, y;
      char word[16];
      std::cin >> x >> y >> word;
      if (!Text(board, x, y, word)) {
        std::cout << "error" << '\n';
      }
    } else if (Is(cmd, "print")) {
      Print(board);
    } else {
      std::cout << "error" << '\n';
    }
  }

  return 0;
}
