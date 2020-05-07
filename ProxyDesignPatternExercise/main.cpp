//
// Proxy Coding Exercise
//
//     You are given the Person class and asked to write a ResponsiblePerson wrapper/proxy that does the following:
//     - Allows person to drink unless they are younger than 18 (in that case, return "too young")
//     - Allows person to drive unless they are younger than 16 (otherwise "too young")
//     - In case of driving while drunk, returns "dead"
//
//     The interface of ResponsiblePerson has to match that of Person, except for the constructor, which takes an underlying Person object.
//

#include <iostream>
#include <string>
using namespace std;

class Person
{
  friend class ResponsiblePerson;
  int age;
public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
    ResponsiblePerson(const Person &person) : person(person) {}

    int get_age() const { return person.age; }
    void set_age(int age) { person.age = age; }

    string drink() const {
        if(person.age < 18)
            return "too young";
        else
            return person.drink();
    }
    string drive() const {
        if(person.age < 16)
            return "too young";
        else
            return person.drive();
    }
    string drink_and_drive() const {
        return "dead";
    }
    // todo
private:
    Person person;
};

int main(int argc, char* argv[])
{
    ResponsiblePerson young_person{Person{14}};
    ResponsiblePerson old_person{Person{42}};
    ResponsiblePerson teen{Person{17}};

    cout << young_person.drink() << endl;
    cout << young_person.drive() << endl;
    cout << young_person.drink_and_drive() << endl;
    cout << old_person.drink() << endl;
    cout << old_person.drive() << endl;
    cout << old_person.drink_and_drive() << endl;
    cout << teen.drink() << endl;
    cout << teen.drive() << endl;
    cout << teen.drink_and_drive() << endl;

    return EXIT_SUCCESS;
}

