x = int(input("Enter a number: "))  #get input

while not(x>=20 and x<=99):         #keep asking until valid input is given
    x = int(input("'Di ko 'yan kaya huhu; from 20 to 99 lang pls: "))

#The fundamental realization that one must reach in order to solve this problem
#is the fact that the name of the numbers from 20 to 99 can be separated into
#two parts that have no effect on each other: the tens place and the ones place

#To get the tens place, just get the floor quotient by 10
tens = x//10
#To get the ones place, just get the modulo by 10
ones = x%10

#For relationships that computers don't understand such as numbers to human
#language, you sometimes have no choice but to semi-brute-force your way through
#(unless another human already did the convertions for you)

#Here's a long elif chain that stores the desired tens place output in tens_t
if tens==2:
    tens_t = "Twenty"
elif tens==3:
    tens_t = "Thirty"
elif tens==4:
    tens_t = "Forty"
elif tens==5:
    tens_t = "Fifty"
elif tens==6:
    tens_t = "Sixty"
elif tens==7:
    tens_t = "Seventy"
elif tens==8:
    tens_t = "Eighty"
elif tens==9:
    tens_t = "Ninety"

#Here's another long chain that stores the ones into ones_t
if ones==1:
    ones_t = "-one"
elif ones==2:
    ones_t = "-two"
elif ones==3:
    ones_t = "-three"
elif ones==4:
    ones_t = "-four"
elif ones==5:
    ones_t = "-five"
elif ones==6:
    ones_t = "-six"
elif ones==7:
    ones_t = "-seven"
elif ones==8:
    ones_t = "-eight"
elif ones==9:
    ones_t = "-nine"

#For long and repetitive code like this, Ctrl+C and Ctrl+V are your friends!

#Now, just print the output
print("You entered: " + tens_t + ones_t + ".")
