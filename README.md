# Medical-Call-center 
Name: Prachi Modi
Email: pbmodi@umass.edu
ID: 31816621

Class: COMPSCI 230-01
Professor: Joe Chiu
                       Project 4 - Threads and Synchronization: Cure for an unknown virus

URL For Video: https://youtu.be/QXtv2kekuiw



Files:

virus_cure.c -The program is medical call center simulation. There are 8 lines, and 5 operators. The code is supposed to
              manage any amount of calls between 8 lines, and accordingly connect them to the 5 operators.

Global Variables:

1)int next_id

2)static sem_t connected_lock - Binary semaphore

3)static sem_t operators      - Connected semaphore

4)static int NUM_OPERATORS    - variable for no. of operators

5)static int NUM_LINES        - variable for no. of lines

6)static int connected        - Callers that are connected

Functions:

1)phonecall -function executed on creation of thread that checks if the line is busy or not

2)available- function executed when the caller line is not busy

3)lineBusy - recursive function executed when the caller line is busy
