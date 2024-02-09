#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<std::string> result;

    int first = 0;
    int count = 0;
    for (int i = 0; i < rawWords.length(); i++)
    {
        if (!isalnum(rawWords[i]) && i - first > 1)
        {
            result.insert(convToLower(rawWords.substr(first, i - first)));

            first = i + 1;
        }

        else if (!isalnum(rawWords[i]))
        {
            first = i + 1;
        }
    }

    // edge case of last substring (if isn't a punctuation)
    if (isalnum(rawWords[rawWords.length() - 1]) && rawWords.length() - 1 - first > 1)
    {
        result.insert(convToLower(rawWords.substr(first, rawWords.length())));
    }

    return result;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s)
{
    s.erase(
        std::find_if(s.rbegin(),
                     s.rend(),
                     std::not1(std::ptr_fun<int, int>(std::isspace)))
            .base(),
        s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}
