from __future__ import print_function
from math import sqrt

def isprime(num):
    is_prime = True

    for i in range(int(sqrt(num))):
        i += 2
        if not(num % i):
            is_prime = False
            break
    else:
        return is_prime

def main():
    countprime = 1 #automatically counting 2 as prime
    counter = 2 #number 2 is composite
    prime = 0

    while countprime < 10001:
        if isprime(counter):
            countprime += 1
            prime = counter

        counter += 1

    print("The 10001st prime number is: ", str(prime))

if __name__ == "__main__":
    main()
