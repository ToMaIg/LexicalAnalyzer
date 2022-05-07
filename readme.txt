The following OS and Compiler versions are not requirements.
--------------------------------------------------------------
Operative System Version used:
  Distributor ID: Kali
  Description:    Kali GNU/Linux Rolling
  Release:        2021.2

Compiler Version used:
  gcc (Debian 10.2.1-6) 10.2.1 20210110
--------------------------------------------------------------
How to compile and run:
  1- make

How to check memory leaks:
  1- gcc *.c -Wall -g
  2- valgrind ./a.out

NOTE: In case valgrind isn't already installed, you can run the following commands: 
  1- sudo apt-get update
  2- sudo apt-get install valgrind
