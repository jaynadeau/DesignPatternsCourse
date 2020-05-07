#include "Person.h"

#include <iostream>

using namespace std;

int main()
{
    factory::PersonFactory pf;
    factory::Person p1 = pf.create_person("Jay");
    factory::Person p2 = pf.create_person("Steve");

    cout << p1.id << " " << p1.name << endl;
    cout << p2.id << " " << p2.name << endl;

    return 0;
}