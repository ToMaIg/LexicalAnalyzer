Sistema Operativo:
Distributor ID: Kali
Description:    Kali GNU/Linux Rolling
Release:        2021.2

Compilador:
gcc (Debian 10.2.1-6) 10.2.1 20210110

Procedimiento para compilar y ejecutar:
1- gcc *.c -Wall
2- ./a.out

Procedimiento para revisar si existen leaks de memoria:
1- gcc *.c -Wall -g
2- valgrind ./a.out

NOTA: para instalar valgrind: 
1- sudo apt-get update
2- sudo apt-get install valgrind
