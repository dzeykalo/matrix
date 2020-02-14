#pragma once
#include <vector>

template <typename T>
class resizer
{
private:
  std::vector<T>& v;
public:
  resizer(std::vector<T>& r) : v(r) {}
  void resize(unsigned int size, T default_val){
    v.resize(size+1, default_val);
  }
};

template <typename T, T value>
class matrix
{
private:
  std::vector<std::vector<T>> m;
  T def_val;
  size_t count;
public:
  matrix(unsigned int x, unsigned int y): count(0), def_val(value)
  {
    m.resize(x, std::vector<T>(y,value));
  }
  matrix(): count(0), def_val(value){}
  T size()
  {
    return m.size();
  }
  class p_matrix{
  private:
    std::vector<T>& v;
    T def_val;
  public:
    p_matrix(std::vector<T>& r, T dv) : v(r), def_val(dv) {}
    T& operator[](unsigned int y){
      if (y >= v.size()){
        resizer<T> rv(v);
        rv.resize(y, def_val);
      }
      return v.at(y);
    }
  };
  p_matrix operator[](unsigned int x){
    if (x >= m.size()){
      resizer<std::vector<T>> v(m);
      v.resize(x, std::vector<T>());
    }
    return p_matrix(m.at(x), def_val);
  }
};

