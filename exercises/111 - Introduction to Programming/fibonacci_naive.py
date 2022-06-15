#Get input from user, and convert to int
x = int(input("Please enter a number: "))

#Error Handling: While input is invalid, keep asking for input
while x<0:
    x = int(input("Number should be positive: "))

#The nth number in the Fibonacci sequence is the sum of the (n-2)th
#and the (n-1)th numbers, where the first two numbers are 1 and 1.
#Thus, we use 3 variables to remember n-2, n-1, and n all at the same
#time, and set n-2 and n-1 to 1 at the start.

past = 1    #Fibonacci sequence generators
pres = 1    #Fun fact: If you change pres to 3, it will generate the Lucas series!
futu = 0

print("Fibonacci sequence up to n = " + str(x))

for a in range(x):  #Setup the loop to iterate x times
    print(past)         #we print past in order to print the first 1 first
    futu = past + pres  #calculate n
    
    past = pres         #update n-2
    pres = futu         #update n-1
