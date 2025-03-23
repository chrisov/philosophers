#!/usr/bin/env bash

run_helgrind()
{
	if ! command -v valgrind &> /dev/null; then
	local RED='\033[0;31m'
	local RESET='\033[0m'
	echo -e "${RED}Error: Helgrind is not installed. Please install Valgrind to run Helgrind tests.${RESET}"
	return 1
	fi

	if [[ -z "$1" ]]; then
		echo -e "${RED}Error: No executable provided.${RESET}"
		return 1
	fi	
	local GREEN='\033[0;32m'
	local RED='\033[0;31m'
	local RESET='\033[0m'
	local FLAG=helgrind # or drd, helgrind	
	rm -f helgrind_output_*.txt
	for i in $(seq 2 10); do
		echo "Running Helgrind for test: $1 $i 800 200 200 3"	
		# Run Helgrind and capture the output
		output=$(valgrind --tool="$FLAG" "$1" $i $TIME_TO_DIE_H $TIME_TO_EAT_H $TIME_TO_SLEEP_H $NBR_MEALS_H 2>&1)
		echo "$output" > helgrind_output_"$i".txt	
		# Extract the error summary using grep and awk
		error_summary=$(echo "$output" | grep "ERROR SUMMARY:" | awk '{print $4}')	
		# Display the result based on the error count
		if [[ "$error_summary" -eq 0 ]]; then
			echo -e "${GREEN}No errors detected for: $1 $i 800 200 200 3${RESET}"
			# rm -f helgrind_output_"$i".txt
		else
		    echo -e "${RED}$error_summary errors detected for: $1 $i 800 200 200 3${RESET}"
		fi	
		echo "-----------------------------------"
	done
}

