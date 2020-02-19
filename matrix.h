#pragma once
#include <vector>
#include <algorithm>

template <typename T>
struct element
{
  int x;
  int y;
  T value;
  element():x(-1), y(-1), value(0){};
  element(int _x, int _y, T _value):x(_x), y(_y), value(_value){};
  element(T _value):x(-1), y(-1), value(_value){};
};

template <typename T, T DefValue>
class PushDef
{
private:
    std::vector<element<T>>& v;
public:
    PushDef(std::vector<element<T>>& r) : v(r) {
    }
    void Def(){
      element<T> el(DefValue);
      v.push_back(el);
    }
    void Try(){
      if (v.back().value != DefValue){
        Def();
      }
    }
};

template <typename T, T DefValue>
class Matrix
{
private:
  std::vector<element<T>> m;
public:
  Matrix():m(){
    PushDef<T,DefValue> Push(m);
    Push.Def();
  };
  size_t size() {
    PushDef<T,DefValue> Push(m);
    Push.Try();
    return m.size()-1;
  }

  class access{
  private:
    std::vector<element<T>>& v;
    unsigned int x;
  public:
    access(std::vector<element<T>>& r, unsigned int _x) : v(r), x(_x){}
    T& operator[](unsigned int y){
      PushDef<T,DefValue> Push(v);
      Push.Try();
      auto result = std::find_if(v.begin(), v.end(), [=](element<T> el){ return (el.x == x && el.y == y && el.value != DefValue);});
      if (result != v.end()){
        return (*result).value;
      }
      v.back().x = x; v.back().y = y;
      return v.back().value;
    }
  };
  access operator[](unsigned int x){
    return access(m, x);
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

