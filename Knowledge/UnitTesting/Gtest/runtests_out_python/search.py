import sys

file_path = 'save.txt'
search_word = 'FAILED'
found = False

with open(file_path, 'r') as file:
    for line in file:
        if search_word in line:
            found = True
            break

if found:
    print(f"'{search_word}' found in the file.")
    sys.exit(1)  # Exit with a status code 1 to indicate the word was found
else:
    print(f"'{search_word}' not found in the file.")
    sys.exit(0)  # Exit with a status code 0 to indicate the word was not found
