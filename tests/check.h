#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define CHECK(condition) do { if (!(condition)) { fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); exit(EXIT_FAILURE); } } while (0)
#define NEAR(actual, expected) CHECK(fabsf((actual) - (expected)) < 0.00001f)
