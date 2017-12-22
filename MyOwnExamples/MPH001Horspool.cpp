//CHT007Horspool - finds a word in other word

#include <stdio.h>
#include <txlib.h>

const int MOVE_ARRAY_SIZE = 256;

int horspoolSearch(const char[], const char[]);
void fillMoveArray(int[], const char[], const int);

bool checkWord(char source[], char word[], int startOffset, int wordLen) {
    for(int i = 0; i < wordLen; i++) if(word[i] != source[i + startOffset]) return false;
    return true;
}

int findWordNaive(char source[], char word[]) {
    int sourceLen = strlen(source), wordLen = strlen(word);
    for(int i = 0; i <= sourceLen - wordLen; i++) if(checkWord(source, word, i, wordLen)) return i;
    return -1;
}

void fillWithRandomText(char c[], int l) {
    for(int i = 0; i < l; i++) c[i] = rand() % 3 + 65;
    c[l - 1] = 0;
}

int main()
    {
    srand(time(NULL));
    const int sl = 20, wl = 4;
    char s[sl] = {0}, w[wl] = {0};

    for(int i = 0; i < 10000; i++){
    fillWithRandomText(s, sl);
    fillWithRandomText(w, wl);

    int f = horspoolSearch(s, w), f2 = findWordNaive(s, w);

    if(f2 != f) printf("%d %s %s\r", i, s, w);
    else printf("%4d %s %s %2d %2d\r", i, s, w, f, f2);
    //Sleep(300);
    }
    printf("\n\nTOTAL SUCCESS", s, w);
    return 0;

    }

int horspoolSearch(const char source[], const char word[])
    {

    int wordLen = strlen(word), sourceLen = strlen(source);
    int moveArray[MOVE_ARRAY_SIZE] = {0};

    fillMoveArray(moveArray, word, wordLen);

    for(int i = 0; i <= sourceLen - wordLen;)
        {
        for(int j = 0;; j++)
            {
            if(j >= wordLen) return i;
            if(source[i + j] != word[j])
                {
                i += moveArray[source[i + wordLen - 1]];
                break;
                }
            }
        }

        return -1;
    }

void printArr(int a[], int l)
    {
    for(int i = 0; i < l; i++) printf("%d ", a[i]);
    printf("\n");
    }

void fillMoveArray(int moveArray[], const char word[], const int wordLen)
    {

    for(int i = 0; i < MOVE_ARRAY_SIZE; i++) moveArray[i] = wordLen;

    for(int i = 0; i < wordLen - 1; i++) moveArray[word[i]] = wordLen - i - 1;

    }
