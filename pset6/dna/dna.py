import csv
import sys

# def main()
if len(sys.argv) != 3:
    sys.exit("Usage: python DNA.py DATABASE sequence")

database = []
STR_name = []
# TODO: Read dna database memory from file
with open(str(sys.argv[1]), "r") as file:
    reader = csv.DictReader(file)
    dict_from_csv = dict(list(reader)[0])
    # making a list from the keys of the dict
    STR_name = list(dict_from_csv.keys())
    file.seek(0)
    for name in reader:
        database.append(name)

STR_name.remove("name")
# read the sequence file 
f = open(str(sys.argv[2]), "r")
sequence = f.read()

# search for the repetitive pattern in the sequence
combination = []
counter = {}
counter_max = {}

i = 0

for i in range(len(sequence)+1):
    for j in range(4, 10):
        for k in range(len(STR_name)):
            if sequence[i:i+j] == STR_name[k]:
                combination.append(str(sequence[i:i+j]))
                length = len(sequence[i:i+j])
                if sequence[i:i+j] != sequence[i+length:i+j+length]:
                    combination.append("!")

for x in range(len(combination)):
    if combination[x] in STR_name:
        if combination[x] not in counter:
            counter[combination[x]] = 1
            counter_max[combination[x]] = 1
        if combination[x] == combination[x + 1]:
            counter[combination[x]] += 1
        elif combination[x] != combination[x + 1]:
            if counter_max[combination[x]] < counter[combination[x]]:
                counter_max[combination[x]] = counter[combination[x]]
            else: 
                continue
            counter[combination[x]] = 1


# print the result 
for y in range(1, len(database)):
    checker = 0
    for key in STR_name:
        if counter_max.get(key) == int(database[y].get(key)):
            checker += 1
        if checker == len(STR_name):
            print(database[y]["name"])
            exit()

print("No Match")