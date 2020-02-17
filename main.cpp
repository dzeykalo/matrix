#include <iostream>
#include "matrix.h"
#include <cassert>

int main()
{
  {
    matrix<int, -1> m;
    assert(m.size() == 0);

    auto a = m[0][0];
    assert(a == -1);
    assert(m.size() == 0);

    m[100][100] = 314;
    assert(m[100][100] == 314);
    assert(m.size() == 1);
  }
  {
    int N = 10;
    matrix<int, 0> m;
    for (int i = 0; i < N; i++){
      m[i][i] = m[N - 1 - i][i] = i;
    }

    for (int i = 1; i <= 8; i++)
    {
      for (int j = 1; j <= 8; j++)
      {
        std::cout << m[i][j];
        if (j!=8) {std::cout << " "; }
      }
      std::cout << std::endl;
    }
  }
    return 0;
}