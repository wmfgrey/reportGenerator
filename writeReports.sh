#! /bin/bash -f

# gcc commentsBank.c -o commentsBank -Wall -lm

if [ 1 ] ; then 

 [ -f files/reports.txt ] && rm -f files/reports.txt
 [ -f files/classListOut.txt ] && rm -f files/classListOut.txt

 ./commentsBank files/classList.txt files/classListOut.txt 12 < files/intest.txt
 #./commentsBank -reports files/classListOut.txt files/bank.txt files/reports.txt 12
 #gedit files/reports.txt

fi

if [ ] ; then 

 [ -f files/reports.txt ] && rm -f files/reports.txt
 [ -f files/classListOut.txt ] && rm -f files/classListOut.txt

 ./commentsBank -grades files/classList.txt files/classListOut.txt 12 < files/intest.txt
 ./commentsBank -reports files/classListOut.txt files/bank.txt files/reports.txt 12
 gedit files/reports.txt

fi


if [ ] ; then 

 [ -f files/reports.txt ] && rm -f files/reports.txt
 [ -f files/classListOut.txt ] && rm -f files/classListOut.txt

 ./commentsBank -grades files/classList.txt files/classListOut.txt 7 < files/intest.txt
 ./commentsBank -reports files/classListOut.txt files/bank.txt files/reports.txt 7
 gedit files/reports.txt

fi


