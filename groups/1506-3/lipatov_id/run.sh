#!/bin/bash
for file in ./Tests/*; do
  if [[ "$file" != *perfect.ans ]];
  then
    ./OpenMP/b 4 $file seq_$file parr_$file
  fi
done
