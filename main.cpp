#include <iostream>
#include <vector>

template <typename T>

class matrix_mmm
{
private:
    T& mm;
public:
    matrix_mmm(T& r) : mm(r) {}
    T& operator=(T val)
    {
        mm = val;
        return mm;
    }
};

template <typename T>
class matrix_mm
{
private:
    std::vector<T>& mm;
public:
    matrix_mm(std::vector<T>& r) : mm(r) {}
    matrix_mmm<T> operator[](unsigned int y)
    {
        return mm.at(y);
    }
};



template <typename T, T value>
class matrix
{
private:
    std::vector<std::vector<T>> m;
    T default_val = value;
    size_t count;
public:
    matrix(unsigned int x, unsigned int y): count(0)
    {
        m.resize(x, std::vector<T>(y,value));
    }
    matrix(): count(0)
    {
        m.resize(100, std::vector<T>(100,value));
    }
    T size()
    {
        return static_cast<T>(m.size());
    }
    matrix_mm<T> operator[](unsigned int x)
    {
        return matrix_mm<T>(m.at(x));
    }
    T& operator=(T val)
    {
        return val;
    }
};

int main()
{
    matrix<int, -1> m;
    std::cout << m.size() << std::endl;
    m[1][2] = 4;
    //std::cout << m[1][2] << " " << m[1][3] << std::endl;
    return 0;
}