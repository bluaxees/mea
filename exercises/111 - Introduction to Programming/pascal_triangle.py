def pascals(nth):
    if nth == 0:
        return []
    elif nth == 1:
        return [[1]]
    else:
        row = [1]
        res = pascals(nth-1)
        last = res[-1]
        for i in range(len(last)-1):
            row.append(last[i]+last[i+1])
        row += [1]
        res.append(row)
    return res
        
def main():
    nth = int(input("Get what line of the pascal's triangle? "))
    pasc = pascals(nth)
    del pasc[:nth-1]
    print(pasc)
    
if __name__ == "__main__":
    main()

