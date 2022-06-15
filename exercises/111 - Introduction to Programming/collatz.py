highest_step = 0
highest_step_number = 0

#loop from 1 to 1 million
for integer in range(1,1000000):

    #we assign integer to another variable because integer will be reduced to 1 after the process
    candidate = integer

    #we start our step counter with 1 because the initial number is considered as one step
    step_ctr = 1

    print("For number: " + str(integer))

    #counting steps loop
    while (integer != 1):

        #if even
        if (integer % 2) == 0:
            integer /= 2                        #divide by 2
            step_ctr += 1                       #increment step counter

        #if odd
        else:
            integer *= 3                        #multiply by 3
            integer += 1                        #add 1
            step_ctr += 1                       #increment step counter

    #updates number with highest steps and the highest step counter
    if step_ctr > highest_step:
        highest_step_number = candidate
        highest_step = step_ctr

#printing
print("Current highest counter: #" + str(highest_step_number) + " has " + str(highest_step) +  " steps")






        
        


