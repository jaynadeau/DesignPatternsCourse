
//
// Flyweight Coding Exercise
//
//     You are given a class called Sentence, which takes a string such as "hello world". You need to provide an interface such that the indexer
//     (operator[]) returns a WordToken that can be used to capitalize a particular word in the sentence.
//
//     Typical use would be something like:
//
//         Sentence sentence{"hello world"};
//         sentence[1].capitalize = true;
//         cout << sentence.str();     // prints "hello WORLD"
//

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


struct Sentence
{
  struct WordToken
  {
    bool capitalize;
  };

  Sentence(const string& text)
  : text{text}
  {
    istringstream  stream(text);
    string        oneWord;
    while(stream >> oneWord)
    {
        wordTokens.emplace_back(WordToken{false});
        // cout << oneWord << endl;
    }
  }

  WordToken& operator[](size_t index)
  {
    return wordTokens[index];
  }

  string str() const
  {
    istringstream iStream(text);
    ostringstream oStream;
    string        oneWord;
    for(auto wordToken : wordTokens)
    {
        iStream >> oneWord;
        if(wordToken.capitalize)
        {
            transform(oneWord.begin(), oneWord.end(), oneWord.begin(), ::toupper);
            oStream << oneWord;
        }
        else
        {
            oStream << oneWord;
        }
        oStream << " ";
    }
    string result = oStream.str();
    result.erase(result.find_last_not_of(" ") + 1);
    return result;
  }
private:
    vector<WordToken> wordTokens;
    string text;
};

int main(int argc, char* argv[])
{
    Sentence sentence{"hello world"};
    sentence[0].capitalize = true;
    cout << sentence.str() << endl;

    return 0;
}
