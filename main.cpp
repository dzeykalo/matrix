#include <iostream>
#include <vector>

template <typename T, T value>
class matrix
{
private:
    std::vector<std::vector<T>> m;
    T default_val = value;
    size_t count;
public:
    matrix(): count(0)
    {
      m.resize(100, std::vector<T>(100,value));
    }
    T size()
    {
      return static_cast<T>(m.size());
    }
    class matrix_mm
    {
    private:
      std::vector<T>& mm;
    public:
      matrix_mm(std::vector<T>& r) : mm(r) {}
      T& operator[](unsigned int y)
      {
        return mm.at(y);
      }
    };
    matrix_mm operator[](unsigned int x)
    {
      return matrix_mm(m.at(x));
    }
};

int main()
{
    matrix<int, -1> m(100,100);
    std::cout << m.size() << std::endl;
    m[1][2] = 4;
    std::cout << m[1][2] << " " << m[1][3] << std::endl;
    return 0;
}