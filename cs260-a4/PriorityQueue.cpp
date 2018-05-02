#include "PriorityQueue.h"
#include "Process.h"

using namespace std;

const int TIME_SLICE = 20;

PriorityQueue::PriorityQueue(string fileName) {
	this->currentTime = 0;
	this->fileName = fileName;
	this->runSimulation();
}

bool PriorityQueue::getDataFromFile() {
	ifstream fileStream(this->fileName);
	string line;
	if (fileStream.is_open()) {
		while (getline(fileStream, line)) {
			// construct processes from each line
			stringstream stringStream(line);
			cout << line << endl;
			for (int i = 0; i < 2; i++) {
				int initialPriority;
				stringStream >> initialPriority;
				int remainingRunTime;
				stringStream >> remainingRunTime;

				Process newProcess(i, initialPriority, remainingRunTime);
				this->addNewProcess(newProcess);
			}
		}
		fileStream.close();
		return true;
	} else {
		cerr << "Unable to open file";
		return false;
	}
}

void PriorityQueue::addNewProcess(Process newProcess) {
	processQueues[newProcess.getInitialPriority()].push(newProcess);
}

bool PriorityQueue::runSimulation() {
	if (!this->getDataFromFile()) { return false; }
	int currentTime = 0;
	this->printHeader();

	for (int i = 0; i < 5; i++) {
		while (!processQueues[i].empty()) {
			int remainingTime = processQueues[i].front().getRemainingRunTime();
			if (remainingTime == processQueues[i].front().getInitialNeededRuntime()) {
				processQueues[i].front().setStartTime(currentTime);
			}
			if (remainingTime <= TIME_SLICE) {
				// only process it for remaining RunTime 
				processQueues[i].front().setRemainingRunTime(0);
				// print it
				processQueues[i].front().outputStats(currentTime);
				// pop it
				processQueues[i].pop();
				currentTime += remainingTime;
			} else if (remainingTime == 0) {
				// print it
				processQueues[i].front().outputStats(currentTime);
				// pop it
				processQueues[i].pop();
			} else {
				// 20ms won't be enough, just subtract 20 from remaining time
				processQueues[i].front().setRemainingRunTime(remainingTime - TIME_SLICE);
				processQueues[i].front().setTotalRunTime(remainingTime + TIME_SLICE);
				// and push onto next queue, unless we're already in last queue
				int nextQueue = i;
				if (i < 4) { nextQueue++; } 
				processQueues[nextQueue].push(processQueues[i].front());
				processQueues[i].pop();
				currentTime += remainingTime;
			}
		}
	}
	return true;
}

void PriorityQueue::printHeader() {
	cout << "PID	Initial Priority	Time Needed	Start Time	End Time	Elapsed Time	Final Priority" << endl;
}

