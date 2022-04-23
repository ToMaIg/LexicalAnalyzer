Operative System Version:
  Distributor ID: Kali
  Description:    Kali GNU/Linux Rolling
  Release:        2021.2

Compiler Version:
  gcc (Debian 10.2.1-6) 10.2.1 20210110

How to compile and run:
  1- gcc *.c -Wall
  2- ./a.out

How to check memory leaks:
  1- gcc *.c -Wall -g
  2- valgrind ./a.out

NOTE: you can install valgrind with the following commands: 
  1- sudo apt-get update
  2- sudo apt-get install valgrind
