//CHT007Horspool - finds a word in other word

#include <stdio.h>
#include <txlib.h>

const int MOVE_ARRAY_SIZE = 256, CHECK_SOURCE_LENGTH = 20, CHECK_WORD_LENGTH = 4, CHECK_ITERATIONS_NUMBER = 1000;

int BMHSearch(char[], char[]);
int KMPSearch(char[], char[]);
void fillMoveArray(int[], const char[], const int);
void fillWithRandomText(char[], int);
int naiveSearch(char[], char[]);
int checkWord(char[], char[], int);
bool checkStringFinder(int(*)(char[], char[]), int(*)(char[], char[]));

int main()
    {
    srand(time(NULL));

    checkStringFinder(&naiveSearch, &KMPSearch);
//    printf("\n%d", KMPSearch("mmeow", "meow"));

    return 0;
    }

bool checkStringFinder(int(*idealSearch)(char[], char[]), int(*paramSearch)(char[], char[]))
    {
    char source[CHECK_SOURCE_LENGTH] = {0}, word[CHECK_WORD_LENGTH] = {0};

    for(int i = 0; i < CHECK_ITERATIONS_NUMBER; i++)
        {
        fillWithRandomText(source, CHECK_SOURCE_LENGTH);
        fillWithRandomText(word, CHECK_WORD_LENGTH);

        printf("%s %s\r", source, word);

        if(paramSearch(source, word) != idealSearch(source, word))
            {
            printf("\n\nTOTAL FAILURE");
            return false;
            }
        }

    printf("\n\nTOTAL SUCCESS");
    return true;
    }

int BMHSearch(char source[], char word[])
    {
    int wordLen = strlen(word), sourceLen = strlen(source);
    int moveArray[MOVE_ARRAY_SIZE] = {0};

    fillMoveArray(moveArray, word, wordLen);

    for(int i = 0; i <= sourceLen - wordLen;)
        {
        for(int j = 0; ; j++)
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

int KMPSearch(char source[], char word[])
    {
    int sourceLen = strlen(source), wordLen = strlen(word);
    for(int i = 0; i <= sourceLen; ) {
        int checkWordResult = checkWord(source, word, i);
        //printf("%d %d\n", checkWordResult, i);
        if(checkWordResult == -1) return i;
        else
            {
            if(checkWordResult > 0) i += checkWordResult;
            else i++;
            }
    }

    return -1;
    }

void fillMoveArray(int moveArray[], const char word[], const int wordLen)
    {
    for(int i = 0; i < MOVE_ARRAY_SIZE; i++) moveArray[i] = wordLen;

    for(int i = 0; i < wordLen - 1; i++) moveArray[word[i]] = wordLen - i - 1;
    }

int checkWord(char source[], char word[], int startOffset)
    {
    for(int i = 0; word[i] != 0; i++) if(word[i] != source[i + startOffset]) return i;

    return -1;
    }

int naiveSearch(char source[], char word[])
    {
    int sourceLen = strlen(source), wordLen = strlen(word);
    for(int i = 0; i <= sourceLen - wordLen; i++) if(checkWord(source, word, i) == -1) return i;

    return -1;
    }

void fillWithRandomText(char c[], int l)
    {
    for(int i = 0; i < l; i++) c[i] = rand() % 3 + 65;

    c[l - 1] = 0;
    }
