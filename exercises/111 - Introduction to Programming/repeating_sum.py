from __future__ import print_function

def main():
    #assume all inputs are integers
    val = int(input("Enter a single digit integer (1-9): "))
    while ((val < 1) or (val > 9)):
        val = int(input("Enter a single digit integer (1-9): "))
    n1 = val
    #print(n1)
    n2 = n1 * 10 + n1
    #print(n2)
    n3 = n2 * 10 + n1
    #print(n3)
    n4 = n3 * 10 + n1
    #print(n4)
    n5 = n4 * 10 + n1

    sn2 = str(n1) + str(n1)
    sn3 = sn2 + str(n1)
    sn4 = sn3 + str(n1)
    sn5 = sn4 + str(n1)

    print("The sum of", n1, "+", sn2, "+", sn3, "+", sn4, "+", sn5, "is", n1 + n2 + n3 + n4 + n5)

if __name__ == "__main__":
    main()