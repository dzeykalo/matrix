#pragma once
#include <vector>
#include <algorithm>

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

template <typename T>
class v_matrix{
private:
    std::vector<T>& v;
    T def_val;
public:
    v_matrix(std::vector<T>& r, T dv) : v(r), def_val(dv){}
    T& operator[](unsigned int y){
      if (y >= v.size()){
        resizer<T> rv(v);
        rv.resize(y, def_val);
      }
      return v.at(y);
    }
};

template <typename T, T value>
class matrix
{
private:
  std::vector<std::vector<T>> m;
  T def_val;
  size_t count;
  bool ask;
public:
  matrix(unsigned int x, unsigned int y): count(0), def_val(value), ask(false)
  {
    m.resize(x, std::vector<T>(y,value));
  }
  matrix(): count(0), def_val(value), ask(false){}
  void counter(){count++;}
  size_t size(){
    if (!ask) {return count;}
    ask = false;
    count = 0;
    std::for_each(m.begin(),m.end(),[&](auto v)
    {
      count+=std::count_if(v.begin(), v.end(), [=](int i) {return i != def_val;});
    });
    return count;
  }
  v_matrix<T> operator[](unsigned int x){
    ask = true;
    if (x >= m.size()){
      resizer<std::vector<T>> v(m);
      v.resize(x, std::vector<T>());
    }
    return v_matrix<T>(m.at(x), def_val);
  }
  class iterator{
  private:
      std::vector<T> v;
  public:
      iterator(std::vector<T> r):v(r){}
  };
};

