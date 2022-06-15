from __future__ import print_function

def main():
    in_str = input("Enter string: ")
    upper, lower = 0, 0

    for letter in in_str:
        if letter.isupper():
            upper += 1
        elif letter.islower():
            lower += 1
        else:
            pass

    print("# of uppercase letters:", upper)
    print("# of lowercase letters:", lower)

if __name__ == "__main__":
    main()