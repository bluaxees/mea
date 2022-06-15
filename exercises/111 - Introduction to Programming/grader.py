#Ask for input. This time, we convert it to float since grades aren't always integers
x = float(input("Please input your grade: "))

#Python doesn't have a built-in EEE Grade converter, so just build one from scratch
#using a bunch of if statements:

if x>=92:
    grade = "1.00"      #Always aim for this grade! :)
elif x>=88:         #You will only advance to the next elif if the previous if/elifs
    grade = "1.25"  #aren't met, so there is no need to put the upper limit condition
elif x>=84:         #at least for this case.
    grade = "1.50"
elif x>=80:
    grade = "1.75"
elif x>=76:
    grade = "2.00"
elif x>=72:
    grade = "2.25"
elif x>=68:
    grade = "2.50"
elif x>=64:
    grade = "2.75"
elif x>=60:
    grade = "3.00"
else:
    grade = "5.00"      #Actually unnecessary code since you won't ever get this, right?
    
#Now just print the output.
print("Your grade is: " + str(grade))




#A sign of programming skill is one's ability to think of solutions using only the least
#resources possible. For practical codes, however, extremely short but complex codes
#such as this one should be avoided, since it often becomes very hard to debug when
#something goes wrong, and even harder for someone else to understand how it works...
#They're fun and challenging mental exercises, though!

#For this problem, the restrictions are pretty strict, so I suggest starting big and
#then just keep simplifying it until you're able to pass the restrictions.

#Ask for input. We convert it to float since grades aren't always integers
x = float(input("Please input your grade: "))

#To do this with only a few if statements, we need to see a pattern of some sort in
#order to be able to simplify it using a loop. In this case, from 3.00 to 1.00, the
#cut-off increments by 4, and the grade decrements by 0.25.

#One solution is to start with the grade at 3.00, then if the grade hits the next
#threshold, the grade will decrement and the threshold will increase, up until the
#grade could become 1.00 (which happens at the 8th iteration)
grade = 3.00            #start at 3.00
for a in range(8):      #do this for 8 iterations
    if x >= 64+(4*a):   #cut-off increases by 4 for each iteration
        grade -= 0.25   #decrement grade by 0.25 if the grade passes cut-off
if x<60:                #5.00 doesn't follow the pattern above, so just use
    grade = 5.00        #another if statement
    
#Now finally, just print the output.
print("Your grade is: " + str(grade))
