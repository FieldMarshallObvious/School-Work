#!//bin/bash

FILES=$(ls *.dis)
num=0

for FILE in $FILES
do
  echo "Disassembling ${FILE%.*}.mips into ${FILE%.*}.out"
  ./disassembler test$num.mips > test$num.out
  diff -w -s test$num.dis test$num.out
  let num+=1
done
