import math

def optimus_prime(n):
    i = 2
    while i <= math.sqrt(n):
        while n % i == 0:
            n /= i
            int(n)
            if n == i:
                return int(n)
        i += 1
    return int(n)

print(optimus_prime(39))