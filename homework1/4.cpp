#include <iostream>

// Задача: трёхмерный куб N x N x N целых чисел. Сначала вводится N, куб создается в динамической памяти и заполняется 0.
// Команды:
// insert x y z a - записать число a в ячейку (x,y,z)
// row x y - напечатать сумму чисел в строке (x,y)
// col x z - напечатать сумму чисел в столбце (x,z)
// layer x - напечатать сумму чисел слоя x
// print - напечатать куб по слоям
// quit - выход из программы
// другие команды выдадут error

bool Is(const char* a, const char* b) {
  while (*a && *b && *a == *b) {
    ++a;
    ++b;
  }
  return *a == *b;
}

int*** Allocate(int n) {
  int*** cube = new int**[n];
  for (int x = 0; x < n; ++x) {
    cube[x] = new int*[n];
    for (int y = 0; y < n; ++y) {
      cube[x][y] = new int[n];
      for (int z = 0; z < n; ++z) {
        cube[x][y][z] = 0;
      }
    }
  }
  return cube;
}

void DeleteCube(int*** cube, int n) {
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < n; ++y) {
      delete[] cube[x][y];
    }
    delete[] cube[x];
  }
  delete[] cube;
}

int main() {
  int n;
  std::cin >> n;

  int*** cube = Allocate(n);

  void* generic = cube;
  int*** c = (int***)generic;

  char cmd[16];
  while (std::cin >> cmd) {
    if (Is(cmd, "quit")) {
      break;
    }

    if (Is(cmd, "insert")) {
      int x, y, z, a;
      std::cin >> x >> y >> z >> a;
      if (x < 0 || x >= n || y < 0 || y >= n || z < 0 || z >= n) {
        std::cout << "error" << '\n';
        continue;
      }
      c[x][y][z] = a;

    } else if (Is(cmd, "row")) {
      int x, y;
      std::cin >> x >> y;
      if (x < 0 || x >= n || y < 0 || y >= n) {
        std::cout << "error" << '\n';
        continue;
      }
      long long sum = 0;
      for (int i = 0; i < n; ++i) {
        sum += c[x][y][i];
      }
      std::cout << sum << '\n';

    } else if (Is(cmd, "col")) {
      int x, z;
      std::cin >> x >> z;
      if (x < 0 || x >= n || z < 0 || z >= n) {
        std::cout << "error" << '\n';
        continue;
      }
      long long sum = 0;
      for (int i = 0; i < n; ++i) {
        sum += c[x][i][z];
      }
      std::cout << sum << '\n';

    } else if (Is(cmd, "layer")) {
      int x;
      std::cin >> x;
      if (x < 0 || x >= n) {
        std::cout << "error" << '\n';
        continue;
      }
      long long sum = 0;
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          sum += c[x][i][j];
        }
      }
      std::cout << sum << '\n';

    } else if (Is(cmd, "print")) {
      for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
          for (int z = 0; z < n; ++z) {
            if (z > 0) {
              std::cout << ' ';
            }
            std::cout << c[x][y][z];
          }
          std::cout << '\n';
        }
        if (x + 1 < n) {
          std::cout << '\n';
        }
      }

    } else {
      std::cout << "error" << '\n';
    }
  }

  DeleteCube(cube, n);
  return 0;
}
