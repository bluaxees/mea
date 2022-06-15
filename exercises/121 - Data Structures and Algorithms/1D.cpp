#include <iostream>

int propdivSum(int num)
{
/*
Returns the sum of all the proper divisors of the input integer
*/
	int sum = 0;
	for (int possible_div = 1; possible_div <= num/2; possible_div += 1)
	{
		if (num % possible_div == 0)
		{
			sum += possible_div;
		}
	}
	return sum;
}

bool isAmicable(int num, int lower = 1, int upper = 10000)
{
/*
Checks whether a number has an amicable pair within the upper and lower boundaries (default value at 1 and 10000, respectively)
*/
	int protopair = propdivSum(num);
	if (protopair > upper || protopair < lower || protopair == num)
	{
		return false;
	}
	else if (propdivSum(protopair) == num)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int amicableSum(int lower = 1, int upper = 10000)
{
/*
Computes the sum of the first n amicable pairs between the lower and upper boundaries, inclusive (default values are 1 and 10000)
*/
	int sum = 0;
	for (int possible_pair = lower; possible_pair <= upper; possible_pair += 1)
	{
		if (isAmicable(possible_pair))
		{
			sum += possible_pair;
		}
		else
		{
			continue;
		}
	}
	return sum;
}

int main()
{
/*
These are test program runs for Exercise 1D
*/
	int test_num = 21;
	std::cout << '\n' << "Test run for sum of proper divisors:" << '\n'
	<< "The sum of all the proper divisors of " << test_num << " is " << propdivSum(test_num) << '\n' << '\n';	
	std::string amicable_str;

	if (isAmicable(test_num))
	{
		amicable_str = " has an amicable pair less than 10000.";
	}
	else
	{
		amicable_str = " has no amicable pair less than 10000.";
	}
	std::cout<< "Dummy run for amicable pair test:" << '\n'
	<< "The number " << test_num << amicable_str << '\n' << '\n';
	
	std::cout << "The sum of all amicable pairs less than 10000 is " << amicableSum() << '\n';
}