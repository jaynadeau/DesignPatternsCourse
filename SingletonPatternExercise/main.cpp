//
// Singleton Coding Exercise
//
//     Implementing a singleton is a bit too easy, so you've got a different challenge. 
//     You are given the function SingletonTester::is_singleton() defined below. This function takes a factory, and needs to return true or 
//     false depending on whether that factory produces singletons.
//     This one's actually easy. Ask yourself: what traits do two 'instances' of a singleton have in common?
//

#include <iostream>
#include <functional>
using namespace std;

class Singleton
{
public:
    static Singleton& getInstance()
    {
        static Singleton singleton;
        return singleton;
    }

    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& rhs) = delete;
private:
    Singleton() = default;
    ~Singleton() = default;
};

class SingletonFactory
{
public:
    static Singleton* make_singleton()
    {
        return &Singleton::getInstance();
    }
};

struct SingletonTester
{
  template <typename T>
  bool is_singleton(function<T*()> factory)
  {
    return (factory() == factory());
  }
};

int main(int argc, char* argv[])
{
    SingletonTester st;
    cout << boolalpha << "Produces singletons: " << st.is_singleton<Singleton>(SingletonFactory::make_singleton) << endl;

    return 0;
}