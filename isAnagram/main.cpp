#include <iostream>
#include <array>

int main() {
    std::string s = "anagram";
    std::string t = "nagaram";
    int vector[26];
    for (int &i: vector)
        i = 0;
    for (char c: s) {
        std::cout << tolower(c) << "\n";
        vector[tolower(c)] += 1;
    }
    for (char c: t) {
        vector[tolower(c)] -= 1;
    }
    for (int i: vector) {
        if (i != 0) {
            std::cout << "false";
            break;
        }
    }
    std::cout << "true";
    return 0;
}
