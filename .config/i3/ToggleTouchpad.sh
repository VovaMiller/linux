#!/bin/bash
device=$(xinput list | sed -n 's/.*FocalTech Touchpad.*id=\(.*\)\t.*/\1/ip;T;q')
state=$(xinput list-props "$device" | grep "Device Enabled" | grep -o "[01]$")
if [ $state == '1' ];then
  xinput --disable "$device"
else
  xinput --enable "$device"
fi
