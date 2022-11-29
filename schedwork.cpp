

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t shift_counter[],
    size_t row,
    size_t col);

bool isValid(
    const size_t maxShifts,
    DailySchedule& sched,
    size_t row,
    size_t col);



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
    
    for(size_t i = 0; i < avail.size(); i++){ // avail.size() = n days
      std::vector<Worker_T> temp(dailyNeed, INVALID_ID);
      sched.push_back(temp);
    }
    size_t* shift_counter = new size_t[avail[0].size()];
    // Store shift counts of k possible workers as the size, provided from avail[0].size()
    for(size_t i = 0; i < avail[0].size(); i++){
      shift_counter[i] = 0; // Make every worker start with 0 shifts given
    }
    bool foundSchedule = schedule_helper(avail, dailyNeed, maxShifts, sched, shift_counter, 0, 0);
    delete[] shift_counter;
    return foundSchedule;
}

bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t shift_counter[],
    size_t row,
    size_t col){
      
    if(row == avail.size()){
        return true; // avail.size() = n days
    }
    for(size_t i = 0; i < avail[row].size(); i++){ // Iterate through all workers for a given day
        if( avail[row][i] == 1 && shift_counter[i] + 1 <= maxShifts){ 
            // If worker is available to work and if adding a shift stays within max shift constraint
            sched[row][col] = i; // Put worker id in the schedule cell (will be overridden on next iteration if schedule doesn't work)
            shift_counter[i]++; // Add the shift to the worker's shift counter
            if(col == dailyNeed - 1){
                if(schedule_helper(avail, dailyNeed, maxShifts, sched, shift_counter, row + 1, 0) == true){
                    return true;
                }
            }
            else{
                if(schedule_helper(avail, dailyNeed, maxShifts, sched, shift_counter, row, col + 1) == true){
                    return true;
                }
            }
            shift_counter[i]--; // Remove worker's shift if sched ended up being invalid
        }
    }
    return false;
}