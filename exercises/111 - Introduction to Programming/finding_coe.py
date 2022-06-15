from __future__ import print_function

def main():
    long_string = input("Enter a string: ")

    c, o, e = '', '', ''
    cntr = 0

    for letter in long_string:
        c = o
        o = e
        e = letter
        #print(c)
        #print(o)
        #print(e)
        if (c == 'c' and o == 'o' and e == 'e'):
            cntr += 1

    print("I found 'coe'", cntr, "times")

if __name__ == "__main__":
    main()