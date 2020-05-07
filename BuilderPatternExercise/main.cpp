#include "CodeBuilder.h"

#include <iostream>

int main()
{
    builder::CodeBuilder cb{"Person"};
    cb.add_field("name", "string").add_field("args", "int");

    cout << cb << endl;

    return 0;
}
