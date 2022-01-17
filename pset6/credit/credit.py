from cs50 import get_string 
import math

number = get_string("Number: ")
length = len(number)


SumOdd = 0
SumEven = 0

s = []
for i in range(length):
    s.append(int(number[i]))


if length % 2 == 1:
    for i in range(0, length, 2):
        SumOdd += s[i]
    for j in range(1, length, 2):
        if 2 * s[j] >= 10:
            t = math.floor((2 * s[j]) / 10) + (2 * s[j]) % 10
        else:
            t = 2 * s[j]
        SumEven += t
        
else:
    for i in range(1, length, 2):
        SumOdd += s[i]
    for j in range(0, length, 2):
        if 2 * s[j] >= 10:
            t = math.floor((2 * s[j]) / 10) + (2 * s[j]) % 10
        else:
            t = 2 * s[j]
        SumEven += t
        
print(SumOdd)
print(SumEven)

if (SumOdd + SumEven) % 10 != 0:
    print("INVALID")
elif s[0] == 4 and (length == 13 or length == 16):
    print("VISA")
elif s[0] == 3 and (s[1] == 4 or s[1] == 7) and length == 15: 
    print("AMEX")
elif s[0] == 5 and s[1] > 0 and s[1] < 6 and length == 16:
    print("MASTERCARD")
else:
    print("INVALID")