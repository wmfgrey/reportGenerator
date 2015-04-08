#! /bin/bash -f

# gcc reportGenerator.c -o reportGenerator -Wall -lm

if [ ] ; then 
 
 [ -f dataFiles/reports.txt ] && rm -f dataFiles/reports.txt
 [ -f dataFiles/classListOut.txt ] && rm -f dataFiles/classListOut.txt
 
 reportGenerator -grades dataFiles/classList.txt dataFiles/bank.xml dataFiles/classListOut.txt
 reportGenerator -reports dataFiles/classListOut.txt dataFiles/bank.xml dataFiles/reports.txt
 
fi

if [ 1 ] ; then 
 
 [ -f dataFiles/reports.txt ] && rm -f dataFiles/reports.txt
 [ -f dataFiles/classListOut.txt ] && rm -f dataFiles/classListOut.txt
 
 reportGenerator -grades dataFiles/classList.txt dataFiles/bank.xml dataFiles/classListOut.txt < dataFiles/intest.txt
 reportGenerator -reports dataFiles/classListOut.txt dataFiles/bank.xml dataFiles/reports.txt
 
fi

