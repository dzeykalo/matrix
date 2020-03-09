#include <iostream>
#include "matrix.h"
#include <cassert>


int main()
{
  {
    ///######## initial check ########///
    Matrix<int, -1> m;
    assert(m.size() == 0);

    auto a = m[0][0];
    assert(a == -1);
    assert(m.size() == 0);

    m[100][100] = 314;
    assert(m[100][100] == 314);
    assert(m.size() == 1);
  }
  {
    ///######## filling ########///
    int N = 10;
    Matrix<int, 0> m;
    for (int i = 0; i < N; i++){
      m[i][i] = m[N - 1 - i][i] = i;
    }

    for(int i = 0; i < N; i+=2){
      for (int j = 0; j < N; j+=2){
        m[i][j] = m[i+1][j+1] = 0;
      }
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
    std::cout << "Matrix size = " << m.size() << std::endl;
    for(auto el: m)
    {
      for(auto n: el.first)
        std::cout << "[" << n << "]";
      std::cout << " = " << el.second << std::endl;
    }

  }
  {
    ///######## initial check N measure ########///
    Matrix<int, -1, 4> m;
    assert(m.size() == 0);

    auto a = m[0][0][0][0];
    assert(a == -1);
    assert(m.size() == 0);

    m[100][100][100][100] = 314;
    assert(m[100][100][100][100] == 314);
    assert(m.size() == 1);
  }
  return 0;
}