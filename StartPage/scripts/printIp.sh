#!/bin/bash
IP=$(/sbin/ip route get 8.8.8.8 2>/dev/null | awk 'NR==1 {print $NF}')
echo $IP
