#include <stdio.h>
#include <string.h>

/* ---------------------------------------------- */
#define HEIGHT 5
#define WIDTH 10

char enemy[HEIGHT][WIDTH]=                                                    
        { {0,0,0,0,0,0,0,0,0,0},                                              
          {0,1,1,0,0,1,0,0,0,0},                                              
          {0,0,0,1,0,1,0,1,1,0},                                              
          {0,0,0,0,0,0,0,0,1,1},                                              
          {0,0,1,1,0,1,0,0,0,1} };  

void matrixScanning()
{
    char myFriend[HEIGHT][WIDTH];

    int i, j;
    for( i=0; i < HEIGHT; i++ ) 
    {
        for( j=0; j < WIDTH; j++) 
        {
            myFriend[i][j] = enemy[i][j]==1 ? 'X' : '.';
        }
    }

    for( i=0; i<HEIGHT;i++) {
        for( j=0;j<WIDTH;j++) {
            printf("%c", myFriend[i][j]);
        }
        printf("\n");
    }
}
/* ---------------------------------------------- */

/* ---------------------------------------------- */
void printNmeaType(char *nmea, const char *delimiters) {
    char *curPosition;
    curPosition = strtok(nmea, delimiters);

    while(curPosition!=NULL){
        printf(curPosition);
        printf("\n");
        curPosition = strtok(NULL, delimiters);
    }
    printf("\n-----\n");
}

void processNmea(){

    char nmea01[] = "$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18";
    char nmea02[] = "$GPGLL,3723.2475,N,12158.3416,W,161229.487,A*2C";
    char nmea03[] = "$GPGSA,A,3,07,02,26,27,09,04,15,,,,,,1.8,1.0,1.5*33";
    char nmea04[] = "$GPGSA,A,3,07,02,26,27,09,04,15,,,,,,1.8,1.0,1.5*33$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18$GPGGA,161229.487,3723.2475,N,12158.3416,W,1,07,1.0,9.0,M,,,,0000*18";
    char bigSucker[530];
    int i;

    char delimiters[] = "$,";
    printNmeaType(nmea01, delimiters);
    printNmeaType(nmea02, delimiters);
    printNmeaType(nmea03, delimiters);
    
    
    for(i=0; i<1000;i++){
        strcpy(bigSucker, nmea04);
        printNmeaType(bigSucker, delimiters);
    }
}
/* ---------------------------------------------- */

int main(int argc, char *argv[]){
    printf("\n/* ---------------------------------------------- */\n\n");
    matrixScanning();

    printf("\n/* ---------------------------------------------- */\n\n");
    processNmea();
}