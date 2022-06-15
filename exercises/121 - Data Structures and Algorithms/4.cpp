//2018-04736
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> vec_str = {};

int index_vec(std::vector<std::string> &v_str, std::string b_str)
{
	int pos;
	b_str.erase(0,1);
	auto it = std::find(v_str.begin(), v_str.end(), b_str);
	if (it != v_str.end())
	{
		pos = distance(v_str.begin(), it);
	}
	else
	{
		pos = -1;
	}
	return pos;
}

void del_substr(std::vector<std::string> &a_str, int pos) {
	a_str.erase(a_str.begin() + pos);
}

void print() {
	for (std::vector<std::string>::iterator it = vec_str.begin(); it != vec_str.end(); ++it) {
		if (it == vec_str.begin()) {
			std::cout << *it;
		}
        else {
        	std::cout << ", " << *it;
        }
	}
	std::cout << '\n';
}

void add_str(std::vector<std::string> &a_str, std::string b_str) {
	b_str.erase(0,1);
	a_str.push_back(b_str);	
}

int whattodo(std::string a_str) {
	if (a_str == "add") {
		return 1;
	}
	else if (a_str == "delete") {
		return 2;
	}
	else if (a_str == "print") {
		return 3;
	}
	else if (a_str == "stop") {
		return 4;
	}
	else {
		return 0;
	}
}

int main() {

	int pos;

	int running = 1;
	do {
		int index = 0;
		std::string input = "";
		std::string command = "";
		std::cout << "Enter a command: ";
		std::cin >> command;
		getline(std::cin, input);
		switch(whattodo(command)) {
			case 0:
				std::cout << "Invalid keyword." << '\n';
				break;
			case 1:
				add_str(vec_str, input);
				break;
			case 2:
				index = index_vec(vec_str, input);
				if (vec_str.size() == 0) {
					std::cout << "No word to delete" << '\n';
				}
				else if (index == -1){
					std::cout << input.erase(0,1) << " not found." << '\n';
					break;
				}
				else {
					del_substr(vec_str, index);	
				}
				break;
			case 3:
				if (input.size()) {
					std::cout << "Invalid keyword." << '\n';
					break;
				}
				else if (!vec_str.size()) {
					std::cout << "There are no word(s) to print." << '\n';
					break;
				}
				print();
				break;
			case 4:
				if (input.size()) {
					std::cout << "Invalid keyword." << '\n';
					break;
				}
				running = 0;
				break;
		}
	} while (running);
}
