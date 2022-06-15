def propdiv_sum(num):
    sum = 0
    n = 2
    if num <= 1:
        return 0
    while n**2 <= num:
        if num % n == 0:
            if n == num / n: 
                sum += n
            else:
                sum += n + num/n
        n += 1
    return (int(sum + 1))

def frennynummy(a,b):
    if propdiv_sum(a)/a == propdiv_sum(b)/b and a != b:
        return 1
    else:
        return 0
	

def determinant(i,j):
    a = propdiv_sum(i) + propdiv_sum(j)
    b = i + j
    c = float(a/b)
    return c
    print(determinant(i,j))	

def rarara(a,b,c):
    for i in range(b,c):
        for j in range(c,b,-1):
            if frennynummy(i,j) == 1:
                if i <= j: 
                    if determinant(i,j) > a:
                        print (i,j)
		

a = float(input("Input ratio here: "))
b = int(input("Input 1st number here: "))
c = int(input("Input 2nd number here: "))
rarara(a,b,c)	
