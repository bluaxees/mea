import math

def prime(num):
    for n in range (2, math.floor(num**0.5 +1)):
        if num % n == 0:
            return False
    return True

def sum_prime(num):
    optimus = 2
    for n in range (3, num+1, 2):
        if prime (n) == True:
            optimus += n
    return optimus

print(sum_prime(2000000))