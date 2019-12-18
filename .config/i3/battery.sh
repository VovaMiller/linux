battery_p=$(upower -i `upower -e | grep 'BAT'` | sed -n '/percentage/ s/[^0-9]//g p')
battery_s=$(upower -i `upower -e | grep 'BAT'` | sed -n '/state:/ s/state:// p' | sed -n 's/\s//g p')
#echo $battery_p
#echo "\"$battery_s\""

# Coloring
#printf '\033[0;31m'

# Battery label
if [ "$battery_p" -le "10" ]; then
    printf 
elif [ "$battery_p" -le "25" ]; then
    printf 
elif [ "$battery_p" -le "40" ]; then
    printf 
elif [ "$battery_p" -le "90" ]; then
    printf 
else
    printf 
fi

# Percentage
printf " $battery_p"
printf "%% "

# Status label
if [ "$battery_s" = "charging" ]; then
    printf 
else
    printf 
fi

#printf '\033[0m' # color to default
printf \\n

