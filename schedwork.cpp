#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

bool sched_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int pos
);

int scheduled_days(Worker_T worker, DailySchedule& sched, int sum);

// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    sched.resize(avail.size());

    for (int i = 0; i < sched.size(); i++) {
        sched.at(i).resize(dailyNeed);
        for (int j = 0; j < sched.at(i).size(); j++) {
            sched.at(i).at(j) = INVALID_ID;
        }
    }

    return sched_helper(avail, dailyNeed, maxShifts, sched, 0, 0);

}

bool sched_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int pos
)
{

    /*
    try all candidate workers
    for each candidate:
    - if candidate is not available on that day, move on to next
    - if candidate is already scheduled for maxShifts, move on to next
    - if you do both of these and can't find a candidate for that day, return false, 
    - return true only on a valid fill of the schedule
    */


    // base case: recursive call happened a non-existent extra day

    if (day == avail.size()) return true;

    for (Worker_T candidate = 0; candidate < avail[0].size(); ++candidate)
    {

       
        
        // attempt to schedule worker here
        // if worker is not scheduled, sched spot will remain as invalid

        int scheduledDays = scheduled_days(candidate, sched, 0);
        bool alreadyScheduled = (find(sched[day].begin(), sched[day].end(), candidate) != sched[day].end());
        

        if (avail[day][candidate] != 1) {
            continue;
        } 
        else if (scheduledDays >= maxShifts) {
            continue; 
        } 
        else if (alreadyScheduled) {
            continue;
        } 
        else {

            sched[day][pos] = candidate;

            if (pos == dailyNeed-1) {
                if (sched_helper(avail, dailyNeed, maxShifts, sched, day + 1, 0)) {
                    return true;
                }
            }
            else {
                if (sched_helper(avail, dailyNeed, maxShifts, sched, day, pos + 1)) {
                    return true;
                }
            }

        }

        

    }

    // return conditions
    sched[day][pos] = INVALID_ID;
    return false;

}

int scheduled_days(Worker_T worker, DailySchedule& sched, int sum) 
{

    vector<Worker_T> current = sched.at(sum);

    if (sum == sched.size()-1) 
    {
        if (find(current.begin(), current.end(), worker) != current.end()) return 1;
        else return 0;
    }
    else
    {
        if (find(current.begin(), current.end(), worker) != current.end()) 
        {
            return 1 + scheduled_days(worker, sched, sum+1);
        }
        else 
        {
            return scheduled_days(worker, sched, sum+1);
        }
    }
}

