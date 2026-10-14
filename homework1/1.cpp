#include <iomanip>
#include <iostream>

double averageTemp(const int* temps, int n) {
  long long sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += temps[i];
  }
  return static_cast<double>(sum) / n;
}

struct MinMax {
  int min;
  int max;
};

MinMax minMaxTemp(const int* temps, int n) {
  MinMax result{temps[0], temps[0]};
  for (int i = 1; i < n; ++i) {
    if (temps[i] < result.min) {
      result.min = temps[i];
    }
    if (temps[i] > result.max) {
      result.max = temps[i];
    }
  }
  return result;
}

int frostDays(const int* temps, int n) {
  int count = 0;
  for (int i = 0; i < n; ++i) {
    if (temps[i] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int n;
  std::cin >> n;

  int* temps = new int[n];

  for (int i = 0; i < n; ++i) {
    std::cin >> temps[i];
  }

  double avg = averageTemp(temps, n);
  MinMax mm = minMaxTemp(temps, n);
  int frost = frostDays(temps, n);

  std::cout << std::fixed << std::setprecision(1) << avg << '\n';
  std::cout << mm.min << ' ' << mm.max << '\n';
  std::cout << frost << '\n';

  delete[] temps;

  return 0;
}
