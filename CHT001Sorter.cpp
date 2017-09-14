#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <txlib.h>

int const ARR_LENGHT = 4000;

int binaryFind(int sortedArr[], int startN, int endN, int x);
void ROR(int arr[], int startN, int endN);
void binarySort(int arr[], int lenght);
void printArr(int arr[]);
void randomFill(int arr[]);
void mswap(int arr[], int l, int r);
void qwickSort(int arr[], int zero, int lenght);

int main () {
    srand(time(NULL));
    int arr[ARR_LENGHT] = {};
    randomFill(arr);
    //printArr(arr);
    qwickSort(arr, 0, ARR_LENGHT);
    //binarySort(arr, ARR_LENGHT);
    printArr(arr);
    return 0;
}

void binarySort(int arr[], int lenght) {
    for(int i = 0; i <= lenght; i++) {
        ROR(arr, binaryFind(arr, 0, i, arr[i]), i);
    }
}

void ROR(int arr[], int startN, int endN) {
    int fict = arr[endN];
    for(int i = endN - 1; i >= startN; i--) arr[i + 1] = arr[i];
    arr[startN] = fict;
}

int binaryFind(int arr[], int startN, int endN, int x) {
    int r = endN, l = startN;
    while(r - l > 3) {
        int m = floor((r + l) / 2);
        if(arr[m] > x) r = m;
        else l = m;
    }
    for (int i = l; i < r; i++) if (arr[i] > x) return i;
    return r;
}

void printArr(int arr[]) {
//    for(int i = 0; i < ARR_LENGHT; i++) printf("%d\n", arr[i]);
    for(int i = 0; i < ARR_LENGHT; i++) {
        printf("-");
        for(int j = 0; j < arr[i]; j++) printf(".");
        printf("\n");
    }
    printf("\n");
}

void randomFill(int arr[]) {
    for(int i = 0; i < ARR_LENGHT; i++) arr[i] = rand() % 80;
}

void qwickSort(int arr[], int leftIn, int rightIn) {
    int l = leftIn, r = rightIn, x = l;
    while (r > l) {
        bool canSwap = true;
        if (arr[r] >= arr[x]) {
            r--;
            canSwap = false;
        }
        if (arr[l] <= arr[x] && canSwap) l++;
        if (arr[r] < arr[l]) mswap(arr, l, r);
    }
    if (rightIn - leftIn <= 1) return;
    qwickSort(arr, leftIn, x);
    qwickSort(arr, x + 1, rightIn);
}

void mswap(int arr[], int l, int r) {
    int fict = arr[l];
    arr[l] = arr[r];
    arr[r] = fict;
}
