def cycle(n):
    count = 1
    while n != 1:
        if n % 2 == 1:
            n *= 3
            n += 1
            count += 1
        else:
            n /= 2
            count += 1
    return count

#I assumed that a>b :p
a = int(input("Input a: "))
b = int(input("Input b: "))
lux = 0
kir = 0
for f in range (b, a):
    if cycle(f) > lux:
        kir = f
        lux = cycle(f)
print(lux)
print(kir)