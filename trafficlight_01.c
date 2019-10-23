/*
 * Traffic light control
 * Linux: gcc -o trafficlight trafficlight_01.c && ./trafficlight
 * Windows: gcc -o trafficlight trafficlight_01.c; ./trafficlight
 */ 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#define NUM_ITER 2 // number of iterations

typedef struct ST_Trafficlight {
    int red; /* traffic-light */
    int yellow; /* traffic-light */
    int green;  /* traffic-light */
    char state[30]; /* description of state */
    int trigger; /* in ms */
} Trafficlight;


int trafficlight_timer(Trafficlight *tlight) {
    /* stay in state within a certain time defined by timer */
    int msec = 0; 
    int iterations = 0; 
    clock_t before = clock(); // start clock

    printf("\nTraffic-Light State: %s\n",tlight->state);
    printf("Red: %d\n",tlight->red);
    printf("Yellow: %d\n",tlight->yellow);
    printf("Green: %d\n",tlight->green);
    // do timeer 
    do {
        clock_t difference = clock() - before;
        msec = difference * 1000 / CLOCKS_PER_SEC;
        iterations++;
        } while ( msec < tlight->trigger );

    printf("Time taken %d seconds %d milliseconds (%d iterations)\n\n",
    msec/1000, msec%1000, iterations);

    return 0;
}



int main(){
    Trafficlight tlight; // create instance of struct
    int iter;
    for(iter=0; iter < NUM_ITER; iter++){
        
        // do red phase
        tlight.red = 1;
        tlight.yellow = 0; 
        tlight.green = 0;  
        strcpy(tlight.state,"Traffic-Light Red"); 
        tlight.trigger = 1000; // time in ms
        trafficlight_timer(&tlight); // call timer

        // do yellow phase
        tlight.red = 0;
        tlight.yellow = 1; 
        tlight.green = 0;  
        strcpy(tlight.state,"Traffic-Light Yellow"); 
        tlight.trigger = 3000; // time in ms
        trafficlight_timer(&tlight); // call timer

        // do green phase
        tlight.red = 0;
        tlight.yellow = 0; 
        tlight.green = 1;  
        strcpy(tlight.state,"Traffic-Light Green"); 
        tlight.trigger = 2000; // time in ms
        trafficlight_timer(&tlight); // call timer

        printf("==================================\n");
        printf(" Iteration finished (%d|%d) ",iter+1,NUM_ITER);
        printf("\n==================================\n\n");
    }
}