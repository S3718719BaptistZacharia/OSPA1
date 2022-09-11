# grep -o "\w*\w*" wlist_match1.txt  // list only words 

# grep -o -w '\w\{3,15\}' $1 | sort -u | shuf > $2 #// list only words between 3 and 15

# grep -i -o -w '[a-z]\w[a-z]\w\{2,16\}' $1 | sort -u | shuf > $2 #// list only words between 3 and 15

# awk '{if (length($0) > 2 && length($0) < 16  && $0 ~ /[a-z]/) print}' $1 | sort -u > $2

grep -i -o -E '^[[:lower:]]{3,15}' $1 | sort -u | shuf > $2