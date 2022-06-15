#include <iostream>

bool isTwoDigit(std::string user_input)
{
/*
Checks if input is a two digit integer
*/
	if (user_input.length() == 2)
	{
		int input_value = atoi(user_input.c_str());
		if (input_value >= 10 && input_value <= 99)
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

int main()
{
/*
Main function for Exercise 1C. Prompts user to re-enter input if the value is not a two-digit integer (floats are not accepted)
*/
	int limit;
	std::string limit_str;
	std::cout << "Enter any two-digit integer: ";
	std::cin >> limit_str;
	
	while (std::cin.fail() || !isTwoDigit(limit_str))
	{
		std::cout << "Please enter a valid input: ";
		std::cin.clear();
		std::cin.ignore(500, '\n');
		std::cin >> limit_str;
	}
	limit = atoi(limit_str.c_str());
	std::cout << "Multiples of nine below the input integer: " << '\n';
	for (int n = 9; n < limit; n += 9)
	{
		std::cout << n << '\n';
	}
}