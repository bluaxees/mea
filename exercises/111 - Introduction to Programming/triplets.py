
#Declaration of integer input variables
#with x and y being the short and long legs of the triangle 
#respectively and z as the hypotenuse
x=int(input('Enter first number: '))
y=int(input('Enter second number: '))
z=int(input('Enter third number: '))

#Error handling: Only positive integers
#Loop is executed as long as either x, y, or z is not positive (optional)
while (x<1 or y<1 or z<1):
	x=int(input('Numbers must all be positive. Enter first number: '))
	y=int(input('Enter second number: '))
	z=int(input('Enter third number: '))

#Error handling: Following problem specifications that a<b<c, 
#where in this case, x<y<z.
#If x<y AND y<z (because Python does not recognize x<y<z), 'A' is executed.
#Else, 'B' is executed

#A
#Conditional statement. 
#If the 'hypotenuse' squared is equal to the result 
#from x*x + y*y, A1 is executed. 
#Else, A2 is executed

if (x<y and y<z):
	#A1
	if ((z*z==x*x+y*y)):
		print(str(x) + ', ' + str(y) + ', and ' + str(z) +' form a Pythagorean triplet')
		#String concatenation/type conversion; remember that you can't concatenate integers with strings
	#A2
	else:
		print(str(x) + ', ' + str(y) + ', and ' + str(z) +' do not form a Pythagorean triplet')
		#String concatenation/type conversion
#B
else:
		print(str(x) + ', ' + str(y) + ', and ' + str(z) +' do not form a Pythagorean triplet')
		#String concatenation/type conversion 
