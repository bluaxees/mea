//Alarcon Ace H. Belen
//2018-04736

#include <iostream>
#include <stack>
#include <fstream>

bool checkBracket(std::string str) { 
    std::stack<char> char_stack; 
    char c;

    if (str.size()%2) {
        return false;
    }
  
    for (int i=0; i<str.length(); i++) 
    { 
        if (str[i]=='('|| str[i]=='['|| str[i]=='{') 
        { 
            char_stack.push(str[i]); 
            continue; 
        }

        else if (str[i]==')'|| str[i]==']'|| str[i]=='}') {
            switch (str[i]) { 
            case ')':  
                if (char_stack.empty() && i == str.length()-1){
                    return false;
                }
                c = char_stack.top(); 
                char_stack.pop(); 
                if (c != '(') {
                    return false; 
                }
                break; 

            case ']':
                if (char_stack.empty() && i == str.length()-1){
                    return false;
                }   
                c = char_stack.top(); 
                char_stack.pop(); 
                if (c != '[') {
                    return false; 
                }
                break;

            case '}':
                if (char_stack.empty() && i == str.length()-1){
                    return false;
                }
                c = char_stack.top(); 
                char_stack.pop(); 
                if (c != '{') {
                    return false; 
                }
                break; 
        default:
            break;
        } 
        }

        else {
            continue;
        }
    } 
    return (char_stack.empty()); 
} 
   
int main() 
{
    // modified read_file.cpp
    std::fstream infile("input_ex9C.txt", std::ios::in);
    char c = ' ';
    std::string line;
    while(true) {
        c = infile.get();
        if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') {
            line += c;
        }
        if(infile.eof()) {
            break;
        }
    }
    infile.clear();
    infile.seekg(0, infile.beg);
    infile.close();

    std::cout << line << '\n';

    if (checkBracket(line)) {
        std::cout << "No Error";
    }
    else {
        std::cout << "There is an error.";
    }
} 
