from cs50 import get_int

height = 0
row = 1

while height < 1 or height > 8:
    height = get_int("Height: ")

while row <= height:
    i = row + 1
    while i <= height:
        print(" ", end='')  # end='' = print in the same line
        i += 1
    for j in range(row):
        print("#", end='')
    print("  ", end='')
    for k in range(row):
        print("#", end='')
    print("")
    row += 1
    