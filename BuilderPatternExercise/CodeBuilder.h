#ifndef CODE_BUILDER_H
#define CODE_BUILDER_H

// Builder Coding Exercise
//
//     You are asked to implement the Builder design pattern for rendering simple chunks of code.
//     Sample use of the builder you are asked to create:
//
//         auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
//         cout << cb;
//
//     The expected output of the above code is:
//
//         class Person
//         {
//             string name;
//             int args;
//         };
//
//     Please observe the same placement of curly braces and use two-space indentation.


#include <string>
#include <ostream>
#include <utility>
#include <vector>
using namespace std;

namespace builder {

class CodeBuilder
{
public:
    CodeBuilder(const string& class_name);

    CodeBuilder& add_field(const string& name, const string& type);

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj);
private:
    
    string className;
    vector<pair<string, string>> fields;
    inline static const string indentation{"  "};
    inline static const string space{" "};
    inline static const string newline{"\n"};
    inline static const string semicolon{";"};
    inline static const string openCurlyBrace{"{"};
    inline static const string closeCurlyBrace{"}"};
    inline static const string classKeyword{"class"};
};

} // builder

#endif // CODE_BUILDER_H
