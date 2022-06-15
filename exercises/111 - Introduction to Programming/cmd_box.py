#Take an integer input from the user and assign it to the 'length' variable
length=int(input('Enter length: '))

#Similarly, take an integer input from the user and assign it to the 'width' variable
width=int(input('Enter width: '))

#ERROR HANDLING. Following problem specifications of 2<length<=50 and 2<width<=20
#Only one loop is used to simplify code
while length<3 or length>50 or width<3 or width>20:
		print('Length/Width out of range')
		print('2<Length<=50 and 2<Width<=20')
		length=int(input('Enter length: '))
		width=int(input('Enter width: '))

#Declare a range
x=range(width)

#x has a value of [0, 1, 2, ..., width-1]
 
for num in x:
	print('*'*length)	#Multiply the character by the given length 
				#since Python only prints downward after 
				#each new print()

#In comparison to the 'while-loop' solution, the for-loop executes its 
#statements as long as there are elements in the range.
#Once exhausted of elements, the for-loop terminates.

#Optional print message at the end
print('The box is ' + str(length) + ' characters long and ' + str(width) + ' characters wide.')



#Declaration of a variable, a 'starting point'
#Common programming practice to start at zero rather than 1
x=0

#Take an integer input from the user and assign it to the 'length' variable
length=int(input('Enter length: '))

#Similarly, take an integer input from the user and assign it to the 'width' variable
width=int(input('Enter width: '))

#Error handling. Code must be logical.
#Loop is only executed while the width is greater than the length
while width>length:
	print('Length must be longer than the width') 
	length=int(input('Enter length: '))
	width=int(input('Enter width: '))

#Error handling. Following problem specifications of 2<length<=50 and 2<width<=20
#Only one loop is used to simplify code
while length<3 or length>50 or width<3 or width>20:
		print('Length/Width out of range')
		print('2<length<=50 and 2<width<=20')
		length=int(input('Enter length: '))
		width=int(input('Enter width: '))

while x<width:			#Loop is executed while x is 
				#less than the declared width 
	print('*'*length)	#Multiply the character by the given length
				#since Python only prints downward after
				#each new print()
	x+=1			#UPDATE. x = 1 after the first iteration, 
				#x = 2 after the second, and so on 

#Example
#Length = 6, width = 3
#First iteration
#******
#Second iteration in addition to the first
#******
#******
#Third iteration in addition to the first and second
#******
#******
#******
#Program terminates after last line is printed

#Optional print message at the end
print('The box is ' + str(length) + ' characters long and ' + str(width) + ' characters wide.')




length = int(input("Enter length: ")) #get length in int
width = int(input("Enter width: "))   #get width in int

#ERROR HANDLING. Following problem specifications of 2<length<=50 and 2<width<=20
while length<3 or length>50 or width<3 or width>20:
    print('Length/Width out of range')
    print('2<Length<=50 and 2<Width<=20')
    length=int(input('Enter length: '))
    width=int(input('Enter width: '))

for a in range(width):      #iterate for each row (i.e. 'width' times)
    
    if a==0 or a==width-1:  #if first row or last row,
        print("*"*length)   #print * 'length' times
        
    else:                   #if middle row,
        print("*" + " "*(length-2) + "*")
        #print '*' for left wall, print 'length-2' spaces, then print '*' for right wall

#Optional print message at the end
print('The box is ' + str(length) + ' characters long and ' + str(width) + ' characters wide.')


 
	