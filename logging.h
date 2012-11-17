#ifndef __LOGGING_H__
#define __LOGGING_H__

#include <stdio.h>
#ifndef NDEBUG
#define LOG_DEBUG(fmt, ...)     fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#else
#define LOG_DEBUG(...)
#endif

#endif
