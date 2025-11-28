#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifndef PART
#define PART 1
#endif

#define ARRAY_SIZE (1000000)

int main(void) {
    struct timespec t1, t2;
    const int HalfRandMax = (RAND_MAX >> 1) + 1;

    printf("Running part %d\n", PART);

    long long Sum = 0;
#if PART == 2
    long long Sum2 = 0;
    long long Sum3 = 0;
    long long Sum4 = 0;
#endif
    int A[ARRAY_SIZE];
    int B[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        A[i] = rand();
        B[i] = rand();
    }

    clock_gettime(CLOCK_MONOTONIC, &t1);  // Measure start
    for (int i = 0; i < ARRAY_SIZE; i++) {
    #if PART <= 2
        Sum += A[i] + B[i];
    #endif
    #if PART == 2
        Sum2 += A[i] * B[i];
        Sum3 += A[i] << B[i];
        Sum4 += A[i] - B[i];
    #endif
    #if PART == 4
        if (A[i] < HalfRandMax) {
            continue;
        }
    #endif
    #if PART >= 3
        Sum += (A[i] + B[i]) * (A[i] - B[i]);
    #endif
    }
    clock_gettime(CLOCK_MONOTONIC, &t2);  // Measure end

    printf("Sum = %lld\n", Sum);
#if PART == 2
    printf("Sum2 = %lld\n", Sum2);
    printf("Sum3 = %lld\n", Sum3);
    printf("Sum4 = %lld\n", Sum4);
#endif
    printf("Time: %f ms\n", 1e3 * (t2.tv_sec - t1.tv_sec) + 1e-6 * (t2.tv_nsec - t1.tv_nsec));

    return 0;
}
