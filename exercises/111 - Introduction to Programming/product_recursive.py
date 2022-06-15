product = 0

def prod(x,y):
    if y == 1:
        return x
    else:
        product = x + prod(x,y-1)
        return product
        
def main():
    x = int(input("Multiply: "))
    y = int(input("with: "))
    print(prod(x,y))
    
if __name__ == "__main__":
    main()
