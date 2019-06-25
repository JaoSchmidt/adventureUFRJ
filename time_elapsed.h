///criada em 15/06/19
#ifndef TIME_ELAPSED_HEADER
#define TIME_ELAPSED_HEADER

struct timespec spec;
/*This function return false if elapsed time since it was 
called is smaller than the value of the second parameter 
in seconds. If value is bigger, returns true and reset 
the time elapsed*/
float time_elapsed(float *tv0,float limit){
    clock_gettime(CLOCK_MONOTONIC, &spec);
    float a;
    a = spec.tv_sec + ((float)spec.tv_nsec/1.0e9);
    if(a - *tv0 >= limit){
        *tv0 = a;
        return 1;
    }
    return 0;
}

#endif

/*CLOCK_MONOTONIC represents the absolute elapsed wall-clock 
time since some arbitrary, fixed point in the past. It isn't
 affected by changes in the system time-of-day clock.

If you want to compute the elapsed time between two events 
observed on the one machine without an intervening reboot, 
CLOCK_MONOTONIC is the best option.*/

