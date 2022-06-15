#this code is straightforward, just remember the illustration demonstrated during the review
#to run program: cat scores.txt | python3 pipe.py

highest = 0
s_highest = 0
t_highest = 0
f_highest = 0
ctr = 0

num_scores = int(input())

while(1):

    if ctr == num_scores:
        break
    
    score = int(input())

    #getting highest
    if score > highest:
        f_highest = t_highest
        t_highest = s_highest
        s_highest = highest
        highest = score

    #getting second highest
    elif score > s_highest:
        f_highest = t_highest
        t_highest = s_highest
        s_highest = score

    #getting third highest
    elif score > t_highest:
        f_highest = t_highest
        t_highest = score
    
    #getting fourth highest
    elif score > f_highest:
        f_highest = score

    #increments counter
    ctr += 1

print("2nd Highest: " + str(s_highest))
print("3rd Highest: " + str(t_highest))
print("4th Highest: "+ str(f_highest))


