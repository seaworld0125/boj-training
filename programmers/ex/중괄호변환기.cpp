#include <string>
#include <iostream>
using namespace std;

int main() {

    while(true) {
        string str;

        getline(cin, str);

        for(char& c : str) {
            if(c == '[') printf("{");
            else if(c == ']') printf("}");
            else printf("%c", c);
        }
    }
}