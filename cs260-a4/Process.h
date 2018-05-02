#pragma once
#include<iostream>
class Process {
private:
	int processID;
	int initialPriority;
	int initialNeededRuntime;
	int totalRunTime;
	int remainingRunTime;
	int currentPriority;
	int startTime;
public:
	Process(int processID, int initialPriority, int remainingRunTime);
	int getProcessID();
	int getInitialPriority();
	int getTotalRunTime();
	int getRemainingRunTime();
	int getCurrentPriority();
	int getInitialNeededRuntime();
	int setRemainingRunTime(int runTime);
	int setCurrentPriority(int priority);
	int setTotalRunTime(int currentTime);
	int setStartTime(int currentTime);
	void outputStats(int currentTime);
};

