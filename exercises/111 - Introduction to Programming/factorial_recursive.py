from __future__ import print_function

def factorial(num):
    if (num == 0) or (num == 1):
        return 1
    else:
        return num * factorial(num - 1)

def main():
    x = 5
    result = factorial(x)
    print("The factorial of", x, "is", result)

if __name__ == "__main__":
    main()