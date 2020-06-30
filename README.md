# Medical-Call-centerName: Prachi Modi
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

int next_id
static sem_t connected_lock - Binary semaphore
static sem_t operators      - Connected semaphore
static int NUM_OPERATORS    - variable for no. of operators
static int NUM_LINES        - variable for no. of lines
static int connected        - Callers that are connected

Functions:
phonecall -function executed on creation of thread that checks if the line is busy or not
available- function executed when the caller line is not busy
lineBusy - recursive function executed when the caller line is busy
