#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct timespec timeinfo;
#define timestamp(sample) clock_gettime(CLOCK_MONOTONIC, (sample))

long diff_nano(struct timespec *start, struct timespec *end);
long diff_micro(struct timespec *start, struct timespec *end);
long diff_milli(struct timespec *start, struct timespec *end);
long diff_seconds(struct timespec *start, struct timespec *end);

#endif
