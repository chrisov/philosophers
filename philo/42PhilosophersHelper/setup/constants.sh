
# check_timestamps
readonly MINI_PHILOS=130
readonly MAX_PHILOS=200
readonly STEP=10
readonly TIME_TO_DIE=400
readonly TIME_TO_EAT=100
readonly TIME_TO_SLEEP=100
readonly NBR_MEALS=10

#no_die_test_auto
readonly DEFAULT_TIMEOUT=10

#die_test_auto
readonly MAX_RETRIES=10 #may consider increasing this value to 20 in case the code is not stable enough

#run_helgrind_tests
readonly FLAG=helgrind
readonly MIN_PHILOS_H=2
readonly MAX_PHILOS_H=10
readonly TIME_TO_DIE_H=800
readonly TIME_TO_EAT_H=200
readonly TIME_TO_SLEEP_H=200
readonly NBR_MEALS_H=3
