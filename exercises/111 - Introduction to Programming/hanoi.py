moves = 0

def hanoi(n):
    if n == 0:
        return 1
    else:
        return 2 * hanoi(n-1)
        
def main():
    n = int(input("Enter desired number of discs: "))
    print(hanoi(n)-1)
    
if __name__ == "__main__":
    main()
