#include <iostream>
#include <fstream>

int main() {
    // open file as input
    std::fstream infile("input_ex9C.txt", std::ios::in);

    // per character input
    char c = ' ';
    while(true) {
        c = infile.get();
        // process current character (type: char)
        if(infile.eof()) {break;}   // when no more character can be read, value read is -1 which is End-Of-File (EOF)
        std::cout << c;
    }
    std::cout << '\n';

    // go back to the beginning of the file to read it again
    infile.clear();                 // reset EOF related flags
    infile.seekg(0, infile.beg);    // move to index 0 relative to the beginning of the file   

    // per line input
    std::string line;
    while(std::getline(infile, line)) {
        // process current line (type: std::string)
        std::cout << line << std::endl;
    }

    infile.close(); // close file
    std::cout << line;
}
