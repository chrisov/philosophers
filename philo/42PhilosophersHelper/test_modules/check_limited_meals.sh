#!/usr/bin/env bash

check_limited_meals()
{
	# Check if the input file exists
	if [[ ! -f ./data/no-die-limited-meals.txt ]]; then
	    echo -e "${RED}Error: File ./data/no-die-limited-meals.txt not found.${RESET}"
	    return 1
	fi	
	# Check if the program executable is provided
	if [[ -z "$1" ]]; then
	    echo -e "${RED}Error: No executable provided.${RESET}"
	    return 1
	fi	

	echo -e "${CYAN}=== Starting limited meals tests ===${RESET}"	

	local passed=0
	local failed=0
	local total=0
	local total_meals=0

    while IFS="" read -r line || [[ -n "$line" ]]; do
        # Skip empty lines
        # Skip empty lines
        ((line_number++))
        if ((line_number % 2 == 0)); then
            continue
        fi
        if [[ -z "$line" ]]; then
            continue
        fi

        # Extract number of philosophers and meals from input
        local nbr_philo=$(echo "$line" | awk '{print $1}')
        local nbr_meals=$(echo "$line" | awk '{print $5}')

        # Run the program with the limited meals input
        echo "Testing limited meals input: $line"
        output=$($1 $line 2>&1)
        exit_code=$?

        # Count occurrences of "is eating"
        local eat_count=$(echo "$output" | grep -c "is eating")
		# printf "Eating count: $eat_count\n"

        # Check the result: OK if eat_count >= nbr_philo * nbr_meals and no errors
		total_meals=$((nbr_philo * nbr_meals))
        if [[ $exit_code -eq 0 && $eat_count -ge $total_meals ]]; then
            echo -e "${GREEN}OK: Handled limited meals correctly. Eating count: $eat_count${RESET}"
            ((passed++))
        else
            echo -e "${RED}KO: Eating count ($eat_count) is less than expected (${total_meals}}).${RESET}"
            ((failed++))
        fi
	done < ./data/no-die-limited-meals.txt	
	total=$((passed+failed))
	echo -e "${CYAN}=== Limited meals tests completed ===${RESET}"
	echo -e "${GREEN}PASSED: ${passed}/${total} | ${RED}FAILED: ${failed}/${total}"
}
