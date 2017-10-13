#include <txlib.h>

int const ARR_LENGTH = 250, DEMO_ARR_LENGTH = 100, BORDER_HEIGHT = 50, BORDER_WIDTH = 50, ARR_HEIGHT = 500, ARR_WIDTH = 500;
int GSwaps = 0;

void qwickSort(int arr[], int arrSize, bool show);
void reallyQwickSort(int[], int, int, bool);
void mswap(int arr[], int left, int right, int bearing);
void mswap(int arr[], int left, int right);
void printArr(int arr[], int left, int right, int bearing);
void randomFill(int arr[], int arrSize);

void stickThread(void* param) {
    void(*paramSort)(int arr[], int arrSize, bool show);
    paramSort = (void(*)(int[], int, bool)) param;
    int arr[DEMO_ARR_LENGTH];
    randomFill(arr, DEMO_ARR_LENGTH);
    paramSort(arr, DEMO_ARR_LENGTH, true);
}

void graphicThread(void* param) {
    void(*paramSort)(int arr[], int arrSize, bool show);
    paramSort = (void(*)(int[], int, bool)) param;
    int arr[ARR_LENGTH];
    randomFill(arr, ARR_LENGTH);
    txBegin();
    txSetFillColor(RGB(0, 0, 0));
    txRectangle(BORDER_WIDTH * 3 + ARR_WIDTH, BORDER_HEIGHT, BORDER_WIDTH * 3 + ARR_WIDTH * 2, BORDER_HEIGHT + ARR_HEIGHT);
    txSetFillColor(RGB(255, 255, 255));
    int pGSwaps = 0;
    for(int i = 1; i < ARR_LENGTH; i++) {
        paramSort(arr, i, false);
        printf("%d\n", GSwaps);
        txLine(3 * BORDER_WIDTH + ARR_WIDTH + i * ARR_WIDTH / ARR_LENGTH, BORDER_HEIGHT + ARR_HEIGHT - GSwaps, 3 * BORDER_WIDTH + ARR_WIDTH + (i - 1) * ARR_WIDTH / ARR_LENGTH, BORDER_HEIGHT + ARR_HEIGHT - pGSwaps);
        pGSwaps = GSwaps;
        GSwaps = 0;
        txSleep(50);
    }
    txEnd();
}

int main () {
    srand(time(NULL));
    txCreateWindow(4 * BORDER_WIDTH + 2 * ARR_WIDTH, 2 * BORDER_HEIGHT + ARR_HEIGHT);
    _beginthread(stickThread, 0, (void*)&qwickSort);
    _beginthread(graphicThread, 0, (void*)&qwickSort);
    return 0;
}

void qwickSort(int arr[], int lenght, bool show) {
    reallyQwickSort(arr, 0, lenght, show);
}

void reallyQwickSort(int arr[], int leftBorderIn, int rightBorderIn, bool show) {
    int left = leftBorderIn, right = rightBorderIn, x = arr[left], xn = left;
    while (right > left) {
        if (arr[right] > x) right--;
        if (arr[left] < x) left++;
        if (arr[right] <= x && arr[left] >= x) {
            if (show) mswap(arr, left, right, xn);
            else mswap(arr, left, right);
            if (arr[left] == arr[right]) right--;
        }
    }
    if (rightBorderIn - leftBorderIn <= 1) return;
    reallyQwickSort(arr, leftBorderIn, left, show);
    reallyQwickSort(arr, left + 1, rightBorderIn, show);
}

void mswap(int arr[], int left, int right) {
    int fict = arr[left];
    arr[left] = arr[right];
    arr[right] = fict;
    GSwaps++;
}

void mswap(int arr[], int left, int right, int bearing) {
    int fict = arr[left];
    arr[left] = arr[right];
    arr[right] = fict;
    printArr(arr, left, right, bearing);
}

void printArr(int arr[], int left, int right, int bearing) {
    txBegin();
    txSetFillColor(RGB(0, 0, 0));
    txRectangle(BORDER_WIDTH, BORDER_HEIGHT, BORDER_WIDTH + ARR_WIDTH, BORDER_HEIGHT + ARR_HEIGHT);
    for(int i = 0; i < DEMO_ARR_LENGTH; i++) {
        txSetFillColor(RGB(255, 255, 255));
        if (i == left || i == right) txSetFillColor(RGB(255, 0, 0));
        if (i == bearing) txSetFillColor(RGB(0, 255, 0));
        txRectangle(BORDER_WIDTH + i * ARR_WIDTH / DEMO_ARR_LENGTH, ARR_HEIGHT + BORDER_HEIGHT, BORDER_WIDTH + i * ARR_WIDTH / DEMO_ARR_LENGTH + ARR_WIDTH / DEMO_ARR_LENGTH, BORDER_HEIGHT + arr[i] * ARR_HEIGHT / DEMO_ARR_LENGTH);
    }
    txEnd();
}

void randomFill(int arr[], int arrSize) {
    for(int i = 0; i < arrSize; i++) arr[i] = i;
    for(int i = 0; i < arrSize; i++) mswap(arr, i, rand() % arrSize);
    //for(int i = 0; i < arrSize; i++) arr[i] = rand() % arrSize;
}

