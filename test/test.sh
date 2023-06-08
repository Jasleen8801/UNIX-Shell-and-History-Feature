# test script for shell program

# compile the program
gcc -o shell src/main.c src/shell.c src/history.c src/utils.c

# function to run a command and check the output
run_command() {
    command=$1
    expected_output=$2

    echo "Executing command: $command"
    output=$(./shell <<< "$command")
    if [[ "$output" == "$expected_output" ]]; then
        echo "Pass"
    else
        echo "Fail: Expected output: $expected_output, Actual output: $output"
    fi
    echo
}

# Test case 1: Execute a single command
run_command "ls -l" "$(ls -l)"

# Test case 2: Execute a command in the background
run_command "sleep 5 &" ""

# Test case 3: Execute the most recent command from history
run_command "!!" "$(ls -l)"

# Test case 4: Execute a command from history by number
run_command "!2" "$(sleep 5 &)"

# Test case 5: Display command history
run_command "history" "$(printf "1 ls -l\n2 sleep 5 &\n3 !!\n4 !2\n5 history\n")"

# Clean up
rm shell


# To run the test script, open a terminal, navigate to the directory where your files are located, and execute the following command:
# chmod +x test.sh  # Give execute permissions to the script
# ./test.sh        # Run the test script
