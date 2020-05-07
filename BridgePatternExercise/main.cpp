//
// Bridge Coding Exercise
//
//      You are given an example of an inheritance hierarchy which results in Cartesian-product duplication.
//
//      Please refactor this hierarchy, giving the base class Shape an initializer that takes a Renderer defined as
//
//      struct Renderer
//      {
//          virtual string what_to_render_as() const = 0;
//      }
//
//      as well as VectorRenderer and RasterRenderer.
//      
//      The expectation is that each constructed object has a memeber called str() that returns its textual representation, for example
//
//      Triangle(RasterRenderer()).str()    // returns "Drawing Triangle as pixels"
//

#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct Renderer
{
    virtual string what_to_render_as() const = 0;
};


struct RasterRenderer : public Renderer
{
    string what_to_render_as() const override
    {
        return "pixels";
    }
};

struct VectorRenderer : public Renderer
{
    string what_to_render_as() const override
    {
        return "lines";
    }
};

struct Shape
{
    Shape(Renderer&& renderer)
    : renderer{std::move(renderer)}
    {

    }
    Renderer&& renderer;
    // unique_ptr<Renderer> renderer;
    string name;
};

struct Triangle : Shape
{
    Triangle(Renderer&& renderer)
    : Shape{std::move(renderer)}
    {
        name = "Triangle";
    }

    virtual string str() const
    {
        return "Drawing " + name + " as " + renderer.what_to_render_as();
    }
};

struct Square : Shape
{
    Square(Renderer&& renderer)
    : Shape{std::move(renderer)}
    {
        name = "Square";
    }

    virtual string str() const
    {
        return "Drawing " + name + " as " + renderer.what_to_render_as();
    }
};

// imagine e.g. VectorTriangle/RasterTriangle etc. here

int main(int argc, char* argv[])
{
    Square rasterSquare{RasterRenderer{}};
    cout << rasterSquare.str() << endl;

    Square vectorSquare{VectorRenderer{}};
    cout << vectorSquare.str() << endl;

    return 0;
}

