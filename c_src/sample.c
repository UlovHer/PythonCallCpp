/* sample.c */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

/* Compute the greatest common divisor */
int gcd(int x, int y)
{
  int g = y;
  while (x > 0)
  {
    g = x;
    x = y % x;
    y = g;
  }
  return g;
}

/* Test if (x0,y0) is in the Mandelbrot set or not */
int in_mandel(double x0, double y0, int n)
{
  double x = 0, y = 0, xtemp;
  while (n > 0)
  {
    xtemp = x * x - y * y + x0;
    y = 2 * x * y + y0;
    x = xtemp;
    n -= 1;
    if (x * x + y * y > 4)
      return 0;
  }
  return 1;
}

/* Get Array elem */
int get_elem(int arr[],int index){
  return arr[index];
}

/* Divide two numbers */
int divide(int a, int b, int *remainder)
{
  int quot = a / b;
  *remainder = a % b;
  return quot;
}

/* Average values in an array */
double avg(double *a, int n)
{
  int i;
  double total = 0.0;
  for (i = 0; i < n; i++)
  {
    total += a[i];
  }
  return total / n;
}

/* A C data structure */
typedef struct Point
{
  double x, y;
} Point;

/* Function involving a C data structure */
double distance(Point *p1, Point *p2)
{
  return hypot(p1->x - p2->x, p1->y - p2->y);
}

/* String reversal */
char* reverse(char *str)
{
  // Get string length
  int len = 0;
  char *p = str;
  puts("input string is:\n");
  puts(p);
  while (*p != 0)
  {
    len++;
    p++;
  }

  // Swape
  int i = 0;
  char c;
  while (i <= len / 2 - 1)
  {
    c = *(str + i);
    *(str + i) = *(str + len - 1 - i);
    *(str + len - 1 - i) = c;
    i++;
  }
  // print
  puts("revise string is:\n");
  puts(str);
  return str;
}

/* Populate array, use callback function */
void populate_array(int *array, size_t arraySize, int (*getNextValue)(void))
{
  for (size_t i = 0; i < arraySize; i++)
    array[i] = getNextValue();
}

// Get random value
int getNextRandomValue(void)
{
  return rand();
}