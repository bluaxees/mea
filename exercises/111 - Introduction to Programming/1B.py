import math

def prime(num):
    for n in range (2, math.floor(num**0.5 +1)):
        if num % n == 0:
            return False
    return True

def fact_prime():
    l = int(input("Enter any integer greater than 1: "))
    while l <= 1:
        l = int(input("Please input a valid integer greater than 1: "))
    int(l)
    for x in range (l, 1, -1):
        if l % x == 0:
            if prime (x) == True:
                print (x)


fact_prime()