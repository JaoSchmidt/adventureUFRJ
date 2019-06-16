///criada em 15/06/19
#ifndef TIME_ELAPSED_HEADER
#define TIME_ELAPSED_HEADER

struct timespec spec;

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
