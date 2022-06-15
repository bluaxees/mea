sum = 0

def harmonic(n):
    if n == 1:
        return 1.0
    elif n == 0:
        return 0.0
    else:
        sum = 1/n + harmonic(n-1)
        return sum
        
def main():
    n = int(input("Get the sum of harmonic numbers to what number? "))
    print(harmonic(n))
    
if __name__ == "__main__":
    main()
