//CHT007Horspool - finds a word in other word

#include <stdio.h>
#include <txlib.h>

const int MOVE_ARRAY_SIZE = 256;

int horspoolSearch(const char[], const char[]);
void fillMoveArray(int[], const char[], const int);

int main()
    {

    printf("%d", horspoolSearch("memeow", "meow"));

    return 0;

    }

int horspoolSearch(const char source[], const char word[])
    {

    int wordLen = strlen(word), sourceLen = strlen(source);
    int moveArray[MOVE_ARRAY_SIZE] = {-1};

    fillMoveArray(moveArray, word, wordLen);

    int i = 0;
    while(true)
        {

        for(int j = 0; ; j++)
            {

            if(word[j] == 0) return i;
            if(i > sourceLen - wordLen) return -1;

            if(source[i + j] != word[j])
                {

                if(j > moveArray[source[j + i]]) i += j - moveArray[source[j + i]];
                else i++;
                break;

                }

            }

        }

    }

void fillMoveArray(int moveArray[], const char word[], const int wordLen)
    {

    for(int i = 0; i < wordLen; i++)
        {

        moveArray[word[i]] = i;

        }

    }
