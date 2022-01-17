from cs50 import get_string

paragraph = get_string("Text: ")
    
# count words
word_count = paragraph.split()
W = len(word_count)

# count letters
# count sentence 
letter_count = []
L = 0
S = 0

length = len(paragraph)

for i in range(length):
    letter_count.append(ord(paragraph[i]))

for i in range(len(letter_count)):
    if letter_count[i] > 64 and letter_count[i] < 90:  # use ascii code
        L += 1
    elif letter_count[i] > 96 and letter_count[i] < 123:
        L += 1
    elif letter_count[i] == 33 or letter_count[i] == 46 or letter_count[i] == 63:
        S += 1

    
# use formula 
avg_L = L*100/W
avg_S = S*100/W

grade = round(0.0588 * avg_L - 0.296 * avg_S - 15.8)

# print result 
if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print("Grade", grade)
   
