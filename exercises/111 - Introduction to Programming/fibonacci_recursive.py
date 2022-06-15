def fibonacci(n):
    if n == 0 or 1:
        return n
    else:
        return fibonacci(n-1) + fibonacci(n-2)

def main():
    n = int(input("Get fibonacci values to the: "))
    print(fibonacci(n))

if __name__ == "__main__":
    main()
