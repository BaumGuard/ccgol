#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/ioctl.h>
#include<time.h>
#include<string.h>
#include<stdbool.h>

#include "import_field.h"
#include "console_size.h"
#include "show_help.h"

#define DEAD_CHAR  "░"
#define ALIVE_CHAR "█"

// Default values
int HEIGHT      = 0;
int WIDTH       = 0;
int INTERVAL    = 70;
int RUNS        = 2;
bool AUTOSTOP   = false;
int X           = 0;
int Y           = 0;
bool FROM_FILE  = false;
bool INIT       = false;
bool HELP       = false;
bool INF        = false;



int main (int argc, char** argv) {

    char* FPATH;

    // Parsing the command line parameters/arguments
    for (int i=1; i<argc; i++) {
        if      (strcmp(argv[i], "-h")   ==0)  HEIGHT   = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-w")   ==0)  WIDTH    = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-i")   ==0)  INTERVAL = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-r")   ==0) {RUNS     = atoi(argv[i+1]); AUTOSTOP = true;}
        else if (strcmp(argv[i], "-f")   ==0) {FPATH    = argv[i+1];       FROM_FILE=true;}
        else if (strcmp(argv[i], "-x")   ==0)  X        = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-y")   ==0)  Y        = atoi(argv[i+1]);
        else if (strcmp(argv[i], "-inf") ==0)  INF      = true;
        else if (strcmp(argv[i], "-init")==0)  INIT     = true;
        else if (strcmp(argv[i], "-help")==0 || strcmp(argv[i], "--help")==0) HELP=true;
    }



    // Show help dialog if requested
    if (HELP==true)
        show_help();

    else {

    // Field arrays
    short** arr; // Primary array
    short** tmp_arr; // Secondary array for copying
    short** cmp_arr;


    // Initializing the random function
    srand(time(0));


    // Using a random field
    if (FROM_FILE==false) {

        // Struct for the console size
        struct winsize w;

        // Setting the height/width to the console height/width if the user has not entered them
        if (HEIGHT==0) HEIGHT = getConsoleHeight()-2;
        if (WIDTH==0) WIDTH = getConsoleWidth();


        //Allocating memory for the primary and secondary field array
        arr = malloc(sizeof(short*)*HEIGHT);
        tmp_arr = malloc(sizeof(short*)*HEIGHT);
        cmp_arr = malloc(sizeof(short*)*HEIGHT);

        for (int i=0; i<WIDTH; i++) {
            arr[i] = malloc(sizeof(short)*WIDTH);
            tmp_arr[i] = malloc(sizeof(short)*WIDTH);
            cmp_arr[i] = malloc(sizeof(short)*WIDTH);
        }

        // Generating a random field and setting values in tmp_arr to 0
        for (int a = 0; a < HEIGHT; a++) {
            for (int b=0; b < WIDTH; b++) {
                arr[a][b] = rand() % 2;
                tmp_arr[a][b] = 0;
                cmp_arr[a][b] = 0;
            }
        }
    }

    // Using a field file
    else {
        // Importing the field from the file
        short** file_field = import_field(FPATH);

        // Setting height/width to height/width of file field if the user hasn't entered them'
        if (HEIGHT==0) HEIGHT = sz.height;
        if (WIDTH==0)  WIDTH  = sz.width;

        // Allocating memory for the primary and secondary array
        arr = malloc(sizeof(short*)*HEIGHT);
        tmp_arr = malloc(sizeof(short*)*HEIGHT);
        cmp_arr = malloc(sizeof(short*)*HEIGHT);

        for (int i=0; i<WIDTH; i++) {
            arr[i] = malloc(sizeof(short)*WIDTH);
            tmp_arr[i] = malloc(sizeof(short)*WIDTH);
            cmp_arr[i] = malloc(sizeof(short)*WIDTH);
        }

        // Copying field array to primary array and setting the values of tmp_arr to 0
        for (int a = 0; a < sz.height; a++) {
            for (int b=0; b < sz.width; b++) {
                arr[a+Y][b+X] = file_field[a][b];
                tmp_arr[a+Y][b+X] = 0;
                cmp_arr[a+Y][b+X] = 0;
            }
        }
    }


    // Only show initial state of the field
    if (INIT==true) {
        for (int a=0; a < HEIGHT; a++) {
            for (int b=0; b<WIDTH; b++) {
                if  (arr[a][b] == 0) printf("%s", DEAD_CHAR);
                else printf("%s", ALIVE_CHAR);
            }
            printf("\n");
        }
    }

    else {

        // Array for storing the value neighbor cells
        short n[8];

        size_t run = 1;

        // Iterator
        int it = 0;

        for (; it < RUNS; it++) {

            // Clear console to draw new field
            system("clear");

            // Show number of run
            printf("Run: %llu\n", run);
            run++;

            // Iterate over field
            for (int i=1; i < HEIGHT-1; i++) {
                for (int j=1; j < WIDTH-1; j++) {

                    // Ignore margin cells
                    if (i==0 || j==0 || i==HEIGHT-1 || j==WIDTH-1) continue;
                    else {

                    // Storing the values of the neighbor cells
                    n[0] = arr[i-1][j-1];
                    n[1] = arr[i-1][j];
                    n[2] = arr[i-1][j+1];
                    n[3] = arr[i][j-1];
                    n[4] = arr[i][j+1];
                    n[5] = arr[i+1][j-1];
                    n[6] = arr[i+1][j];
                    n[7] = arr[i+1][j+1];

                    // Counter for number of alive neighbor cells
                    short q_n = 0;

                    // Determine number of alive neighbor cells
                    for (int k=0; k<8; k++)
                        if (n[k] == 1) q_n++;

                    // Applying rules of the Game of Life (saving in tmp_arr)
                    if (arr[i][j] == 0) {
                        if (q_n == 3) tmp_arr[i][j] = 1;
                        else tmp_arr[i][j] = 0;
                    }
                    else if (arr[i][j] == 1) {
                        if (q_n < 2) tmp_arr[i][j] = 0;
                        else if (q_n == 2 || q_n == 3) tmp_arr[i][j] = 1;
                        else tmp_arr[i][j] = 0;
                    }
                }

            }
            }

            // Copying secondary array to primary array
            for (int a=0; a < HEIGHT; a++)
                for (int b=0; b < WIDTH; b++)
                    arr[a][b] = tmp_arr[a][b];



            // Display cells
            for (int a=0; a < HEIGHT; a++) {
                for (int b=0; b<WIDTH; b++) {
                    if  (arr[a][b] == 0) printf("%s", DEAD_CHAR);
                    else printf("%s", ALIVE_CHAR);
                }
                printf("\n");
            }


            // Checking for final/alternating field configuration
            // If the current field and the field before the last field are equal,
            // the execution will be stopped if not requested differently by the user.
            if (run%2 == 0 && INF == false) {

                bool equal = true;

                // Comparing both fields
                for (int a=0; a<HEIGHT; a++) {
                    for (int b=0; b<WIDTH; b++) {
                        if (cmp_arr[a][b] != arr[a][b]) {
                            equal = false;
                            break;
                        }
                    }
                }

                // Exiting if both fields are equal, otherwise saving the current field in cmp_arr
                if (equal == true)
                    break;
                else {
                    for (int a=0; a<HEIGHT; a++) {
                        for (int b=0; b<WIDTH; b++) {
                            cmp_arr[a][b] = arr[a][b];
                        }
                    }
                }
            }

            // Sleep for defined duration
            usleep(INTERVAL*1000);

            // Setting the iterator to 0 for possibly infinite execution
            if (AUTOSTOP == false) it = 0;

        }

        // Freeing the dynamically allocated arrays
        free(arr);

    }
}
}
