#include <iostream>
#include "matrix.h"

template <typename T>
std::ostream &operator<<(std::ostream &os, matrix_mmm<T> c)
{
  auto a = c.get();
  os << a;
}

int main()
{
    matrix<int, -1> m;
    std::cout << m.size() << std::endl;
    m[1][2] = 4;
    auto a = m[1][2];
    std::cout << m[1][2] << " " << m[1][3] << std::endl;
    return 0;
}