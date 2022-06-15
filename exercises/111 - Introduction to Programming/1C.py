import math

def prime(num):
    for n in range (2, math.floor(num**0.5 +1)):
        if num % n == 0:
            return False
    return True

def nth_prime(m):
    count = 0
    for n in range (2, 2**m):
        if prime (n) == True:
            count += 1
            if count == m:
                print (n)
                return (n)

print(nth_prime(10001))