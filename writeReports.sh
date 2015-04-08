#! /bin/bash -f

 gcc reportGenerator.c -o reportGenerator -Wall -lm

if [ 0 ] ; then 

 [ -f files/reports.txt ] && rm -f files/reports.txt
 [ -f files/classListOut.txt ] && rm -f files/classListOut.txt

 ./reportGenerator -grades files/classList.txt files/classListOut.txt 12 < files/intest.txt
  gedit files/classListOut.txt
 #./reportGenerator -reports files/classListOut.txt files/bank.txt files/reports.txt 12
 #gedit files/reports.txt

fi

if [ 1 ] ; then 

 [ -f files/reports.txt ] && rm -f files/reports.txt
 [ -f files/classListOut.txt ] && rm -f files/classListOut.txt

 ./reportGenerator -grades files/classList.txt files/classListOut.txt 12 < files/intest.txt
 ./reportGenerator -reports files/classListOut.txt files/bank.txt files/reports.txt 12
 gedit files/reports.txt

fi


if [ ] ; then 

 [ -f files/reports.txt ] && rm -f files/reports.txt
 [ -f files/classListOut.txt ] && rm -f files/classListOut.txt

 ./reportGenerator -grades files/classList.txt files/classListOut.txt 7 < files/intest.txt
 ./reportGenerator -reports files/classListOut.txt files/bank.txt files/reports.txt 7
 gedit files/reports.txt

fi


