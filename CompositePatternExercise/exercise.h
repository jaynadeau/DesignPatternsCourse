#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ContainsIntegers
{
    virtual int sum() const = 0;
};

struct SingleValue : ContainsIntegers
{
  int value{ 0 };

  int sum() const override
  {
      return value;
  }

  SingleValue* begin()
  {
      return this;
  }

    SingleValue* end()
    {
        return this+1;
    }

  SingleValue() = default;

  explicit SingleValue(const int value)
    : value{value}
  {
  }


};

struct ManyValues : vector<int>, ContainsIntegers
{
  void add(const int value)
  {
    push_back(value);
  }

  int sum() const override
  {
      int total{};
      for(int val : *this)
      {
          total += val;
      }
      return total;
  }
};

int sum(const vector<ContainsIntegers*> items);
