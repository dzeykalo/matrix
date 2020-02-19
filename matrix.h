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
struct element
{
  int x;
  int y;
  T value;
};
template <typename T, T value>
class Matrix
{
private:
  std::vector<element<T>> m;
  T def_val;
public:
  Matrix():def_val(value){
    element<T> el;
    el.x = el.y = -1; el.value = def_val;
    m.push_back(el);
  };
  size_t size() {
    if (m.back().value != def_val){
      element<T> el;
      el.x = el.y = -1; el.value = def_val;
      m.push_back(el);
    }
    return m.size()-1;
  }

  class access{
  private:
    std::vector<element<T>>& v;
    T& dv;
    unsigned int x;
  public:
    access(std::vector<element<T>>& r, T& def_val, unsigned int _x) : v(r), dv(def_val), x(_x){}
    T& operator[](unsigned int y){
      if (v.back().value != dv){
        element<T> el;
        el.x = -1; el.y = -1; el.value = dv;
        v.push_back(el);
      }
      auto result = std::find_if(v.begin(), v.end(), [=](element<T> el){ return (el.x == x && el.y == y && el.value != dv);});
      if (result != v.end()){
        return (*result).value;
      }
      v.back().x = x; v.back().y = y;
      return v.back().value;
    }
  };
  access operator[](unsigned int x){
    return access(m,def_val,x);
  }

  class Iterator{
  private:
    typename std::vector<element<T>>::iterator data;
  public:
    Iterator(typename std::vector<element<T>>::iterator d): data(d){};
    element<T>& operator [](int n){ return data[n];}
    element<T>& operator *(){ return *data;}
    Iterator operator++(){return data++;}
    Iterator operator++(int){return data++;}
    bool operator!=(const Iterator &itr){return data != itr.data;}
    bool operator==(const Iterator &itr){return data == itr.data;}
  };

  Iterator begin(){return m.begin();}
  Iterator end(){return m.end()-1;}
};

