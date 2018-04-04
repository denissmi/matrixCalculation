#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 10
#define MIN 0
#define MAX 100
int matrix[SIZE][SIZE];

void initMatrix(int height, int width);
void printMatrix(int height, int width);
int smallestOfLargest(int height, int width);
int largestOfSmallest(int height, int width);
double arithmeticMean(int height, int width, int a, int b);

int main()
{
    int width = SIZE;
    int height = SIZE;

    initMatrix(height, width);
    printMatrix(height, width);

    int smallest = smallestOfLargest(height, width);
    int largest = largestOfSmallest(height, width);
    printf("smallest = %d\n", smallest);
    printf("largest = %d\n", largest);

    int a = smallest;
    int b = largest;
    if (smallest > largest) {
        a = largest;
        b = smallest;
    }
    printf("(a, b) = (%d, %d)\n", a, b);

    double mean = arithmeticMean(height, width, a, b);
    printf("mean = %f\n", mean);

    return 0;
}

void initMatrix(int height, int width) {
    srand(time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = MIN + rand() % (MAX - MIN);
        }
    }
}

void printMatrix(int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

int smallestOfLargest(int height, int width) {
    int smallest = MAX;
    int maximum = MIN;
    for (int i = 0; i < height; i++) {
        if ((i+1)%2 == 0) {
            for (int j = 0; j < width; j++) {
                if (matrix[i][j] > maximum) {
                    maximum = matrix[i][j];
                }
            }
            if (maximum < smallest) {
                smallest = maximum;
            }
            maximum = MIN;
        }
    }
    return smallest;
}

int largestOfSmallest(int height, int width) {
    int largest = MIN;
    int minimum = MAX;
    for (int i = 0; i < height; i++) {
        if ((i+1)%2 != 0) {
            for (int j = 0; j < width; j++) {
                if (matrix[i][j] < minimum) {
                    minimum = matrix[i][j];
                }
            }
            if (minimum > largest) {
                largest = minimum;
            }
            minimum = MAX;
        }
    }
    return largest;
}

double arithmeticMean(int height, int width, int a, int b) {
    double sum = 0;
    int count = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < i+1; j++) {
            if (matrix[i][j] > a && matrix[i][j] < b) {
                sum += matrix[i][j];
                count++;
            }
        }
    }
    return sum / count;
}
