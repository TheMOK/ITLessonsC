#include "TXLib.h"

struct Cell;

const int VIEW_SIDE = 500, BORDER = 50, FIELD_SIDE = 100;

void addHole(int, int, Cell[FIELD_SIDE][FIELD_SIDE]);
void connect(int, int, int, int, Cell[FIELD_SIDE][FIELD_SIDE]);
Cell findTreeVertex(int, int, Cell[FIELD_SIDE][FIELD_SIDE]);
bool isConnected(int, int, int, int, Cell[FIELD_SIDE][FIELD_SIDE]);

struct Cell {
    int parentX = -1, parentY = -1;
};

int main()
    {
    srand(time(NULL));
    txCreateWindow (2 * BORDER + VIEW_SIDE, 2 * BORDER + VIEW_SIDE);

    struct Cell field[FIELD_SIDE][FIELD_SIDE];

    field[0][0].parentX = 0;
    field[0][0].parentY = 0;
    for(int x = 1; x < FIELD_SIDE; x++) {
        field[x][0].parentX = x - 1;
        field[x][0].parentY = 0;
    }

    field[0][FIELD_SIDE - 1].parentX = 0;
    field[0][FIELD_SIDE - 1].parentY = FIELD_SIDE - 1;
    for(int x = 1; x < FIELD_SIDE; x++) {
        field[x][FIELD_SIDE - 1].parentX = x - 1;
        field[x][FIELD_SIDE - 1].parentY = FIELD_SIDE - 1;
    }

    while(true){     //printf("DRAW %d %d %d\n", x, y, field[x][y].parentX);//
    for(int x = 0; x < FIELD_SIDE; x++)
    for(int y = 0; y < FIELD_SIDE; y++) if(field[x][y].parentX != -1) txCircle(x  * VIEW_SIDE / FIELD_SIDE + BORDER, y  * VIEW_SIDE / FIELD_SIDE + BORDER, VIEW_SIDE / FIELD_SIDE / 2);
    //txLine(field[x][y].parentX * VIEW_SIDE / FIELD_SIDE + BORDER, field[x][y].parentY * VIEW_SIDE / FIELD_SIDE + BORDER, x * VIEW_SIDE / FIELD_SIDE + BORDER, y * VIEW_SIDE / FIELD_SIDE + BORDER);
    if(isConnected(0, 0, 0, FIELD_SIDE - 1, field)) break;
    int randX = 0, randY = 0;
    do{
        randX = rand() % FIELD_SIDE;
        randY = rand() % FIELD_SIDE;
    }while(field[randX][randY].parentX != -1);
    addHole(randX, randY, field);
    }
    return 0;
    }

void addHole(int x, int y, Cell field[FIELD_SIDE][FIELD_SIDE]) {
    field[x][y].parentX = x;
    field[x][y].parentY = y;
    if(y - 1 >= 0 && field[x][y - 1].parentX != -1) connect(x, y, x, y - 1, field);
    if(x - 1 >= 0 && field[x - 1][y].parentX != -1) connect(x, y, x - 1, y, field);
    if(x + 1 < FIELD_SIDE && field[x + 1][y].parentX != -1) connect(x, y, x + 1, y, field);
    if(y + 1 < FIELD_SIDE && field[x][y + 1].parentX != -1) connect(x, y, x, y + 1, field);
}

bool isConnected(int smallX, int smallY, int bigX, int bigY, Cell field[FIELD_SIDE][FIELD_SIDE]){
    struct Cell smallParent = findTreeVertex(smallX, smallY, field), bigParent = findTreeVertex(bigX, bigY, field);
    return smallParent.parentX == bigParent.parentX && smallParent.parentY == bigParent.parentY;
}

void connect(int smallX, int smallY, int bigX, int bigY, Cell field[FIELD_SIDE][FIELD_SIDE]){
    struct Cell smallParent = findTreeVertex(smallX, smallY, field), bigParent = findTreeVertex(bigX, bigY, field);
    field[smallParent.parentX][smallParent.parentY].parentX = bigParent.parentX;
    field[smallParent.parentX][smallParent.parentY].parentY = bigParent.parentY;
//    field[smallX][smallY].parentX = bigX;
//    field[smallX][smallY].parentY = bigY;
}

Cell findTreeVertex(int x, int y, Cell field[FIELD_SIDE][FIELD_SIDE]) {
    while(field[x][y].parentX != x || field[x][y].parentY != y){
        int bufferX = x;
        x = field[x][y].parentX;
        y = field[bufferX][y].parentY;
    }
    struct Cell result;
    result.parentX = x;
    result.parentY = y;
    return result;
}
//
//void findTreeHeightFromVertex(int x, int y, Cell field[][]) {
//    int leftTreeHeight = findTree
//    return ;
//}

