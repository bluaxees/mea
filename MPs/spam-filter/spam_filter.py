#Spam Filter
#BELEN, Alarcon Ace H.
#2018-04736

from collections import Counter
from math import log
from email import message_from_string

alpha_string = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'

count_spam = 0
count_ham = 0
count_all = 0

email_type = []
file_path = []
top_5k_words = []
trainer_wordlist = []
spam_words = []
ham_words = []
email_type_plus_path = []
coined_type_path = []

spamcoin_flow = {}
hamcoin_flow = {}
spamcoin_ebb = {}
hamcoin_ebb = {}
#None
def labelEmail():
    '''
    Reads the file labels and updates two lists; the classification of the individual emails and their file directory
    '''
    some_counter = 0
    fh = open('trec06p-eee111/labels', 'r')
    
    for line in fh:
        (e_type, f_path) = line.split()
        email_type.append(e_type)
        file_path.append(f_path.strip('..'))
        if some_counter >= 21300:
            email_type_plus_path.append((f_path.strip('..'), e_type))
            some_counter += 1
        else:
            some_counter += 1

    fh.close()

def isbeta(word):
    '''
    Checks whether the input is a word; similar to how isalpha() functions except that it only considers Romanized characters
    '''
    if word == "":
        return False
    for letter in word:
        if letter in alpha_string:
            continue
        else:
            return False
    return True

def listWords_A(file_directory):
    '''
    Returns a list of unique words found in an email and appends a list to a backup list to access it later.
    '''
    fh = open(file_directory, 'r', encoding = 'utf-8', errors = 'ignore')
    email_words = []
    unique_email_words = []
    body = []

    i = fh.read()
    pseudobody = message_from_string(i)
    if pseudobody.is_multipart():
        for part in pseudobody.get_payload():
            if part.is_multipart():
                for another_part in part.get_payload():
                    body.append(another_part.get_payload())
            else:
                body.append(part.get_payload())
    else:
        body.append(pseudobody.get_payload())

    for string in body:
        for word in str(string).split():
            if isbeta(word) == True:
                email_words.append(word.lower())
            elif isbeta(word[:-1]) == True:
                email_words.append(word[:-1].lower())
            else:
                continue

    fh.close()
    unique_email_words = list(set(email_words))
    trainer_wordlist.append(unique_email_words)
    
    return unique_email_words

def listWords_B(file_directory):
    '''
    Appends a list of unique words found in an email to a backup list to access it later.
    '''
    fh = open(file_directory, 'r', encoding = 'utf-8', errors = 'ignore')
    email_words = []
    unique_email_words = []
    body = []

    i = fh.read()
    pseudobody = message_from_string(i)
    if pseudobody.is_multipart():
        for part in pseudobody.get_payload():
            if part.is_multipart():
                for another_part in part.get_payload():
                    body.append(another_part.get_payload())
            else:
                body.append(part.get_payload())
    else:
        body.append(pseudobody.get_payload())

    for string in body:
        for word in str(string).split():
            if isbeta(word) == True:
                email_words.append(word.lower())
            elif isbeta(word[:-1]) == True:
                email_words.append(word[:-1].lower())
            else:
                continue

    fh.close()
    unique_email_words = list(set(email_words))
    trainer_wordlist.append(unique_email_words)

def readandcount_train():
    '''
    Reads all the files from the trainer set and lists the words found on a list depending on their classification.
    Simultaneously, counts the number of emails inside the set based on their classification
    '''
    global count_all
    global count_spam
    global count_ham

    for i in range(0, 21300):
        file_directory = 'trec06p-eee111' + file_path[i]
        if email_type[i] == 'spam':
            spam_words.extend(listWords_A(file_directory))
            count_all += 1
            count_spam += 1
        else:
            ham_words.extend(listWords_A(file_directory))
            count_all += 1
            count_ham += 1

def readandcount_test():
    '''
    Reads all the files from the test set
    '''

    for i in range(21300, 37822):
        file_directory = 'trec06p-eee111' + file_path[i]
        listWords_B(file_directory)

def fivek():
    '''
    Writes the 5000 most common words found on the trainer set in a file, including their occurrences on spam emails, occurrences on ham emails and the total number of occurences
    '''
    global top_5k_words
    top_5k_words = [(k,v) for k,v in dict(Counter(sorted(ham_words + spam_words)).most_common(5000)).items()]
    counter_spam = dict(Counter(spam_words).most_common())
    counter_ham = dict(Counter(ham_words).most_common())

    for n in range(len(top_5k_words)):
        top_5k_words[n] = top_5k_words[n] + (counter_spam.get(top_5k_words[n][0], 0),)
        top_5k_words[n] = top_5k_words[n] + (counter_ham.get(top_5k_words[n][0], 0),)

    fh = open('trainer_top_5k_words.txt', 'w')
    fh.write('\n'.join('%s %s %s %s' % word for word in top_5k_words))
    fh.close()

def coin(Lambda):
    '''
    Calculates the probability that a word exists on an email given the email's classification using Lambda Smoothing
    '''
    global count_spam
    global count_ham

    fh = open('trainer_top_5k_words.txt', 'r')

    for line in fh:
        (word, all_occurrences, spam_occurrences, ham_occurrences) = line.split()
        spamcoin_flow[word] = float((int(spam_occurrences) + Lambda)/(count_spam + 5000*Lambda))
        hamcoin_flow[word] = float((int(ham_occurrences) + Lambda)/(count_ham + 5000*Lambda))
        spamcoin_ebb[word] = float(1 - (int(spam_occurrences) + Lambda)/(count_spam + 5000*Lambda))
        hamcoin_ebb[word] = float(1 - (int(ham_occurrences) + Lambda)/(count_ham + 5000*Lambda))

def spamorham():
    '''
    Determines whether an email is spam or ham based on the probability derived using Bayes' Theorem; returns the program's count of spam and ham emails for debugging purposes 
    '''
    global count_all
    global count_spam
    global count_ham
    my_spam_count = 0
    my_ham_count = 0

    for i in range(21300, 37822):
        probability_spam = log(count_spam/count_all)
        probability_ham = log(count_ham/count_all)
        for word in top_5k_words:
            if word[0] in trainer_wordlist[i]:
                probability_spam += log(spamcoin_flow[word[0]])
                probability_ham += log(hamcoin_flow[word[0]])
            else:
                probability_spam += log(spamcoin_ebb[word[0]])
                probability_ham += log(hamcoin_ebb[word[0]])
        if probability_spam > probability_ham:
            coined_type_path.append((file_path[i], 'spam'))
            my_spam_count += 1
        else:
            coined_type_path.append((file_path[i], 'ham'))
            my_ham_count += 1
    return (my_spam_count, my_ham_count)

def darts():
    '''
    Computes for the accuracy and precision
    '''
    FP = 0
    FN = 0
    TP = 0
    TN = 0
    precision = 0
    recall = 0
    j = sorted(email_type_plus_path)
    k = sorted(coined_type_path)

    for i in range(len(email_type_plus_path)):
        if email_type_plus_path[i][1] == 'spam' and coined_type_path[i][1] == 'spam':
            TP += 1
        elif email_type_plus_path[i][1] == 'spam' and coined_type_path[i][1] == 'ham':
            FN += 1
        elif email_type_plus_path[i][1] == 'ham' and coined_type_path[i][1] == 'spam':
            FP += 1
        else:
            TN += 1

    precision = TP/(TP+FP)
    recall = TP/(TP+FN)

    return (precision, recall)

#This is the main function
labelEmail()
print ('read labels done')

readandcount_train()
print ('read trainer set done')

readandcount_test()
print ('read test set done')

fivek()
print ('write most common words done')

Lambda = 1
coin(Lambda)
print ('calculate probability done')

spamorham()
print ('email classification done')

(precision, recall) = darts()

print ('Lambda: ', Lambda)
print ('Precision:', precision)
print ('Recall:', recall)
print ('')

Lambda = 0.05
coined_type_path = []
coin(Lambda)
print ('calculate probability done')

spamorham()
print ('email classification done')

(precision, recall) = darts()

print ('Lambda: ', Lambda)
print ('Precision:', precision)
print ('Recall:', recall)
print ('')

Lambda = 0.1
coined_type_path = []
coin(Lambda)
print ('calculate probability done')

spamorham()
print ('email classification done')

(precision, recall) = darts()

print ('Lambda: ', Lambda)
print ('Precision:', precision)
print ('Recall:', recall)
print ('')

Lambda = 0.5
coined_type_path = []
coin(Lambda)
print ('calculate probability done')

spamorham()
print ('email classification done')

(precision, recall) = darts()

print ('Lambda: ', Lambda)
print ('Precision:', precision)
print ('Recall:', recall)
print ('')

Lambda = 2.0
coined_type_path = []
coin(Lambda)
print ('calculate probability done')

spamorham()
print ('email classification done')

(precision, recall) = darts()

print ('Lambda: ', Lambda)
print ('Precision:', precision)
print ('Recall:', recall)
print ('')