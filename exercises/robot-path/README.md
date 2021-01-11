A robot can make steps of only predefined lengths in only one direction. Given an array of possible step sizes and its length, write a recursive function able to calculate all sequences of steps **(order matters)** that makes the robot cover an exact distance, also given to the function.

The prototype should be as follows:

``` C
/*
 *  - distances : array with possible step sizes
 *  - n         : size of the aforementioned array
 *  - distance  : distance to cover
 */
void cover(int *distances, int n, int distance);
```