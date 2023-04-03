#include <iostream>
#include <queue>
#include <random>
#include <iomanip>
#include <stdexcept>

#define NUM_PROCESSES 1000

using namespace std;

struct Process {
    int id;
    double arrivalTime;
    double serviceTime;

    Process(int id, double arrivalTime, double serviceTime)
        : id(id), arrivalTime(arrivalTime), serviceTime(serviceTime) {}
};

struct Event {
    enum EventType { ARRIVAL, DEPARTURE };

    EventType type;
    double time;
    Process *process;

    Event(EventType type, double time, Process *process)
        : type(type), time(time), process(process) {}

    bool operator<(const Event &other) const {
        return time > other.time;
    }
};

double generateExponential(double lambda);
void runSimulator(double arrivalRate, double serviceTime);

int main(int argc, char *argv[]) {
    srand((unsigned) time(NULL));

    double arrivalRate = 0.0;
    double serviceTime = 0.0;

    // If there aren't inputted arguments 
    // then run the system with:
    // arrival rate: 10 processes a second
    // service time: 0.04 seconds
    if (argc != 3 && argc > 1 ) {
        cerr << "Usage: " << argv[0] << " <arrival_rate> <service_time>" << endl;
        return -1;
    } 
    else if ( argc == 1 ) {
        arrivalRate = 10;
        serviceTime = 0.04;
    }
    else {
        arrivalRate = stod(argv[1]);
        serviceTime = stod(argv[2]);
    }

    // Run the simulator
    runSimulator(arrivalRate, serviceTime);

    return 0;
}

void runSimulator(double arrivalRate, double serviceTime) {
    // Declare all variables needed for funcitonality
    priority_queue<Event> eventQueue;
    queue<Process> readyQueue;

    int completedProcesses = 0;
    int processID = 1;
    int totalObservations = 0;
    double clock = 0.0;
    double totalTurnaroundTime = 0.0;
    double totalWaitTime = 0.0;
    double totalServiceTime = 0.0;
    double totalBusyTime = 0.0;
    double totalReadyQueueSize = 0.0;
    double prevClock = 0.0;
    double totalTimeWeightedQueueSize = 0.0;


    // Schedule the first arrival event
    Process process(processID, clock, generateExponential(1/serviceTime));
    readyQueue.push(process);
    eventQueue.push(Event(Event::ARRIVAL, generateExponential(arrivalRate), &process));

    bool cpuBusy = false;

    // Main simulation loop
    while (!eventQueue.empty() && completedProcesses < NUM_PROCESSES) {
        Event event = eventQueue.top();
        eventQueue.pop();
        clock = event.time;

        totalTimeWeightedQueueSize += readyQueue.size() * (clock - prevClock);
        prevClock = clock;

        // Measure the average size of the ready 
        // queue
        totalReadyQueueSize += readyQueue.size();
        totalObservations++;

        if (event.type == Event::ARRIVAL) {
            if (processID <= NUM_PROCESSES - 1) {
                processID++;

                // Generate and enqueue new process
                Process newProcess(processID, clock, generateExponential(1/serviceTime));
                readyQueue.push(newProcess);

                // Generate next arrival event
                eventQueue.push(Event(Event::ARRIVAL, clock + generateExponential(arrivalRate), &newProcess));
            }

            // Schedule departure event if CPU is not busy
            if (!cpuBusy && !readyQueue.empty()) {
                cpuBusy = true;
                Process &frontProcess = readyQueue.front();
                eventQueue.push(Event(Event::DEPARTURE, clock + frontProcess.serviceTime, &frontProcess));
                //cout << "Process " << frontProcess.id << " Depature Time:  " << frontProcess.serviceTime + clock << endl;
            }
        } else {
            // Process departure
            if (!readyQueue.empty()) {
                Process &completedProcess = readyQueue.front();
                readyQueue.pop();

                completedProcesses++;
                totalTurnaroundTime += clock - completedProcess.arrivalTime;
                totalBusyTime += completedProcess.serviceTime;

                totalWaitTime += clock - completedProcess.arrivalTime - completedProcess.serviceTime;
                totalServiceTime += completedProcess.serviceTime;

                // Schedule next departure event if there is a process in the ready queue
                if (!readyQueue.empty()) {
                    Process &frontProcess = readyQueue.front();
                    eventQueue.push(Event(Event::DEPARTURE, clock + frontProcess.serviceTime, &frontProcess));
                } else {
                    cpuBusy = false;
                }
            }
        }
    }

    // Calculate metrics
    double avgTurnaroundTime = totalTurnaroundTime / completedProcesses;
    double cpuUtilization = totalBusyTime / clock;
    double avgWaitTime = totalWaitTime / completedProcesses;
    double avgServiceTime = totalServiceTime / completedProcesses;
    double avgReadyQueueSize = totalTimeWeightedQueueSize / clock;
    double throughput = completedProcesses / clock;

    // Output all simulator stats
    cout << fixed << setprecision(4);
    //cout << "Average wait time: " << avgWaitTime << " seconds" << endl;
    //cout << "Average service time: " << avgServiceTime << " seconds" << endl;
    cout << "Average turnaround time: " << avgTurnaroundTime << " seconds" << endl;
    cout << "Total throughput: " << throughput << " processes per second" << endl;
    cout << "CPU utilization: " << cpuUtilization * 100 << "%" << endl;
    cout << "Average ready queue size: " << avgReadyQueueSize << " processes" << endl;
    
}

           
double generateExponential(double lambda) {
    // Generate a random number between 0 and RAND_MAX
    double randomValue = static_cast<double>(rand()) / RAND_MAX;

    // Use the inverse transform sampling method to generate an exponential random variable
    return -log(1.0 - randomValue) / lambda;
}