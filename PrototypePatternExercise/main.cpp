#include "Solids.h"

int main()
{
    prototype::Line l1{new prototype::Point{3, 5}, new prototype::Point{7, 6}};

    cout << "l1 constructed" << endl;

    prototype::Line l2 = l1.deep_copy();

    cout << "l2 constructed" << endl;

    cout << l2.start->x << endl;

    return 0;
}