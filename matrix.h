#pragma once
#include <vector>
#include <algorithm>

template <typename T>
struct element
{
  std::vector<int> n;
  T value;
  element():n(2,-1), value(0){};
  element(int x, int y, T _value): value(_value){
    n = {x, y};
  };
  element(T _value):n(2,-1), value(_value){};
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

template <typename T, T DefValue, size_t Size = 2>
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

  template<size_t I, typename Enable = void>
  class access;

  template <size_t I>
  class access<I, typename std::enable_if< ( 1 >= I ) >::type>{
  private:
    std::vector<element<T>>& v;
    std::vector<int> n;
  public:
    access(std::vector<element<T>>& r, std::vector<int>& _n) : v(r), n(_n){}
    T& operator[](unsigned int x){
      PushDef<T,DefValue> Push(v);
      Push.Try();
      n.push_back(x);
      auto result = std::find_if(v.begin(), v.end(), [&](element<T> el){ return std::equal( n.begin(), n.end(), el.n.begin() ); });
      if (result != v.end()){
        return (*result).value;
      }
      v.back().n = std::move(n);
      return v.back().value;
    }
  };

  template <size_t I>
  class access<I, typename std::enable_if< ( 1 < I ) >::type>{
  private:
    std::vector<element<T>>& v;
    std::vector<int> n;
  public:
    access(std::vector<element<T>>& r, std::vector<int>& _n) : v(r), n(_n){}
    auto operator[](unsigned int y){
      n.push_back(y);
      return access<I-1>(v, n);
    }
  };

  auto operator[](unsigned int x){
    std::vector<int> n;
    n.push_back(x);
    return access<Size-1>(m, n);
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

