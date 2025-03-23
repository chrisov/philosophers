#! /bin/bash

for file in ./test_modules/*.sh; do
	[ -f "$file" ] && source "$file"
done
