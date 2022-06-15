def main():
    ans = 0
    term1 = 1
    term2 = 2

    while term1 <= 4000000:
        if not(term1 % 2):
            ans += term1
        term1, term2 = term2, term1 + term2

    print(ans)

if __name__ == "__main__":
    main()