import math

def prime(num):
    for n in range (2, math.floor(num**0.5 +1)):
        if num % n == 0:
            return False
    return True

def strime():
    strime = input(str("Input a string here: "))
    strum = 0
    for n in strime:
        if n.isdigit():
            strum += int(n)
        else:
            continue
    if prime(strum) == True:
        print ("The sum of the numbers in this string is a prime number!")
    else:
        print ("The sum of the numbers in this string is not a prime number!")
strime()