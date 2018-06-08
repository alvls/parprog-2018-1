#!/bin/bash
rm -rf Tests
mkdir Tests
./Test/gen 10 ./Tests/10
echo "10 done"
./Test/gen 50 ./Tests/50
echo "50 done"
./Test/gen 100 ./Tests/100
echo "100 done"
./Test/gen 200 ./Tests/200
echo "200 done"
./Test/gen 500 ./Tests/500
echo "500 done"
./Test/gen 1000 ./Tests/1000
echo "1000 done"
./Test/gen 2000 ./Tests/2000
echo "2000 done"
./Test/gen 5000 ./Tests/5000
echo "5000 done"
./Test/gen 10000 ./Tests/10000
echo "10000 done"
./Test/gen 20000 ./Tests/20000
echo "20000 done"
