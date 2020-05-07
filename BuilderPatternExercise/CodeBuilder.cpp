#include "CodeBuilder.h"

namespace builder {

CodeBuilder::CodeBuilder(const string& class_name)
: className{class_name}
{
}

CodeBuilder& CodeBuilder::add_field(const string& name, const string& type)
{
    fields.emplace_back(pair{name, type});
    return *this;
}

ostream& operator<<(ostream& os, const CodeBuilder& obj)
{
    os << CodeBuilder::classKeyword << CodeBuilder::space << obj.className << CodeBuilder::newline
       << CodeBuilder::openCurlyBrace << CodeBuilder::newline;
    for(const auto& [fieldName, fieldType] : obj.fields)
    {
        os << CodeBuilder::indentation << fieldType << CodeBuilder::space << fieldName << CodeBuilder::semicolon << CodeBuilder::newline;
    }
    os << CodeBuilder::closeCurlyBrace << CodeBuilder::semicolon;
    return os;
}

} // builder
