#!/bin/bash

for LINE in ls /usr/lib/*; do
	echo $LINE	
	nm $LINE | grep " I "
done
