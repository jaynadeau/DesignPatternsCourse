//
// Adapter Coding Exercise
//
//     Here's a very synthetic example for you to try.
//
//     You are given a Rectangle protocol and extension method on it. Try to define a SquareToRectangleAdapter
//     that adapts the Square to the Rectangle.
//

#include <iostream>
using namespace std;

struct Square
{
  int side{ 0 };


  explicit Square(const int side)
    : side(side)
  {
  }
};

struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

struct SquareToRectangleAdapter : Rectangle
{
  SquareToRectangleAdapter(const Square& square)
  : mWidth{square.side},
    mHeight{square.side}
  {
      // todo
  }

  int width() const override
  {
      return mWidth;
  }

  int height() const override
  {
      return mHeight;
  }

  int mWidth;
  int mHeight;
};

