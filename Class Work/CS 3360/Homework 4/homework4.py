import sys
from collections import deque
import random as rn
import numpy as np
from queue import PriorityQueue


def poisson(n=1):
    randomUniform = rn.uniform(0, 1)
    poissonValue = (np.log(randomUniform))/(-n)
    return poissonValue

class Process:
	def __init__(self, params):
		self.id = params.get('id')
		self.AT = params.get('AT')
		self.ST = params.get('ST')
		self.RT = params.get('ST')
		self.CT = 0

def createProcess(pParams):
	processParams = {
		"id" : pParams.get("id"),
		"AT" : float(pParams.get("clock") + poisson(pParams.get("lmbda"))),
		"ST" : float(poisson(pParams.get("mu")))
  }
	return Process(processParams)

class Event:
	def __init__(self, eventParams):
		self.type = eventParams.get('type')
		self.time = eventParams.get('time')
		self.process = eventParams.get('process')

def arrivalEvent(pParams):
	newProcess = createProcess(pParams)
	event = {
		"type" : "ARR",
		"time" : newProcess.AT,
		"process" : newProcess
	}
	return Event(event)

def departureEvent(process, time):
	event = {
		"type" : "DEP",
		"time" : time,
		"process" : process
	}
	return Event(event)

def FCFS_scheduler(processParams, nCompletions=10_000):
	readyQ = deque()
	eventQ = PriorityQueue()
	qSize = 0
 
	recordData = []

	pCount = 0
 
	isCPUIdle = True
	utilizationTime = 0
	totalCpuTime = 0

	arrEvent = arrivalEvent(processParams)
	processParams["id"] += 1
	eventQ.put((arrEvent.time, arrEvent))

	while pCount < nCompletions:
		clock, currentEvent = eventQ.get()
		currentProcess = currentEvent.process

		if(currentEvent.type == "ARR"):
			if isCPUIdle:
				isCPUIdle = False
				totalCpuTime += clock - utilizationTime
				depEvent = departureEvent(currentProcess, clock + currentProcess.ST)
				eventQ.put((depEvent.time, depEvent))
			else:
				readyQ.append(currentProcess)
				qSize += 1

			processParams.update({'clock': clock})
			arrEvent = arrivalEvent(processParams)
			processParams["id"] += 1
			eventQ.put((arrEvent.time, arrEvent))

		elif(currentEvent.type == "DEP"):
			if (len(readyQ) == 0):
				isCPUIdle= True
				utilizationTime = clock
			else:
				qSize -= 1
				queuedProcess = readyQ.pop()
				depEvent = departureEvent(queuedProcess, clock + queuedProcess.ST)
				eventQ.put((depEvent.time, depEvent))

			recordData.append({
				"cpuTime": currentProcess.ST,
				"turnaroundTime": clock - currentProcess.AT,
				"queueSize": qSize,
			})
			pCount += 1

	if not eventQ.empty():
		lastEvent = eventQ.get()[1]
		clock = lastEvent.time + lastEvent.process.ST
		processParams.update({'clock': clock})

	processParams.update({'CPU_IddleTime': totalCpuTime})
	return recordData
	
def computeStatistics(recordedData, processParams, nCompletions=10000):
	averageTurnaroundTime = 0
	averageQueueSize = 0
	averageCpuUtilization = 0
 
	for data in recordedData:
		averageTurnaroundTime += data.get('turnaroundTime')
		averageQueueSize += data.get('queueSize')
		averageCpuUtilization += data.get('cpuTime')

	averageTurnaroundTime /= nCompletions
	averageQueueSize /= nCompletions
	averageCpuUtilization /= processParams.get('clock')
	throughput = nCompletions / processParams.get('clock')

	print(f"Average Turnaround Time: {averageTurnaroundTime}")
	print(f"Average Queue Size: {averageQueueSize}")
	print(f"Average CPU Utilization: {averageCpuUtilization}")
	print(f"Throughput: {throughput}")
 
	return {"averageTurnaroundTime": averageTurnaroundTime, "averageQueueSize": averageQueueSize, "averageCpuUtilization": averageCpuUtilization, "throughput": throughput}

def graphData(data, xLabel, yLabel, title):
	import matplotlib.pyplot as plt
	plt.plot(data)
	plt.xlabel(xLabel)
	plt.ylabel(yLabel)
	plt.title(title)
	plt.savefig(f"{title}.png")
	plt.show()
    
def run_fcfs(lmbda=10, averageST=0.04):
    process = {
        "id": 0,
        "clock": 0.0,
        "lmbda": lmbda,
        "averageST": averageST,
        "mu": 1.0 / averageST,
    }
    dataList = FCFS_scheduler(process, nCompletions=10000)
    stats = computeStatistics(dataList, process, nCompletions=10000)
    return stats
    
if __name__ == "__main__":
    try:
        lmbda = float(sys.argv[1])
        averageST = float(sys.argv[2])
        
    except:
        lmbda = 10
        averageST = 0.04
        
    run_fcfs(lmbda, averageST)
    
    # runstats = []
    # for lam in range(10,31):
    #     runstats.append(run_fcfs(lam, averageST))
    
    # # Compute the average turnaround time, average queue size, average CPU utilization, and throughput for each value of λ.
    # averageSTs = [runstat['averageTurnaroundTime'] for runstat in runstats]
    # averageQs = [runstat['averageQueueSize'] for runstat in runstats]
    # averageCpuUtilizations = [runstat['averageCpuUtilization'] for runstat in runstats]
    # averageThroughputs = [runstat['throughput'] for runstat in runstats]
    
    # print(f"Average Turnaround Time: {averageSTs}")
    # print(f"Average Queue Size: {averageQs}")
    # print(f"Average CPU Utilization: {averageCpuUtilizations}")
    # print(f"Throughput: {averageThroughputs}")
    
    # for lam in range(10,31):
    #     graphData(averageSTs, 'λ', 'Average Turnaround Time', f'Average Turnaround Time for λ = {lam}')
    #     graphData(averageQs, 'λ', 'Average Queue Size', f'Average Queue Size for λ = {lam}')
    #     graphData(averageCpuUtilizations, 'λ', 'Average CPU Utilization', f'Average CPU Utilization for λ = {lam}')
    #     graphData(averageThroughputs, 'λ', 'Throughput', f'Throughput for λ = {lam}')