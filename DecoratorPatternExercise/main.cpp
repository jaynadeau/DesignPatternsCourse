//
// Decorator Coding Exercise
//
//     Roses can be red, blue or red and blue. Given the class interface Flower and class Rose, build decorators RedFlower and BlueFlower that would 
//     print the following:
//
//          Rose rose;
//          RedFlower red_rose{rose};
//          RedFlower red_red_rose{red_rose};
//          BlueFlower blue_red_rose{red_rose};
//          cout << rose.str();             // "A rose"
//          cout << red_rose.str();         // "A rose that is red"
//          cout << red_red_rose.str();     // "A rose that is red"
//          cout << blue_red_rose.str();    // "A rose that is red and blue"
//

#include <iostream>
#include <string>
using namespace std;

struct Flower
{
  virtual string str() = 0;
};

struct Rose : Flower
{
  virtual string str() override {
    return "A rose";
  }
};

struct RedFlower : Flower
{
    Flower& flower;
    const string color{"red"};

    RedFlower(Flower& flower)
    : flower(flower)
      {

      }

    virtual string str() override
    {
        string result;
        int length = flower.str().length();
        if(length > 6 && length < 20)
        {
            result = flower.str() + " and " + color;
        }
        else if(length < 7)
        {
            result = flower.str() + " that is " + color;
        }
        else
        {
            result = flower.str();
        }
        
        return result;
    }

};

struct BlueFlower : Flower
{
    Flower& flower;
    const string color{"blue"};

    BlueFlower(Flower& flower)
    : flower(flower)
      {

      }

    virtual string str() override
    {
        string result;
        int length = flower.str().length();
        if(length > 6 && length < 19)
        {
            result = flower.str() + " and " + color;
        }
        else if(length < 7)
        {
            result = flower.str() + " that is " + color;
        }
        else
        {
            result = flower.str();
        }
        
        return result;
    }
};

int main(int argc, char* argv[])
{
    Rose rose;
    RedFlower red_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_rose{rose};
    BlueFlower blue_red_rose{red_rose};
    RedFlower red_blue_rose{blue_rose};
    RedFlower red_blue_red_rose{blue_red_rose};
    BlueFlower blue_red_blue_rose{red_blue_rose};
    cout << rose.str() << endl;
    cout << red_rose.str() << endl; 
    cout << red_red_rose.str() << endl;
    cout << blue_rose.str() << endl;
    cout << blue_red_rose.str() << endl;
    cout << red_blue_rose.str() << endl;
    cout << red_blue_red_rose.str() << endl;
    cout << blue_red_blue_rose.str() << endl;

    return 0;
}
