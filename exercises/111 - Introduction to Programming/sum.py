sum = 0

def summation(n):
    if n == 1:
        return 1
    else:
        sum = n + summation(n-1)
        return sum
    
def main():
    n = int(input("Get summation of: "))
    print(summation(n))
    
if __name__ == "__main__":
    main()
