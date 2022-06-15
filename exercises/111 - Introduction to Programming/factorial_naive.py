#Get input from user, and convert to int
x = int(input("Please enter a number: "))

#Error Handling: While input is invalid, keep asking for input
while x<0 or x>50:
    x = int(input("Number should be positive and less than 50: "))

#n! is equal to 1*2*3*4*...*n
#So basically, we are counting from 1 to n, but cumulatively multiplying
#each number along the way.
#To do this, we just make a for loop that counts up to x, and just multiply
#the current number to a variable for each iteration.
    
fact = 1            #We start at 1 since 0!=1!=0
for a in range(x):  #Setup the loop to iterate x times
    fact *= (a+1)   #Since the loop starts counting at 0 and ends at x-1,
                    #we use a+1 here so that the numbers we multiply are
                    #from 1 to x instead.
                    #This has the covenient side-effect of inputs 0 and 1
                    #outputting '1', which is the correct answer!
                    #For other solutions, an input of 0 usually requires
                    #an additional if statement since 0! is weird.

#Now just print the output.                    
print(str(x) + "! is equal to: " + str(fact))
