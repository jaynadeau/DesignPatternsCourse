//
// Interpreter Coding Exercise
//
//     You are asked to write an expression processor for simple numeric expressions with the following constraints:
//
//         - Expressions use integral values (e.g., "13"), single letter variables defined in variables, as well as + and - operators only
//         - There is no need to support braces or any other operations
//         - If a variable is not found in variables (or if we encounter a variable with > 1 letter, e.g., ab) the evaluator returns 0 (zero)
//         - In case of any parsing failure, the evaluator returns 0
//
//     Example:
//
//         - calculate("1+2+3") should return 6
//         - calculate("1+2+xy") should return 0
//         - calculate("10-2-x") where x=3 is in variables should return 5
//

#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using namespace std::placeholders;

class Token
{
public:
    enum Type 
    {
        integer,
        plus,
        minus,
        variable
    };

    Token(string token, Type type)
    : token{token},
      type{type}
    {

    }

    Type getType() const
    {
        return type;
    }

    string getToken() const
    {
        return token;
    }

    friend ostream& operator<<(ostream& os, const Token& token)
    {
        os << "Token Type: " << token.type << " value: '" << token.token << "'";
        return os;
    }
private:
    string token;
    Type type;
};

class Element
{
public:
    Element() = default;
    virtual ~Element() = default;
    virtual int eval() const = 0;
};

class Integer : public Element
{
public:
    Integer(int value)
    : value{value}
    {

    }

    virtual ~Integer() = default;

    int eval() const override
    {
        return value;
    }

private:
    int value;
};

class BinaryOperation : public Element
{
public:
    enum Type {addition, subtraction};

    BinaryOperation() = default;
    virtual ~BinaryOperation() = default;

    int eval() const override
    {
        int result{0};
        auto left = lhs->eval();
        auto right = rhs->eval();
        if(type == addition)
        {
            result = left + right;
        }
        else if(type == subtraction)
        {
            result = left - right;
        }
        else
        {
            result = 0;
        }
        
        return result;
    }

    bool getHasLhs() const
    {
        return hasLhs;
    }

    void setHasLhs(bool input)
    {
        hasLhs = input;
    }
    void setLhs(shared_ptr<Element> input)
    {
        lhs = input;
    }
    void setRhs(shared_ptr<Element> input)
    {
        rhs = input;
    }
    void setType(Type input)
    {
        type = input;
    }
private:
    Type type;
    shared_ptr<Element> lhs, rhs;
    bool hasLhs{false};
};




struct ExpressionProcessor
{
  map<char,int> variables;

    int parse(const vector<Token>& tokens)
    {
        int total{0};
        auto operation = make_shared<BinaryOperation>();
        for(int i = 0; i < tokens.size(); ++i)
        {
            auto& token = tokens.at(i);
            switch(token.getType())
            {
            case Token::integer:
            {
                istringstream iss{token.getToken()};
                int value;
                iss >> value;
                auto integer = make_shared<Integer>(value);
                if(!operation->getHasLhs())
                {
                    operation->setLhs(integer);
                    operation->setHasLhs(true);
                    total = value;
                }
                else
                {
                    operation->setRhs(integer);
                    operation->setHasLhs(false);
                    total = operation->eval();
                    operation->setLhs(make_shared<Integer>(total));
                    operation->setHasLhs(true);
                }
                break;
            }
            case Token::minus:
                operation->setType(BinaryOperation::subtraction);
                break;
            case Token::plus:
                operation->setType(BinaryOperation::addition);
                break;
            case Token::variable:
            {
                // int value = variables[token.getToken().at(0)];
                auto search = variables.find(token.getToken().at(0));
                if(token.getToken().size() > 1 || search == variables.end())
                {
                    return 0;
                }
                else
                {
                    int value = search->second;
                    auto integer = make_shared<Integer>(value);
                    if(!operation->getHasLhs())
                    {
                        operation->setLhs(integer);
                        operation->setHasLhs(true);
                        total = value;
                    }
                    else
                    {
                        operation->setRhs(integer);
                        operation->setHasLhs(false);
                        total = operation->eval();
                        operation->setLhs(make_shared<Integer>(total));
                        operation->setHasLhs(true);
                    }
                }
                break;
            }
            default:
                return 0;
                break;
            }
        }
        return total;
    }
    vector<Token> lexer(const string& input)
    {
        vector<Token> result;

        for(int index = 0; index < input.size(); ++index)
        {
            char charToConsider = input.at(index);
            switch(charToConsider)
            {
            case '+':
                result.push_back(Token{string{charToConsider}, Token::plus});
                break;
            case '-':
                result.push_back(Token{string{charToConsider}, Token::minus});
                break;
            default:
                getAlphaNumericToken(input, index, result, Token::variable, [](int x){return isalpha(x);});
                getAlphaNumericToken(input, index, result, Token::integer, [](int x){return isdigit(x);});
                break;
            }
        }
        return result;
    }

  int calculate(const string& expression)
  {
    vector<Token> tokens = lexer(expression);
    auto parsed = parse(tokens);
    return parsed;
  }

private:

    void getAlphaNumericToken(const string& input, int& indexIntoInput, vector<Token>& result, Token::Type type, const function<int(int)>& f)
    {
        ostringstream buffer;
        
        if(f(input.at(indexIntoInput)))
        {
            buffer << input.at(indexIntoInput);
            // we have a variable...
            for(int j = indexIntoInput+1; j < input.size(); ++j)
            {
                if(f(input.at(j)))
                {
                    buffer << input.at(j);
                    ++indexIntoInput;
                }
                else
                {
                    break;
                }
            }
            result.push_back(Token{buffer.str(), type});
        }
    }
};

int main(int argc, char* argv[])
{
    string input{"x"};
    ExpressionProcessor ep;
    ep.variables['x'] = 3;
    int result = ep.calculate(input);
    cout << result << endl;

    return 0;
}

