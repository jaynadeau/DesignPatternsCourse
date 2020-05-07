// Prototype Coding Exercise
//
//     Given the provided code, you are asked to implement Line::deep_copy() to perform a deep copy of the current Line object
//     Beware of memory leaks!
//
#ifndef SOLIDS_H
#define SOLIDS_H

#include <iostream>

using namespace std;

namespace prototype {

struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){cout << "Point default constructor" << endl;}

  ~Point(){cout << "Point destructor" << endl;}
  
  Point(const int x, const int y) : x{x}, y{y} {
    //   cout << "Point parameterized constructor" << endl;
  }

  Point(const Point& other)
  : x{other.x},
    y{other.y}
    {
    //   cout << "Point copy constructor" << endl;

    }
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
      cout << "Line parameterized constructor" << endl;
  }

  Line(const Line& other)
  : start{new Point{*other.start}},
    end{new Point{*other.end}}
  {
      cout << "Line copy constructor" << endl;
  }

  ~Line()
  {
      cout << "Line dtor" << endl;
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    // Line l{new Point{*start}, new Point{*end}};
    return {new Point{*start}, new Point{*end}};
  }
};

} // prototype

#endif // SOLIDS_H
