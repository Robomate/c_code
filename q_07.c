#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<assert.h>
/*
 * RL Algos: Q_Learning
 * 2D Gridworld Example
 * Epsilon-Greedy Action
 * Exec: gcc -o test q_07.c && ./test
 */ 

// init globals
#define ITERATIONS 1000 // max number of iterations
#define ROWS 5 // number of rows
#define COLS 5 // number of columns
#define STRING_LEN 10 // string length for printing
#define MAX_ACTIONS 4 // max number of next actions
#define DIM_STATES 2 // number of state dimensions

const double trans[3] = {0.1,0.8,0.1}; // transistion probs for fixed policy
const char *actions[] = {"up   ", "right", "down ", "left "}; // actions
static double gamma = 0.9; // discount factor
static double alpha = 0.9; // learning factor
static double epsilon = 0.9; // epsilon-greedy factor
const double eps_decay = 0.99; // eps decay factor (high for big envs)
const double eps_minimum = 0.1; // epsilon-greedy minimum

double R[ROWS][COLS]; // reward table
double Q[ROWS][COLS]; // q table
char P[ROWS][COLS][STRING_LEN]; // policy table

// init struct for a state
typedef struct ST_State{
    int r; // row
    int c; // col
} State;

// init struct for array of actions
typedef struct ST_ActionStates{
    int v1[MAX_ACTIONS]; // case: corner up-left  
    int v2[MAX_ACTIONS]; // case: corner up-right
    int v3[MAX_ACTIONS]; // case: corner down-right
    int v4[MAX_ACTIONS]; // case: corner down-left
    int v5[MAX_ACTIONS]; // case: rim up
    int v6[MAX_ACTIONS]; // case: rim right
    int v7[MAX_ACTIONS]; // case: rim down
    int v8[MAX_ACTIONS]; // case: rim left
    int v9[MAX_ACTIONS]; // standard case, action order: (North, East, South, West)
}StateAction;

// init tuple for maximum
typedef struct ST_MaxTuple{
 double max_val; 
 int max_idx;   
} MaxTuple;

// init functions
double rand_double() {
    /* uniform random number */
   return rand()/(double)RAND_MAX;
}

int rand_int(int max_rand){
    /* random number between 0 and max_rand-1 */
    return rand() % max_rand;
}

int fill_mat_const(double array[][COLS], double val){
    /* fills a matrix with a constant value */
    int i,j;
    for(i=0; i < ROWS; i++){
        for(j=0; j<COLS; ++j){
            array[i][j] = val;
        }   
    }
    return 0;
}

int fill_mat_string(char array[][COLS][STRING_LEN], int val){
    /* fills a matrix with a constant string */
    int i,j;
    for(i=0; i < ROWS; i++){
        for(j=0; j<COLS; ++j){
            strcpy(array[i][j], actions[val]); 
        }   
    }
    return 0;
}

int fill_Qvec(double vec[], State states[MAX_ACTIONS]){
    /* fill vector with Q-Values */
    for (int i = 0; i < MAX_ACTIONS; i++){
        vec[i] = Q[states[i].r][states[i].c];   
    }
    return 0;
}

void print_mat_double(double array[][COLS]){
    /* prints out a double matrix */
    int i,j;
    for(i=0; i < ROWS; i++){
        for(j=0; j<COLS; ++j){
            printf("  %3.2lf", array[i][j]);
        }
        printf("\n");   
    }
    printf("\n");
}

void print_mat_string(char array[][COLS][STRING_LEN]){
    /* prints out a string matrix */
    int i,j;
    for(i=0; i < ROWS; i++){
        for(j=0; j<COLS; ++j){
            printf(" %s", array[i][j]);
        }
        printf("\n");   
    }
    printf("\n");
}

void print_vec(double vec[]){
    /* prints out a double vector */
    printf("\nQVector: ( ");
    for (int i = 0; i < MAX_ACTIONS; ++i){ 
        printf("%3.2lf ", vec[i]);
    }
    printf(")");
}

int next_actions(State current_state, State next_states[MAX_ACTIONS], StateAction state_actions[DIM_STATES]){
    /* return next possible actions by array of structs */
    int i;
    printf("\nCurrent State: ");
    printf("(%d,%d)\n",current_state.r,current_state.c);
    printf("\nPossible Next States:\n");
    // loop over all actions by order: (North, East, South, West)
    for (i = 0; i < MAX_ACTIONS; i++){    
        // check 9 cases: 4 corner, 4 rim cases, 1 standard case
        if(current_state.r == 0 && current_state.c == 0){
            // case: corner up-left
            next_states[i].r = state_actions[0].v1[i]; // assign value to row
            next_states[i].c = state_actions[1].v1[i]; // assign value to col         
        }
        else if(current_state.r == 0 && current_state.c == COLS-1){  
            // case: corner up-right
            next_states[i].r = state_actions[0].v2[i]; // assign value to row
            next_states[i].c = COLS -1 + state_actions[1].v2[i]; // assign value to col
        }
        else if(current_state.r == ROWS-1 && current_state.c == COLS-1){
            // case: corner down-right
            next_states[i].r = ROWS -1 + state_actions[0].v3[i]; // assign value to row
            next_states[i].c = COLS -1 + state_actions[1].v3[i]; // assign value to col       
        }
        else if(current_state.r == ROWS-1 && current_state.c == 0){        
            // case: corner down-left
            next_states[i].r = ROWS -1 + state_actions[0].v4[i]; // assign value to row
            next_states[i].c = state_actions[1].v4[i]; // assign value to col    
        }
        else if(current_state.r == 0 && current_state.c != 0 && current_state.c != COLS-1){
            // case: rim up
            next_states[i].r = state_actions[0].v5[i]; // assign value to row
            next_states[i].c = current_state.c + state_actions[1].v5[i]; // assign value to col 
        }
        else if(current_state.c == COLS-1 && current_state.r != 0 && current_state.r != ROWS-1){
            //  case: rim right
            next_states[i].r = current_state.r + state_actions[0].v6[i]; // assign value to row
            next_states[i].c = COLS -1 + state_actions[1].v6[i]; // assign value to col       
        }
        else if(current_state.r == ROWS-1 && current_state.c != 0 && current_state.c != COLS-1){
            //  case: rim down
            next_states[i].r = ROWS -1 + state_actions[0].v7[i]; // assign value to row
            next_states[i].c = current_state.c + state_actions[1].v7[i]; // assign value to col     
        }
        else if(current_state.c == 0 && current_state.r != 0 && current_state.r != ROWS-1){
            //  case: rim left
            next_states[i].r = current_state.r + state_actions[0].v8[i]; // assign value to row
            next_states[i].c = state_actions[1].v8[i]; // assign value to col        
        }
         else if(current_state.r != 0 && current_state.r != ROWS-1 && current_state.c != 0 && current_state.c != COLS-1 ){
            // standard case
            next_states[i].r = current_state.r + state_actions[0].v9[i]; // assign value to row
            next_states[i].c = current_state.c + state_actions[1].v9[i]; // assign value to col     
        }
        else{
            printf("\nError, no next states found!!\n");   
        }
        printf("%s: ",actions[i]);
        printf("(%d,%d)\n",next_states[i].r,next_states[i].c);
    }
    return 0;
}

MaxTuple find_max_vec(double array[]){
    /* find maximum value and index in matrix */
    MaxTuple max; // struct instance
    max.max_val = array[0];
    max.max_idx = 0;

    for(int r = 0; r < MAX_ACTIONS; r++){
        if (array[r] > max.max_val){
            max.max_val = array[r];
            max.max_idx = r;
        }
    }
    printf("\nMax: %3.2lf, Idx: %d\n",max.max_val,max.max_idx);
    return max; // return struct directly
}

// init main
int main(int argc, char** argv){

    system("clear"); // clear screen
    // init locals
    StateAction state_actions[DIM_STATES] = {
        {        
        .v1 = { 0, 0, 1, 0 },
        .v2 = { 0, 0, 1, 0 },
        .v3 = { -1, 0, 0, 0 },
        .v4 = { -1, 0, 0, 0 },
        .v5 = { 0, 0, 1, 0 },
        .v6 = { -1, 0, 1, 0 },
        .v7 = { -1, 0, 0, 0 },
        .v8 = { -1, 0, 1, 0 },
        .v9 = { -1, 0, 1, 0 },  
        },
        { 
        .v1 = { 0, 1, 0, 0 },
        .v2 = { 0, 0, 0, -1 },
        .v3 = { 0, 0, 0, -1 },
        .v4 = { 0, 1, 0, 0 },
        .v5 = { 0, 1, 0, -1 },
        .v6 = { 0, 0, 0, -1 },
        .v7 = { 0, 1, 0, -1 },
        .v8 = { 0, 1, 0, 0 },
        .v9 = { 0, 1, 0, -1 },    
        }, 
    }; // init special cases, first rows then cols
  
    State current_state = {.r = 0, .c = 0}; // init start position at e.g. [0,0]
    if(current_state.r >= ROWS || current_state.c >= COLS){
        printf("\nError, Start State is not within Q-table.\n");   
    };
    State next_states[MAX_ACTIONS]; // init next possible states
    State next_state; // init next state (for action)
    MaxTuple max; // init for Q maximum
    MaxTuple eps_max; // init for epsilon maximum

    double Q_current; // current q value for current state
    double Q_new; // new q value for current state
    double Q_max; // max q value from next state
    double R_current; // current reward for current state
    double Q_max_array[MAX_ACTIONS]; // vector for Q-values to find max
    double eps_array[DIM_STATES] = {eps_minimum, 1.0}; // vector for epsilon to find max
    double init_q = 0.0; // initial q value
    double init_reward = 1.0; // initial reward
    int init_action = 0; // init action: up
    int action; // action for next state
    int iter; // current number of iterations
    double rand_uni; // uniform random number
    time_t t; // for pseudo random number
    srand((unsigned) time(&t)); // init random number generator
    ///////////////////
    // init tables
    ///////////////////
    printf("\n==== Init tables ====\n");
    fill_mat_const(Q, init_q); // init Q-table with zeros
    printf("\nQ-table\n");
    print_mat_double(Q);
    // init R-table 
    fill_mat_const(R, init_reward);
    R[1][4] = 100.0;
    R[2][4] = 50.0;
    R[1][3] = 25.0;
    printf("Reward-table\n");
    print_mat_double(R);
    // init Policy Table with north actions
    fill_mat_string(P, init_action);
    //strcpy(P[1][3], actions[init_action]); // Update Policy Table 
    printf("Action-table\n");
    print_mat_string(P);

    // check possible next states for start state: Q[0][0] 
    printf("=== Check for Start State ===\n");
    next_actions(current_state, next_states, state_actions);
    
    // start iterations
    for(iter = 1; iter < ITERATIONS+1; iter++){
        printf("\n\n==================================\n");
        printf("    Start with Iteration (%d|%d) ",iter,ITERATIONS);
        printf("\n==================================\n");
        printf("\nCurrent State in Q: ");
        printf("(%d,%d)\n",current_state.r,current_state.c);        
        // epsilon-greedy strategy with expontial decay
        printf("\n=== Select Action ===\n");


        eps_array[1] = epsilon * eps_decay;
        eps_max = find_max_vec(eps_array); // find max of epsilon
        epsilon = eps_max.max_val;
        rand_uni = rand_double();
        printf("\nEpsilon: %3.2lf\n",epsilon);
        // printf("RandUni: %3.2lf\n",rand_uni);
        if(epsilon > rand_uni){ 
            // case: random action 
            action = rand_int(MAX_ACTIONS); // rand(number from 0 to 3)
            printf("\nRandom Action: %s, (%d)\n", actions[action], action);   
        }
        else{ 
            // case: greedy action 
            fill_Qvec(Q_max_array, next_states); // find Q-Values
            print_vec(Q_max_array);
            max = find_max_vec(Q_max_array); // find max of Q-Values
            action = max.max_idx; 
            printf("\nGreedy Action: %s, (%d)\n", actions[action], action);    
        }
        // set the next state
        next_state.r = next_states[action].r;
        next_state.c = next_states[action].c;

        // opt: show action in action table
        strcpy(P[current_state.r][current_state.c], actions[action]);
        printf("\nAction-table\n");
        print_mat_string(P);

        // find Q_max of next states 
        printf("\n=== Find Qmax ===\n");
        next_actions(next_state, next_states, state_actions);
        fill_Qvec(Q_max_array, next_states); // find Q-Values
        print_vec(Q_max_array);
        max = find_max_vec(Q_max_array); // find max of Q-Values
        
        // assign values
        Q_max = max.max_val; 
        Q_current = Q[current_state.r][current_state.c]; 
        R_current = R[current_state.r][current_state.c];

        // do Bellman Update
        Q_new = Q_current + alpha * (R_current + gamma * Q_max - Q_current);
        Q[current_state.r][current_state.c] = Q_new; // Update Q-table

        // set next state to current state
        current_state = next_state;

        printf("\n=== Iteration (%d|%d) ===\n",iter,ITERATIONS);
        printf("\nQ-table\n");
        print_mat_double(Q);
    }
    // Print out final results:
    printf("\n\n=====================\n");
    printf("=== Final Results ===");
    printf("\n=====================\n");
    printf("\nTotal Iterations: %d\n",ITERATIONS);
    printf("\nAction-table\n");
    print_mat_string(P);
    printf("Q-table\n");
    print_mat_double(Q);


    // convert double to string




    return 0;
}