#!/usr/bin/env bash

die_test_auto () #TODO: add progress bar because it takes a long time to run
{
    printf "\n${CYAN}=== Starting tests where program should end with death or enough eaten ===\n${RESET}"
    while IFS="" read -r -u 3 input || [ -n "$input" ] # read input from fd 3
    do
        read -r -u 3 result # read desired result description from input.txt
        printf "\nTest: ${BLUEBG}${WHITE}[$input]${RESET} | ${PURP}$result${RESET}\n\n"
        
        # Run the program up to 5 times
        for i in $(seq 1 "$MAX_RETRIES"); do
            # Run the program with test case input and capture the output
            output=$($1 $input 2>&1)
            last_line=$(echo "$output" | tail -n 1) # Get the last line of the output
            
            # Check if "died" is in the last line
            if ! echo "$last_line" | grep -q "died"; then
                printf "${RED}KO${RESET} - 'died' not found in the last line\n"
                break # Exit the loop early on failure
            fi
        done
        
        # If the loop completes all 5 iterations successfully
        if [ "$i" -eq $MAX_RETRIES ]; then
            printf "${GREEN}OK${RESET}\n"
        fi
    done 3< ./data/yes-die.txt   # open file is assigned fd 3
    exec 3<&- # close fd 3
}

