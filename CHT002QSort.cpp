#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <txlib.h>

int const ARR_LENGHT = 700, DBH = 50, DBW = 50, DH = 500, DW = 700;

int binaryFind(int sortedArr[], int startN, int endN, int x);
void ROR(int arr[], int startN, int endN);
void binarySort(int arr[], int lenght);
void printArr(int arr[]);
void printArr(int arr[], int l, int r, int o);
void randomFill(int arr[]);
void mswap(int arr[], int l, int r);
void mswap(int arr[], int l, int r, int o);
void qwickSort(int arr[], int zero, int lenght);

int main () {
    srand(time(NULL));
    int arr[ARR_LENGHT] = {};
    txCreateWindow(2 * DBW + DW, 2 * DBH + DH);
    randomFill(arr);
    printArr(arr, -1, -1, -1);
    txSleep(500);
    qwickSort(arr, 0, ARR_LENGHT);
    //binarySort(arr, ARR_LENGHT);
    printArr(arr, -1, -1, -1);
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

void printArr(int arr[], int l, int r, int o) {
    txBegin();
    txSetFillColor(RGB(0, 0, 0));
    txClear();
    for(int i = 0; i < ARR_LENGHT; i++) {
        txSetFillColor(RGB(255, 255, 255));
        if (i == l || i == r) txSetFillColor(RGB(255, 0, 0));
        if (i == o) txSetFillColor(RGB(0, 255, 0));
        txRectangle(DBW + i * DW / ARR_LENGHT, DH + DBH, DBW + i * DW / ARR_LENGHT + DW / ARR_LENGHT, DBH + arr[i] * DH / ARR_LENGHT);
    }
    txEnd();
}

void randomFill(int arr[]) {
    for(int i = 0; i < ARR_LENGHT; i++) arr[i] = i;
    for(int i = 0; i < ARR_LENGHT; i++) mswap(arr, i, rand() % ARR_LENGHT);
}

void qwickSort(int arr[], int leftIn, int rightIn) {
    int l = leftIn, r = rightIn, x = arr[l], xn = l;
    while (r > l) {
        if (arr[r] > x) r--;
        if (arr[l] < x) l++;
        if (arr[r] <= x && arr[l] >= x) mswap(arr, l, r, xn);
    }
    if (rightIn - leftIn <= 1) return;
    qwickSort(arr, leftIn, l);
    qwickSort(arr, l + 1, rightIn);
}

void mswap(int arr[], int l, int r) {
    int fict = arr[l];
    arr[l] = arr[r];
    arr[r] = fict;
}

void mswap(int arr[], int l, int r, int o) {
    int fict = arr[l];
    arr[l] = arr[r];
    arr[r] = fict;
    printArr(arr, l, r, o);
}
