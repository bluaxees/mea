def optimus_prime(n):
    smol = 2
    while smol**2 < n:
        while n % smol == 0:
            n /= smol
    smol += 1    
    return int(n)

print(optimus_prime(5))