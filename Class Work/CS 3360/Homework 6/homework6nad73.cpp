#include <iostream>
#include <queue>
#include <random>
#include <iomanip>
#include <stdexcept>
#include <vector>

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
    int readyQueue;
    Process *process;

    Event(EventType type, double time, Process *process,int readyQueue = 0)
        : type(type), time(time), readyQueue(readyQueue), process(process) {}

    bool operator<(const Event &other) const {
        return time > other.time;
    }
};

struct CPU {
    Process* curProcess;
    bool busy;

    CPU() : curProcess(nullptr), busy(false) {} // Initialize curProcess as a nullptr
};

struct SimulationState {
    int completedProcesses = 0;
    int processID = 1;
    int totalObservations = 0;
    double clock = 0.0;
    double totalTurnaroundTime = 0.0;
    double totalWaitTime = 0.0;
    double totalServiceTime = 0.0;
    vector<double> cpuBusyTime;
    double totalReadyQueueSize = 0.0;
    double prevClock = 0.0;
    double totalTimeWeightedQueueSize = 0.0;
    vector<bool> cpuBusy;
    vector<double> cpuTurnaroundTime;
    vector<double> cpuWaitTime;
    vector<double> cpuServiceTime;
    vector<int> cpuCompletedProcesses;
};



double generateExponential(double lambda);
void runSimulator(double arrivalRate, double serviceTime, int total_cpus, int total_ready_queues, int scenario);
void runEvent(Event event, double arrivalRate, double serviceTime, queue<Process*> &readyQueue, priority_queue<Event> &eventQueue, SimulationState &curState, 
              int total_ready_queues);

int main(int argc, char *argv[]) {
    srand((unsigned) time(NULL));

    double arrivalRate = 0.0;
    double serviceTime = 0.0;
    int total_cpus = 0;
    int total_ready_queues = 0;
    int scenario = 0;

    // If there aren't inputted arguments 
    // then run the system with:
    // arrival rate: 10 processes a second
    // service time: 0.04 seconds
    if (argc != 5 && argc > 1 ) {
        cerr << "Usage: " << argv[0] << " <arrival_rate> <service_time> <# of cpus> <scenario>" << endl;
        return -1;
    } 
    else if ( argc == 1 ) {
        arrivalRate = 10;
        serviceTime = 0.04;
        total_cpus = 1;
        total_ready_queues = 1;
        scenario = 1;
    }
    else {
        try {
            arrivalRate = stod(argv[1]);
            serviceTime = stod(argv[2]);
            total_cpus = stoi(argv[3]);
            total_ready_queues = total_cpus;
            scenario = stoi(argv[4]);
        } catch(...) {
            cerr << "Possible type mismatch - Types are <double> <double> <int> <int>" << endl;
            return -1;
        }
    }

    // Run the simulator
    runSimulator(arrivalRate, serviceTime, total_cpus, total_ready_queues, scenario);

    return 0;
}

void runSimulator(double arrivalRate, double serviceTime, int total_cpus, int total_ready_queues, int scenario) {
    // Declare all variables needed for funcitonality
    SimulationState curState;

    // Initialize the cur states
    curState.cpuBusy.resize(total_cpus, false);
    curState.cpuBusyTime.resize(total_cpus, 0.0);
    curState.cpuTurnaroundTime.resize(total_cpus, 0.0);
    curState.cpuWaitTime.resize(total_cpus, 0.0);
    curState.cpuServiceTime.resize(total_cpus, 0.0);
    curState.cpuCompletedProcesses.resize(total_cpus, 0);

    priority_queue<Event> eventQueue;
    vector<queue<Process*> > readyQueue(total_ready_queues, queue<Process*>());



    // If scenario 1, then choose the ready queue at random
    int choosenReadyQueue = (scenario == 1 && total_ready_queues > 1) ? (rand() % (total_ready_queues - 1) + 0) : 0;

    // Schedule the first arrival event
    Process* process = new Process(curState.processID, curState.clock, generateExponential(1 / serviceTime));
    
    readyQueue[choosenReadyQueue].push(process);

    eventQueue.push(Event(Event::ARRIVAL, generateExponential(arrivalRate), process, choosenReadyQueue));

    // Main simulation loop
    while (!eventQueue.empty() && curState.completedProcesses < NUM_PROCESSES) {
        Event event = eventQueue.top();
        eventQueue.pop();
        curState.clock = event.time;

        curState.totalTimeWeightedQueueSize += readyQueue[event.readyQueue].size() * (curState.clock - curState.prevClock);
        curState.prevClock = curState.clock;


        // Measure the average size of the ready 
        // queue
        curState.totalReadyQueueSize += readyQueue[event.readyQueue].size();
        curState.totalObservations++;

        // Generate new event 
        if (event.type == Event::ARRIVAL && curState.processID <= NUM_PROCESSES - 1) {
            // Chose ready queue
            int newChoosenReadyQueue = (scenario == 1 && total_ready_queues > 1) ? (rand() % (total_ready_queues) + 0) : 0;
            curState.processID++;

            // Generate and enqueue new process
            Process *newProcess = new Process(curState.processID, curState.clock, generateExponential(1 / serviceTime));
            readyQueue[newChoosenReadyQueue].push(newProcess);

            // Generate next arrival event
            eventQueue.push(Event(Event::ARRIVAL, curState.clock + generateExponential(arrivalRate), newProcess, newChoosenReadyQueue));
        }
        
        // Process each event
        runEvent(event, arrivalRate, serviceTime, readyQueue[event.readyQueue], eventQueue, curState, total_ready_queues);
       
    }


    // Output all simulator cpu stats
     cout << fixed << setprecision(4);

    for (int i = 0; i < total_cpus; i++) {
        // Calculate metrics
        double avgTurnaroundTime = curState.cpuTurnaroundTime[i] / curState.cpuCompletedProcesses[i];
        double cpuUtilization = curState.cpuBusyTime[i] / curState.clock * 100;
        double avgWaitTime = curState.cpuWaitTime[i] / curState.cpuCompletedProcesses[i];
        double avgServiceTime = curState.cpuServiceTime[i] / curState.cpuCompletedProcesses[i];
        double throughput = curState.cpuCompletedProcesses[i]/curState.clock ;
        double avgReadyQueueSize = curState.totalTimeWeightedQueueSize / curState.clock;

        cout << "CPU " << i + 1 << " Metrics:" << endl;
        cout << "----------------" << endl;
        cout << "Average turnaround time: " << avgTurnaroundTime << " seconds" << endl;
        cout << "Throughput: " << throughput << " processes per second" << endl;
        cout << "CPU utilization: " << cpuUtilization << "%" << endl;
        cout << "Average wait time: " << avgWaitTime << " seconds" << endl;
        cout << "Average service time: " << avgServiceTime << " seconds" << endl;
        cout << "Average ready queue size: " << avgReadyQueueSize << " processes" << endl;
        cout << endl;
    }    
}
 
void runEvent(Event event, double arrivalRate, double serviceTime, queue<Process*> &readyQueue, priority_queue<Event> &eventQueue,
              SimulationState &curState, int total_cpus) {
    if (event.type == Event::ARRIVAL) {
        // Schedule departure event if the corresponding CPU is not busy
        if (!curState.cpuBusy[event.readyQueue] && !readyQueue.empty()) {
            curState.cpuBusy[event.readyQueue] = true;
            Process &frontProcess = *readyQueue.front();
            eventQueue.push(Event(Event::DEPARTURE, curState.clock + frontProcess.serviceTime, &frontProcess, event.readyQueue));
        }
    } else {
        // Process departure
        if (!readyQueue.empty()) {
            Process &completedProcess = *readyQueue.front();
            readyQueue.pop();

            curState.completedProcesses++;
            curState.cpuBusyTime[event.readyQueue] += completedProcess.serviceTime;
            curState.cpuTurnaroundTime[event.readyQueue] += curState.clock - completedProcess.arrivalTime;
            curState.cpuWaitTime[event.readyQueue] += curState.clock - completedProcess.arrivalTime - completedProcess.serviceTime;
            curState.cpuServiceTime[event.readyQueue] += completedProcess.serviceTime;
            curState.cpuCompletedProcesses[event.readyQueue]++;


            // Set the corresponding CPU to not busy
            curState.cpuBusy[event.readyQueue] = false;

            // Schedule next departure event if there is a process in the ready queue for the corresponding CPU
            if (!readyQueue.empty()) {
                Process &frontProcess = *readyQueue.front();
                eventQueue.push(Event(Event::DEPARTURE, curState.clock + frontProcess.serviceTime, &frontProcess, event.readyQueue));
            }

            // Delete the completed process
            delete &completedProcess;
        }
    }
}


           
double generateExponential(double lambda) {
    // Generate a random number between 0 and RAND_MAX
    double randomValue = static_cast<double>(rand()) / RAND_MAX;

    // Use the inverse transform sampling method to generate an exponential random variable
    return -log(1.0 - randomValue) / lambda;
}