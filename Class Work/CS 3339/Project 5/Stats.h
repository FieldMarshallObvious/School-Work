/******************************
 * Copyright 2021, Lee B. Hinkle, all rights reserved
 * Based on prior work by Martin Burtscher and Molly O'Neil
 * Redistribution in source or binary form, with or without modification,
 * is *not* permitted. Use in source or binary form, with or without
 * modification, is only permitted for academic use in CS 3339 at
 * Texas State University.
 ******************************/
#ifndef __STATS_H
#define __STATS_H
#include <iostream>
#include <iomanip>
#include "Debug.h"
using namespace std;

enum PIPESTAGE { IF1 = 0, IF2 = 1, ID = 2, EXE1 = 3, EXE2 = 4, MEM1 = 5, 
                 MEM2 = 6, WB = 7, PIPESTAGES = 8 };

class Stats {
  private:
    long long cycles;
    int flushes;
    int bubbles;

    int memops;
    int branches;
    int taken;

    int hazardsEXE1;
    int hazardsEXE2;
    int hazardsMEM1;
    int hazardsMEM2;
    int RAWhazards;

    int resultReg[PIPESTAGES];
    int resultStage[PIPESTAGES];

  public:
    Stats();

    void clock();

    void flush(int count);

    void registerSrc(int r, int needed);
    void registerDest(int r, int available);

    void countMemOp() { memops++; }
    void countBranch() { branches++; }
    void countTaken() { taken++; }
	
    void showPipe();

    // getters
    long long getCycles() { return cycles; }
    int getFlushes() { return flushes; }
    int getBubbles() { return bubbles; }
    int getMemOps() { return memops; }
    int getBranches() { return branches; }
    int getTaken() { return taken; }
    int getHazardsEXE1() {return hazardsEXE1; }
    int getHazardsEXE2() { return hazardsEXE2; }
    int getHazardsMEM1() { return hazardsMEM1; }
    int getHazardsMEM2() { return hazardsMEM2; }
    int getRAWHazards() { return RAWhazards; }

  private:
    void bubble();
};

#endif
