import os

def parse_cppcheck_output(file_path):
    mandatory_errors = []
    optimized_output = []
    mandatory_keywords = ["Major", "Critical", "Mandatory"]

    with open(file_path, 'r') as file:
        lines = file.readlines()

    for line in lines:
        # Check if the line contains a mandatory violation
        if any(keyword in line for keyword in mandatory_keywords):
            mandatory_errors.append(line)
        optimized_output.append(line)

    return mandatory_errors, optimized_output

def main():
    # Define ANSI escape code for red
    red = '\033[31m'
    reset = '\033[0m'
    green = '\033[32m'

    # Update this to the full path of MisraCkOut.txt if necessary
    input_file = r'.\MisraCkOut.txt'
    
    if not os.path.isfile(input_file):
        print(f"File not found: {input_file}")
        return 1  # Return error code
    
    mandatory_errors, optimized_output = parse_cppcheck_output(input_file)

    # Write the optimized output to a new file
    optimized_output_file = r'.\MisraC_Check\OptimizedMisraCkOut.txt'
    with open(optimized_output_file, 'w') as file:
        for line in optimized_output:
            file.write(line)

    # Print errors if there are mandatory violations
    if mandatory_errors:
        print("Mandatory violations found:")
        for error in mandatory_errors:
            print(error.strip())
        print(f"{red}\n Error: Mandatory violations detected !!! \n{reset}")
        return 1  # Return error code
    

    print(f"{green}\n No mandatory violations found. \n{reset}")
    return 0  # Return success code

if __name__ == "__main__":
    exit(main())