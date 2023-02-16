#include <iostream>
#include <cstdlib>
#include <math.h>

#define NUM_PROCESSES 1000
#define ARRIVAL_RATE_S 2
#define SERVICE_RATE_S 1

using namespace std;

void generateProcesses(float proccess_data[][3], float* totalTime, int processes);
float generateArrivalTime(float lamda);
float generateServiceTime(float lamda);
void calculateAverages(float* process_data);
void printReceivedProccesses(float process_data[][3], int processes );


int main() {
    // Seed ranom num generator
    srand((unsigned) time(NULL));

    float processLog[NUM_PROCESSES][3];
    float totalTime = 0;
    float averageArrival, averageService;

    generateProcesses(processLog, &totalTime, NUM_PROCESSES);


    // Determine the average arrival time
    averageArrival = NUM_PROCESSES/totalTime;

    printReceivedProccesses(processLog, NUM_PROCESSES);

    cout << "Average time: " << averageArrival << endl;

    // Calculate average service time
    float serviceTimeSum = 0;
    for( int i = 0; i < NUM_PROCESSES; i++ ) 
    {
        serviceTimeSum += processLog[i][2];
    }

    averageService = NUM_PROCESSES/serviceTimeSum;

    cout << "Average Service Time: " << averageService << endl;


}

void generateProcesses(float process_data[][3], float* totalTime, int processes) {
    
    // Generate all processes arrival time & service time
    for( int i = 0; i < processes; i++ ) {
        // Generate arrival time & service time
        float processArrivalTime = generateArrivalTime(ARRIVAL_RATE_S);
        float processServiceTime = generateServiceTime(SERVICE_RATE_S);

        *totalTime += processArrivalTime;
        // Assign ID - arrival time - service time
        process_data[i][0] = i + 1;
        process_data[i][1] = *totalTime;
        process_data[i][2] = processServiceTime;
    } 
}

void printReceivedProccesses(float process_data[][3], int processes ) {
    for( int i = 0; i < processes; i++ ) {
        cout << "<" << process_data[i][0] << "," << process_data[i][1] << "," << process_data[i][2] << ">" << endl;
    }
}

// Generate arrival time via poission distribution
float generateArrivalTime( float lambda ) {
    return -log(1-  ( (float)rand()/RAND_MAX))/lambda;
}

// Generate service time via exponential distribution
float generateServiceTime( float lambda ) {
    return -log(1-  ( (float)rand()/RAND_MAX)) * lambda;
}



