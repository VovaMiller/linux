#!/bin/bash
active_port=$(pactl list sinks | grep -oP "Active Port: \K\S+")
volume=$(pactl list sinks | grep '^[[:space:]]Volume:' | \
        head -n $(( $SINK + 1 )) | tail -n 1 | sed -e 's,.* \([0-9][0-9]*\)%.*,\1,')
mute=$(pactl list sinks | grep '^[[:space:]]Mute:' | \
        head -n $(( $SINK + 1 )) | tail -n 1 | sed -n 's/Mute:// p' | sed -n 's/\s//g p')

#echo $active_port
# analog-output-headphones
# analog-output-speaker

if [ "$active_port" = "analog-output-headphones" ]; then
    printf 
else
    printf 
fi

if [ "$mute" = "yes" ]; then
    printf " MUTE\\n"
else
    printf " $volume%%\\n"
fi

