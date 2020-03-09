#pragma once
#include <vector>
#include <algorithm>
#include <map>

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
    std::map<std::vector<int>,T>& map;
    element<T>& buff;
public:
    PushDef(std::map<std::vector<int>,T>& r, element<T>& _b) : map(r), buff(_b) {
    }
    void Def(){
      buff.n.clear();
      buff.value = DefValue;
    }
    void Lock(){
      map[buff.n] = buff.value;
    }
    void Try(){
      if (buff.value != DefValue)
        Lock();
      Def();
    }
};

template <typename T, T DefValue, size_t Size = 2>
class Matrix
{
private:
  element<T> buffer;
  std::map<std::vector<int>,T> m;
public:
  Matrix():buffer(),m(){
    PushDef<T,DefValue> Push(m, buffer);
    Push.Def();
  };
  size_t size() {
    PushDef<T,DefValue> Push(m, buffer);
    Push.Try();
    return m.size();
  }

  template<size_t I, typename Enable = void>
  class access;

  template <size_t I>
  class access<I, typename std::enable_if< ( 1 >= I ) >::type>{
  private:
    std::map<std::vector<int>,T>& map;
    element<T>& buff;
  public:
    access(std::map<std::vector<int>,T>& r, element<T>& _b) : map(r), buff(_b){}
    T& operator[](unsigned int x){
      buff.n.push_back(x);

      try{
        return map.at(buff.n);
      }
      catch (std::out_of_range){
        return buff.value;
      }
    }
  };

  template <size_t I>
  class access<I, typename std::enable_if< ( 1 < I ) >::type>{
  private:
    std::map<std::vector<int>,T>& map;
    element<T>& buff;
  public:
    access(std::map<std::vector<int>,T>& r, element<T>& _b) : map(r), buff(_b){}
    auto operator[](unsigned int y){
      buff.n.push_back(y);
      return access<I-1>(map, buff);
    }
  };

  auto operator[](unsigned int x){
    PushDef<T,DefValue> Push(m, buffer);
    Push.Try();
    buffer.n.push_back(x);
    return access<Size-1>(m, buffer);
  }

  class Iterator{
  private:
    typename std::map<std::vector<int>,T>::iterator data;
  public:
    Iterator(typename std::map<std::vector<int>,T>::iterator d): data(d){};
    element<T>& operator [](int n){ return data[n];}
    auto& operator *(){ return *data;}
    Iterator operator++(){return data++;}
    Iterator operator++(int){return data++;}
    bool operator!=(const Iterator &itr){return data != itr.data;}
    bool operator==(const Iterator &itr){return data == itr.data;}
  };

  Iterator begin(){return m.begin();}
  Iterator end(){return m.end();}
};

