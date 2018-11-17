//
// Created by ahmednagga19 on 17/11/18.
//

#include <vector>
#include <string>

using namespace std;


std::vector<string> split_string(std::string s, std::string delimiter)
{
    std::vector<std::string> splitted_strings;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        splitted_strings.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    splitted_strings.push_back(s);
    return splitted_strings;
}
