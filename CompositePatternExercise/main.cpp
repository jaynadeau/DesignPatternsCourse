//
// Composite Coding Exercise
//
//     Consider the code presented below. The sum() function takes a vector of pointers to either SingleValue or ManyValues instances and adds up all their elements together.
//     Please complete the implementation so that the sum() function starts to operate correctly. This may involve giving the classes a common interface, among other things.
//
//     Here is an example of how the function might be used:
//
//         SingleValue single_value{ 1 };
//         ManyValues other_values;
//         other_values.add(2);
//         other_values.add(3);
//         sum({&single_value, &other_values});    // returns 6
//

#include "exercise.h"

#include <iostream>
using namespace std;

int sum(const vector<ContainsIntegers*> items)
{
    int total{};
    for(ContainsIntegers* item : items)
    {
        total += item->sum();
    }
    return total;
}


int main(int argc, char* argv[])
{
    SingleValue sv{1};
    ManyValues mv;
    mv.add(2);
    mv.add(3);
    cout << sum({&sv, &mv}) << endl;

    return 0;
}
