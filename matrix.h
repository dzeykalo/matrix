#pragma once
#include <vector>

template <typename T>
class v_matrix
{
public:
  virtual T operator[](T n) = 0;
};

template <typename T>
class pp_matrix
{
private:
  T& m;
public:
  pp_matrix(T& r) : m(r) {}
  T& operator=(T val){
    return m = val;
  }
};

template <typename T>
class p_matrix : public v_matrix<T>
{
private:
  std::vector<T>& m;
public:
  p_matrix(std::vector<T>& r) : m(r) {}
  T operator[](unsigned int n){
    return m.at(n);
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
  p_matrix<T> operator[](unsigned int x)
  {
    return p_matrix<T>(m.at(x));
  }

};

