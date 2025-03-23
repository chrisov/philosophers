#!/bin/bash

source ./load_scripts.sh
source ./setup/colors.sh
source ./setup/constants.sh

# Counters
PASS=0
FAIL=0
TESTS=0

# checks params. If none given, assumes philo executable is in same directory as tester directory.
if [ "$#" -gt 1 ]; then
	printf "Too many parameters. Please only provide path to philo executable.\n"
	exit
elif [ "$#"  -lt 1 ]; then
	set $1 ../philo
fi

# checks if given executable path and file is valid.
if [ ! -f "$1" ]; then
	printf "$1 not found or invalid file. Please (re)make philo executable first.\n"
	exit
fi

PROGRESS_BAR_WIDTH=50  # progress bar length in characters

draw_progress_bar() {
  # Arguments: current value, max value, unit of measurement (optional)
  local __value=$1
  local __max=$2
  local __unit=${3:-""}  # if unit is not supplied, do not display it

  # Anti zero-division protection
  if (( $__max < 1 )); then __max=1; fi

  # Calculate percentage with floating-point precision
  local __percentage=$(awk -v value="$__value" -v max="$__max" 'BEGIN { printf "%.2f", (value / max) * 100 }')

  # Rescale the bar according to the progress bar width
  local __num_bar=$(awk -v perc="$__percentage" -v width="$PROGRESS_BAR_WIDTH" 'BEGIN { printf "%.0f", (perc * width) / 100 }')

  # Draw progress bar
  printf "["
  for (( b=1; b<=__num_bar; b++ )); do printf "#"; done
  for (( s=1; s<=$(( PROGRESS_BAR_WIDTH - __num_bar )); s++ )); do printf " "; done
  printf "] %3.0f%% (%d / %d %s)\r" "$__percentage" "$__value" "$__max" "$__unit"
}

choose_test() {
	read -rn1 -p $'\nChoose test to run:\t
	[1] check invalid input (auto)\t
	[2] die tests - auto (can take a while)\t
	[3] no-die limited meals test (auto)\t
	[4] no-die tests (can take a while)\t
	[5] no-die tests (auto)\t
	[6] check data races && deadlocks (needs docker) \t
	[7] check timestamps - The Chefs Special \t
	[8] The Chaos Feast (auto)\t
	[ESC] exit tester\n\n' choice
    printf "\n"
    case $choice in
		1) check_invalid_inputs "$1";;
        2) die_test_auto "$1" ;;
		3) check_limited_meals "$1";;
        4) no_die_test "$1" ;;
		5) no_die_test_auto "$1" ;;
		6) run_helgrind "$1";;
        7) check_timestamps "$1" && process_files;;
		8) check_invalid_inputs "$1" && check_limited_meals "$1" && 
			die_test_auto "$1" && no_die_test_auto "$1" && check_timestamps "$1" && process_files;;
        $'\e') exit 0 ;;
        *) printf "${RED}Invalid choice\n${RESET}"; choose_test "$1" ;;
    esac
}

printf "${BOLD}\n💭 The 42Philosophers Helper 💭\n${RESET}"
printf " ____  _     _ _                       _                   \n";
printf "|  _ \| |__ (_) | ___  ___  ___  _ __ | |__   ___ _ __ ___ \n";
printf "| |_) | '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|\n";
printf "|  __/| | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \\ \n";
printf "|_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/\n";
printf "                                |_|    by Abdallah Zerfaoui\n\n";
printf "\nThis tester allows you to test:\n\n"
printf "\ta. Invalid input handling\n"
printf "\t- checks if the program handles invalid input correctly.\n\n"
printf "\tb. when philosophers should die\n"
printf "\t- checks if the program stops when a philosopher dies in the expected time.\n\n"
printf "\tc. when no philosophers should die\n"
printf "\t- checks if the program runs for a certain time without any philosopher dying.\n"
printf "\t with and without number of meals limitation.\n\n"
printf "\td. check for data races and deadlocks\n"
printf "\t- using helgrind, drd, and sanitizer.\n\n"
printf "\te. check timestamps\n"
printf "\t- checks if the program runs for a certain time without mixing timestamps\n\n"
printf "\tf. The Chaos Feast\n"
printf "\t- runs all tests in sequence.\n\n"
# printf "\t1. when your program should stop on death or when all philos have eaten enough\n"
# printf "\t- to be checked manually by the user, based on the expected result listed in yes-die.txt.\n\n"
# printf "\t2. when no philosophers should die\n"
# printf "\t- this is checked automatically if the program runs for x seconds (default 10) without death.\n"
choose_test "$1"
