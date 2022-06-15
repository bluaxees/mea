from __future__ import print_function

def main():
    long_string = input("Enter a string: ")

    e1, e2, e3 = '', '', ''
    cntr = 0

    for letter in long_string:
        e1 = e2
        e2 = e3
        e3 = letter
        if (e1 == 'e' and e2 == 'e' and e3 == 'e'):
            cntr += 1

    print("I found 'eee'", cntr, "times")

if __name__ == "__main__":
    main()