#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int SIZE = 10;
const int MIN = 0;
const int MAX = 100;

int **initMatrix(int height, int width);
void printMatrix(int **matrix, int height, int width);
int smallestOfLargest(int **matrix, int height, int width);
int largestOfSmallest(int **matrix, int height, int width);
double arithmeticMean(int **matrix, int height, int width, int a, int b);

int main()
{
    int width = SIZE;
    int height = SIZE;

    int **matrix = initMatrix(height, width);
    printMatrix(matrix, height, width);

    int smallest = smallestOfLargest(matrix, height, width);
    int largest = largestOfSmallest(matrix, height, width);
    printf("smallest = %d\n", smallest);
    printf("largest = %d\n", largest);

    int a = smallest;
    int b = largest;
    if (smallest > largest) {
        a = largest;
        b = smallest;
    }
    printf("(a, b) = (%d, %d)\n", a, b);

    double mean = arithmeticMean(matrix, height, width, a, b);
    printf("mean = %f\n", mean);

    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

int **initMatrix(int height, int width) {
    int **matrix = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) {
        matrix[i] = malloc(width * sizeof(int));
    }

    srand(time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = MIN + rand() % (MAX - MIN);
        }
    }

    return matrix;
}

void printMatrix(int **matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
}

int smallestOfLargest(int **matrix, int height, int width) {
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

int largestOfSmallest(int **matrix, int height, int width) {
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

double arithmeticMean(int **matrix, int height, int width, int a, int b) {
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
