#include <stdio.h>
#include <sys/time.h>

#include "sharedFunctions.h"

/**
 * brief: hepler function to calculate the current timestamp in milliseconds
 * @return long long timestamp in milliseconds
 */
long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}