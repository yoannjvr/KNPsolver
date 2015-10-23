#!/bin/bash

varW=100

varN=10

i=1

while ((i<21))
do 
    ./dist/Release/GNU-MacOSX/knpsolver ${varW} ${varN} 
    i=$((${i} + 1))
done

varN=20

i=1

while ((i<21))
do 
    ./dist/Release/GNU-MacOSX/knpsolver ${varW} ${varN} 
    i=$((${i} + 1))
done

varN=50

i=1

while ((i<21))
do 
    ./dist/Release/GNU-MacOSX/knpsolver ${varW} ${varN} 
    i=$((${i} + 1))
done



