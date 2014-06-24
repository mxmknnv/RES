gcc -c -fPIC BigInt.c -o BigInt.o
gcc -shared  BigInt.o -o libBigInt.so
g++ -c -fPIC LongNumber.cpp -o LongNumber.o
g++ -c rsa.cpp -o rsa.o
g++ -c elgamal.cpp -o elgamal.o
g++ -c schnorr.cpp -o schnorr.o
g++ LongNumber.o -shared -L. -lBigInt -o libLongNumber.so 
g++ rsa.o -L. -lLongNumber -Wl,-rpath,. -o rsa -g
g++ elgamal.o -L. -lLongNumber -Wl,-rpath,. -o elgamal -g
g++ schnorr.o -L. -lLongNumber -Wl,-rpath,. -o schnorr -g
