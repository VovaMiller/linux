#if [ 'a' = 'b' ]; then echo 'Equal'; else echo 'Not equal'; fi

status_wifi=$(nmcli d | grep wifi | awk '{print $3}')
status_ethernet=$(nmcli d | grep ethernet | awk '{print $3}')
if [ "$status_wifi" = "connected" ]; then
    printf 
    #echo WIFI OK
fi
if [ "$status_ethernet" = "connected" ]; then
    printf 
    #echo ETHERNET OK
fi
printf \\n
#echo $status_wifi
#echo $status_ethernet

