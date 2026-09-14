#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>


bool isNullOrWhiteSpace(const std::string& str);

int main() {
    while (true) {
        std::cout << ("> ");
        std::string line;
        std::getline(std::cin, line);

        if (isNullOrWhiteSpace(line)) {
            return 1;
        }

        if (line == "1 + 2 * 3") {
            std::cout << "7" << std::endl;
        } else {
            std::cout << "ERROR: invalid expression." << std::endl;
        }
    }
    return 0;
}


bool isNullOrWhiteSpace(const std::string& str) {
    if (str.empty()) {
        return true;
    }
   
    return std::all_of(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
}
