import csv

########### User Configuration #############

# Input and output file paths
INPUT_FILE = 'jira_all_issues.csv'
OUTPUT_FILE = 'jira_sprint_issues.txt'
s
Sprint_Coloumn = 4 # Sprint Coloumn

############################################


def find_highest_sprint(file_path):
    highest_sprint = None
    with open(file_path, 'r') as file:
        reader = csv.reader(file)
        next(reader)  # Skip header
        for row in reader:
            if len(row) > 1 and row[1].startswith("Sprint "):  # Ensure the column starts with "Sprint "
                try:
                    sprint = int(row[1].replace("Sprint ",""))
                    print(sprint)
                    if highest_sprint is None or sprint > highest_sprint:
                        highest_sprint = sprint
                except ValueError:
                    continue  # Skip rows with invalid sprint numbers
    return highest_sprint

def filter_issues_by_sprint(file_path, highest_sprint, output_file):
    with open(file_path, 'r') as infile, open(output_file, 'w') as outfile:
        reader = csv.reader(infile)
        next(reader)  # Skip header
        
        # Write sprint number at the top
        outfile.write(f"[Sprint {highest_sprint}]\n\n")
        
        for row in reader:
            if len(row) > 1 and row[1].startswith("Sprint "):  # Ensure the column starts with "Sprint "
                try:
                    if int(row[1].replace("Sprint ","")) == highest_sprint:
                        task_id = row[0]
                        task_title = row[2]
                        assignee = row[4]
                        task_description = row[2]
                        # Write task information in the desired format
                        outfile.write(f"[{task_id}] : {task_description}\n\n")
                except ValueError:
                    continue  # Skip rows with invalid sprint numbers

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
