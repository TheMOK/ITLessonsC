#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <txlib.h>

int const BUTTONS_NUMBER = 1, ARR_LENGTH = 100, BORDER_HEIGHT = 50, BORDER_WIDTH = 50, ARR_HEIGHT = 500, ARR_WIDTH = 1000;

void stickThread(void* param){
    int arr[ARR_LENGTH] = {1};
    (*(((void(*)(int[], int, bool)
    )
    *)param
    ))();
}

struct Branch {
    int number, parent, smallChild, bigChild, repeats;
};

class Button {
    private:
    int _x, _y, _width, _height;
    void(*_sort)(int arr[], int length, bool show);
    public:
    Button (void(*sort)(int[], int, bool), int x, int y, int width, int height) {
        _sort = sort;
        _x = x;
        _y = y;
        _width = width;
        _height = height;
    }

    void draw() {
        txSetFillColor(TX_GREEN);
        txRectangle(_x, _y, _x + _width, _y + _height);
    }

    bool click(int x, int y) {
        if (_x < x && _y < y && _x + _width > x && _y + _height > y) _beginthread(stickThread, 0, &_sort);
    }
};

int binaryFind(int sortedArr[], int leftBorderIn, int rightBorderIn, int x);
void ROR(int arr[], int leftBorderIn, int rightBorderIn);
void binarySort(int arr[], int lenght);
void printArr(int arr[]);
void printArr(Branch tree[]);
void printArr(int arr[], int left, int right, int bearing);
void randomFill(int arr[]);
void mswap(int arr[], int left, int right);
void mswap(int arr[], int left, int right, int bearing);
void qwickSort(int arr[], int zero, int lenght);
void buildTree(int arr[], Branch tree[], int lenght);
void huskTree(int arr[], Branch tree[], int* nextArrCell, int currentBranch, int lenght);
void treeSort(int arr[], Branch tree[], int lenght);
void shakerSort(int arr[], int lenght, bool show);

int main () {
    srand(time(NULL));
    Button buttons[BUTTONS_NUMBER] = {*new Button(&shakerSort, BORDER_WIDTH, BORDER_HEIGHT, 100, 100)};
    txCreateWindow(2 * BORDER_WIDTH + ARR_WIDTH, 2 * BORDER_HEIGHT + ARR_HEIGHT);
    for (int i = 0; i < BUTTONS_NUMBER; i++) {
        buttons[i].draw();
    }
    while(true){
        if (txMouseButtons() == 1) {
            for (int i = 0; i < BUTTONS_NUMBER; i++) {
                buttons[i].click(txMouseX(), txMouseY());
            }
        }
    }
    return 0;
}

void treeSort(int arr[], Branch tree[], int lenght) {
    buildTree(arr, tree, lenght);
    int nextArrCell = 0;
    huskTree(arr, tree, &nextArrCell, 0, lenght);
}

void huskTree(int arr[], Branch tree[], int* nextArrCell, int currentBranch, int lenght) {
    if (currentBranch >= lenght || currentBranch < 0) return;
    huskTree(arr, tree, nextArrCell, tree[currentBranch].smallChild, lenght);
    arr[*nextArrCell] = tree[currentBranch].number;
    (*nextArrCell)++;
    huskTree(arr, tree, nextArrCell, tree[currentBranch].bigChild, lenght);
}

void buildTree(int arr[], Branch tree[], int lenght) {
    tree[0] = {arr[0], -1, -1, -1, 1};
    int nextBranchToFill = 1;
    for(int i = 1; i < lenght; i++) {
        int currentBranch = 0;
        while (true) {
            if (tree[currentBranch].number == arr[i]) {
                tree[currentBranch].repeats++;
                break;
            }
            if (tree[currentBranch].number > arr[i]) {
                if (tree[currentBranch].smallChild > 0) {
                    currentBranch = tree[currentBranch].smallChild;
                    continue;
                } else {
                    tree[nextBranchToFill] = {arr[i], currentBranch, -1, -1, 1};
                    tree[currentBranch].smallChild = nextBranchToFill;
                    nextBranchToFill++;
                }
            }
            if (tree[currentBranch].number < arr[i]) {
                if (tree[currentBranch].bigChild > 0) {
                    currentBranch = tree[currentBranch].bigChild;
                    continue;
                } else {
                    tree[nextBranchToFill] = {arr[i], currentBranch, -1, -1, 1};
                    tree[currentBranch].bigChild = nextBranchToFill;
                    nextBranchToFill++;
                }
            }
        }
    }
}

void binarySort(int arr[], int lenght) {
    for(int i = 0; i <= lenght; i++) {
        ROR(arr, binaryFind(arr, 0, i, arr[i]), i);
    }
}

void ROR(int arr[], int leftBorderIn, int rightBorderIn) {
    int fict = arr[rightBorderIn];
    for(int i = rightBorderIn - 1; i >= leftBorderIn; i--) arr[i + 1] = arr[i];
    arr[leftBorderIn] = fict;
}

int binaryFind(int arr[], int leftBorderIn, int rightBorderIn, int x) {
    int right = rightBorderIn, left = leftBorderIn;
    while(right - left > 3) {
        int m = floor((right + left) / 2);
        if(arr[m] > x) right = m;
        else left = m;
    }
    for (int i = left; i < right; i++) if (arr[i] > x) return i;
    return right;
}

void printArr(int arr[]) {
//    for (int i = 0; i < ARR_LENGTH; i++) printf("%d\n", arr[i]);
    for (int i = 0; i < ARR_LENGTH; i++) {
        printf("-");
        for(int j = 0; j < arr[i]; j++) printf(".");
        printf("\n");
    }
    printf("\n");
}

void printArr(Branch tree[]) {
    for (int i = 0; i < ARR_LENGTH; i++) printf("%d %d %d\n", tree[i].number, tree[i].smallChild, tree[i].bigChild);
    printf("\n");
}

void printArr(int arr[], int left, int right, int bearing) {
    txBegin();
    txSetFillColor(RGB(0, 0, 0));
    txClear();
    for(int i = 0; i < ARR_LENGTH; i++) {
        txSetFillColor(RGB(255, 255, 255));
        if (i == left || i == right) txSetFillColor(RGB(255, 0, 0));
        if (i == bearing) txSetFillColor(RGB(0, 255, 0));
        txRectangle(BORDER_WIDTH + i * ARR_WIDTH / ARR_LENGTH, ARR_HEIGHT + BORDER_HEIGHT, BORDER_WIDTH + i * ARR_WIDTH / ARR_LENGTH + ARR_WIDTH / ARR_LENGTH, BORDER_HEIGHT + arr[i] * ARR_HEIGHT / ARR_LENGTH);
    }
    txEnd();
}

void randomFill(int arr[]) {
    for(int i = 0; i < ARR_LENGTH; i++) arr[i] = i + 1;
    for(int i = 0; i < ARR_LENGTH; i++) mswap(arr, i, rand() % ARR_LENGTH);
    //for(int i = 0; i < ARR_LENGTH; i++) arr[i] = rand() % ARR_LENGTH;
}

void qwickSort(int arr[], int leftBorderIn, int rightBorderIn) {
    int left = leftBorderIn, right = rightBorderIn, x = arr[left], xn = left;
    while (right > left) {
        if (arr[right] > x) right--;
        if (arr[left] < x) left++;
        if (arr[right] <= x && arr[left] >= x) {
            mswap(arr, left, right, xn);
            if (arr[left] == arr[right]) right--;
        }
    }
    if (rightBorderIn - leftBorderIn <= 5) return;
    qwickSort(arr, leftBorderIn, left);
    qwickSort(arr, left + 1, rightBorderIn);
}

void shakerSort(int arr[], int lenght, bool show) {
    bool retry = false;
    do {
        retry = false;
        for(int i = 0; i < lenght - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                if (show) mswap(arr, i, i + 1, -1);
                else mswap(arr, i, i + 1);
                retry = true;
            }
        }
        for(int i = lenght; i > 1; i--) {
            if (arr[i] < arr[i - 1]) {
                if (show) mswap(arr, i, i - 1, -1);
                else mswap(arr, i, i - 1);
                retry = true;
            }
        }
    } while(retry);
}

void mswap(int arr[], int left, int right) {
    int fict = arr[left];
    arr[left] = arr[right];
    arr[right] = fict;
}

void mswap(int arr[], int left, int right, int bearing) {
    int fict = arr[left];
    arr[left] = arr[right];
    arr[right] = fict;
    printArr(arr, left, right, bearing);
}
