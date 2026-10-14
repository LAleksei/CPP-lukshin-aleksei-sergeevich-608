#include <iostream>

void Deposit(long long& sum, long long k) {
  if (k <= 0) {
    std::cout << "error" << '\n';
    return;
  }
  sum += k;
}

void Withdraw(long long& sum, long long k) {
  if (k <= 0 || k > sum) {
    std::cout << "error" << '\n';
    return;
  }
  sum -= k;
}

void Balance(long long& sum, long long k) {
  std::cout << sum << '\n';
}

void Reset(long long& sum, long long k) {
  sum = 0;
}

void Double(long long& sum, long long k) {
  sum *= 2;
}

bool Is(const char* a, const char* b) {
  while (*a && *b && *a == *b) {
    ++a;
    ++b;
  }
  return *a == *b;
}

int main() {
  const char* kNames[] = {"deposit", "withdraw", "balance",
                          "reset",   "double"};
  void (*kHandlers[])(long long&, long long) = {Deposit, Withdraw, Balance,
                                                Reset,   Double};
  bool kNeedsArg[] = {true, true, false, false, false};
  const int kCount = sizeof(kNames) / sizeof(kNames[0]);

  long long sum = 0;
  char cmd[32];

  while (std::cin >> cmd) {
    if (Is(cmd, "stop")) {
      break;
    }

    int idx = -1;
    for (int i = 0; i < kCount; ++i) {
      if (Is(cmd, kNames[i])) {
        idx = i;
        break;
      }
    }

    if (idx == -1) {
      std::cout << "error" << '\n';
      continue;
    }

    long long k = 0;
    if (kNeedsArg[idx]) {
      if (!(std::cin >> k)) {
        std::cout << "error" << '\n';
        continue;
      }
    }

    kHandlers[idx](sum, k);
  }

  return 0;
}
