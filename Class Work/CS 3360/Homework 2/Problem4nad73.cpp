#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <chrono>
#include <fstream>

#define MTBF_H 500
#define SERVICE_TIME_H 10 
#define TIME_INTERVAL_Y 20

using namespace std;

void generateFailureData( bool *server1Data, int timeframe );
void outputServerData( bool server1Data[], bool server2Data[], int timeframe );
int testEquivalentTime( int timeframe );
float generateExpTime(float lamda);

int main() {
    // Seed ranom num generator
    srand((unsigned) time(NULL));

    int samples = 365 * 24 * TIME_INTERVAL_Y;
    bool server1Data[samples];
    bool server2Data[samples];

    std::fill(server1Data, server1Data + samples, false);
    std::fill(server2Data, server2Data + samples, false);


    // Generate failuree data & service data
    generateFailureData( server1Data, samples );
    generateFailureData( server2Data, samples );

    // Output Data 
    outputServerData(server1Data, server2Data, samples);

    // Find how much time is required for system failure
    double averageTime = 0;
    int totalRecordTime = 0;
    for( int i = 0; i < 29; i++ )
    {
        totalRecordTime += testEquivalentTime(samples);
    }
    averageTime = totalRecordTime/30.0;

    cout << "Average Time To Total System Failure: " << averageTime << endl;

}

// Output the server data to console & a text file
void outputServerData( bool server1Data[], bool server2Data [], int timeframe ) {
    // Open text file
    ofstream outputFile;

    outputFile.open("P4outnad73.txt");

    int totalFailuresS1 = 0;
    int totalFailuresS2 = 0;
    int totalDowntimeS1 = 0;
    int totalDowntimeS2 = 0;

    for( int i = 0; i < timeframe; i++ ) {
        
        // Output server 1 failures to file
        if (server1Data[i])
        {
            // output to file
            outputFile << "------------------" << endl;
            outputFile << "Server 1 " << endl
                << "Failed at time (hours) " << i << endl 
                << "Service time (hours) " << i + 10 << endl;
            outputFile << "------------------" << endl;

            totalDowntimeS1 += 10;

            totalFailuresS1 += 1;
        }

        // Outuput server 2 failures to file
        if (server2Data[i])
        {
            outputFile << "------------------" << endl;
            outputFile << "Server 2 " << endl
                << "Failed at time (hours) " << i << endl 
                << "Service time (hours) " << i + 10 << endl;
            outputFile << "------------------" << endl;

            totalDowntimeS2 += 10;

            totalFailuresS2 += 1;
        }

        // Output to console and file
        if( i == timeframe - 2 ) 
        {
            outputFile << "Total Failures S1: " << totalFailuresS1 << endl;
            outputFile << "Total Failures S2: " << totalFailuresS2 << endl;

            outputFile << "Total Down Time S1: " << totalDowntimeS1 << endl;
            outputFile << "Total Down Time S2: " << totalDowntimeS2 << endl;

            cout << "Total Failures S1: " << totalFailuresS1 << endl;
            cout << "Total Failures S2: " << totalFailuresS2 << endl;

            cout << "Total Down Time S1: " << totalDowntimeS1 << endl;
            cout << "Total Down Time S2: " << totalDowntimeS2 << endl;        
        }
    }

    outputFile.close();
}

int testEquivalentTime( int timeframe ) {
    // Record final 
    int firstFailureHour = 0;

    // Generate synethic server data
    bool server1Data[timeframe];
    bool server2Data[timeframe];

    // Setup array
    std::fill(server1Data, server1Data + timeframe, false);
    std::fill(server2Data, server2Data + timeframe, false);

    // Generate data
    generateFailureData(server1Data, timeframe);
    generateFailureData(server2Data, timeframe);

    // Seek full system failure
    for( int i = 0; i < timeframe; i++ )
    {
      // If the server failed at this point
      // check surrouding points 
      if(server1Data[i])
      {
        for( int j = (i - 10 > 0 ? i - 10 : 0); j < (i + 10 < timeframe - 1 ? i + 10:timeframe-1); j++ )
        {
            if(server2Data[j])
            {
                firstFailureHour = (i + j)/2;
            }
        }
      }  
    } 

    return firstFailureHour;
}

void generateFailureData( bool serverData[], int timeframe ) {
    int i = 0;
    float totalTime = 0;
    float serverFailedTime = 0;
    float totalPr = 0;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    exponential_distribution<float> distribution (MTBF_H);

    while( i < timeframe ) {
        // Generate probability this is the failure
        totalPr += distribution(generator);

        // Only peform the operations if it's within the timeframe
        if( totalPr >= 1.0 ) 
        {
            totalPr = 0;
            // store failed time in approriate index 
            serverData[i] = true;

            i += 10;
        } 
        i++;
    }

}

float generateExpTime(float lambda) {
    return -log( 1 - ((float)rand()/RAND_MAX)) * lambda;
}
