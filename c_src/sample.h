/* sample.h */
#pragma once
#ifndef _SAMPLE_H_
#define _SAMPLE_H_
#include <stddef.h>
extern int gcd(int x, int y);
extern int in_mandel(double x0, double y0, int n);
int get_elem(int arr[],int index)
extern int divide(int a, int b, int *remainder);
extern double avg(double *a, int n);
extern char* reverse(char *str);
extern void populate_array(int *array, size_t arraySize, int (*getNextValue)(void));

typedef struct Point {
    double x,y;
} Point;

extern double distance(Point *p1, Point *p2);
#endif
