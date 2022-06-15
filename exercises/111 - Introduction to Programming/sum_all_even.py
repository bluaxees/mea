
#Declaration of integer input variable
x = int(input("Please enter a number from 0 to 99: "))

#Error handling: Will keep asking until user gives correct input
while not(x<100 and x>=0):
    x = int(input("Please enter a number from 0 to 99: "))

#Declaration of variable to be used for sum
#'sum' is already a function in Python, so it can't be a variable name
_sum = 0

print("All even numbers from 0 to "+str(x)+":")
for a in range(x+1):        #iterate through all numbers from 0 to x
    if (a%2)==0:            #only true when a is even, since even%2 = 0
        print(a)            #print current list item
        _sum+=a             #add to sum

print("Sum: "+str(_sum))    #print total sum after loop is done



#Declaration of integer input variable
x = int(input("Please enter a number from 0 to 99: "))

#Error handling: Will keep asking until user gives correct input
while not(x<100 and x>=0):
    x = int(input("Please enter a number from 0 to 99: "))

#Declaration of variable to be used for sum
#'sum' is already a function in Python, so it can't be a variable name
_sum = 0

print("All even numbers from 0 to "+str(x)+":")
for a in range(0,x+1,2):    #range will be from 0 to x (since range doesn't...
                            #...include the last value), and will only
                            #increment by 2, thus, will only contain even numbers
    
    print(a)            #print current list item
    _sum+=a             #add to sum

print("Sum: "+str(_sum))    #print total sum after loop is done



