import csv

# Input and output file paths
INPUT_FILE = 'jira_all.csv'
OUTPUT_FILE = 'jira_sprint_python_issues.txt'

########### User Configuration #############

Sprint_Coloumn = 4 # Sprint Coloumn

############################################




def find_highest_sprint(file_path):
    highest_sprint = None
    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip header
        for row in reader:
            if row[4]:
                sprint =  int(row[4].replace("Sprint ",""))  # Sprint is in the 5th column (index 4)
                print(sprint)
                if (highest_sprint is None or sprint > highest_sprint):
                    highest_sprint = sprint
    return highest_sprint

def filter_issues_by_sprint(file_path, highest_sprint, output_file):
    with open(file_path, 'r') as infile, open(output_file, 'w', newline='') as outfile:
        reader = csv.reader(infile)
        writer = csv.writer(outfile)
       
        for row in reader:
            if row[4]:
                if  int(row[4].replace("Sprint ","")) == highest_sprint:  # Sprint is in the 5th column (index 4)
                    print(row)
                    writer.writerow(row)

def main():
    highest_sprint = find_highest_sprint(INPUT_FILE)
    if highest_sprint is None:
        print("No sprint found.")
        return
    print(f"Highest sprint found: {highest_sprint}")
    filter_issues_by_sprint(INPUT_FILE, highest_sprint, OUTPUT_FILE)
    print(f"Filtered issues have been saved to {OUTPUT_FILE}")

if __name__ == "__main__":
    main()
