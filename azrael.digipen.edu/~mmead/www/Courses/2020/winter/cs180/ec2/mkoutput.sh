#!/bin/bash

OUTDIR=output

./prp --help > $OUTDIR/output-help.txt

./prp -n3 -pfifo -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-fifo-3-1.txt
./prp -n4 -pfifo -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-fifo-4-1.txt
./prp -n5 -pfifo -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-fifo-5-1.txt

./prp -n3 -pclock -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-clock-3-1.txt
./prp -n4 -pclock -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-clock-4-1.txt
./prp -n5 -pclock -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-clock-5-1.txt

./prp -u -n3 -pclock -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-clock-3-1u.txt


./prp -n3 -plru -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-lru-3-1.txt
./prp -n4 -plru -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-lru-4-1.txt
./prp -n5 -plru -r7,0,1,2,0,3,0,2,0,4,0,2 > $OUTDIR/output-lru-5-1.txt

./prp -n3 -pfifo -r3,2,1,0,3,2,4,3,2,1,0,4 > $OUTDIR/output-fifo-3-2.txt
./prp -n4 -pfifo -r3,2,1,0,3,2,4,3,2,1,0,4 > $OUTDIR/output-fifo-4-2.txt

./prp -n3 -plru -r3,2,1,0,3,2,4,3,2,1,0,4 > $OUTDIR/output-lru-3-2.txt
./prp -n4 -plru -r3,2,1,0,3,2,4,3,2,1,0,4 > $OUTDIR/output-lru-4-2.txt
./prp -n4 -plru -r3,2,1,0,3,2,4,3,2,1,0,4 > $OUTDIR/output-lru-5-2.txt

./prp -n3 -pfifo -r@pages.txt > $OUTDIR/output-fifo-3-3.txt
./prp -n4 -pfifo -r@pages.txt > $OUTDIR/output-fifo-4-3.txt
./prp -n5 -pfifo -r@pages.txt > $OUTDIR/output-fifo-5-3.txt
./prp -n6 -pfifo -r@pages.txt > $OUTDIR/output-fifo-6-3.txt
./prp -n7 -pfifo -r@pages.txt > $OUTDIR/output-fifo-7-3.txt
./prp -n8 -pfifo -r@pages.txt > $OUTDIR/output-fifo-8-3.txt

./prp -n3 -pclock -r@pages.txt > $OUTDIR/output-clock-3-3.txt
./prp -n4 -pclock -r@pages.txt > $OUTDIR/output-clock-4-3.txt
./prp -n5 -pclock -r@pages.txt > $OUTDIR/output-clock-5-3.txt
./prp -n6 -pclock -r@pages.txt > $OUTDIR/output-clock-6-3.txt
./prp -n7 -pclock -r@pages.txt > $OUTDIR/output-clock-7-3.txt
./prp -n8 -pclock -r@pages.txt > $OUTDIR/output-clock-8-3.txt

./prp -n3 -plru -r@pages.txt > $OUTDIR/output-lru-3-3.txt
./prp -n4 -plru -r@pages.txt > $OUTDIR/output-lru-4-3.txt
./prp -n5 -plru -r@pages.txt > $OUTDIR/output-lru-5-3.txt
./prp -n6 -plru -r@pages.txt > $OUTDIR/output-lru-6-3.txt
./prp -n7 -plru -r@pages.txt > $OUTDIR/output-lru-7-3.txt
./prp -n8 -plru -r@pages.txt > $OUTDIR/output-lru-8-3.txt

rm $OUTDIR/output-fifo-stress-1.txt 
for value in {1..9} 
do
	./prp -n$value -pfifo -r@pages.txt -s >> $OUTDIR/output-fifo-stress-1.txt
done

rm $OUTDIR/output-clock-stress-1.txt 
for value in {1..9} 
do
	./prp -n$value -pclock -r@pages.txt -s >> $OUTDIR/output-clock-stress-1.txt
done

rm $OUTDIR/output-lru-stress-1.txt 
for value in {1..9} 
do
	./prp -n$value -plru -r@pages.txt -s >> $OUTDIR/output-lru-stress-1.txt
done

rm $OUTDIR/output-fifo-stress-2.txt 
for value in {1..9} 
do
	./prp -n$value -pfifo -r@pages.txt >> $OUTDIR/output-fifo-stress-2.txt
done

rm $OUTDIR/output-clock-stress-2.txt 
for value in {1..9} 
do
	./prp -n$value -pclock -r@pages.txt >> $OUTDIR/output-clock-stress-2.txt
done

rm $OUTDIR/output-lru-stress-2.txt 
for value in {1..9} 
do
	./prp -n$value -plru -r@pages.txt >> $OUTDIR/output-lru-stress-2.txt
done

rm $OUTDIR/output-clock-stress-2u.txt 
for value in {1..9} 
do
	./prp -u -n$value -pclock -r@pages.txt >> $OUTDIR/output-clock-stress-2u.txt
done

rm $OUTDIR/output-all-stress.txt 
for value in 2 3 5 8 9
do
	./prp --numframes=$value --policy=fifo --requests=@pages2.txt >> $OUTDIR/output-all-stress.txt
	./prp --numframes=$value --policy=clock --requests=@pages2.txt >> $OUTDIR/output-all-stress.txt
	./prp --numframes=$value --policy=lru --requests=@pages2.txt >> $OUTDIR/output-all-stress.txt
done











