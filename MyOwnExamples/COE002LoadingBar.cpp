//COE002LoadingBar - prints a beautiful loading bar

#include <stdio.h>
#include <windows.h>

const int LOADING_BAR_LENGTH = 15;

int main()
{
    while(true)
    {
        for(int i = 0; i < LOADING_BAR_LENGTH; i++)
        {
            for(int j = 0; j < LOADING_BAR_LENGTH; j++)
            {
                if(j > i) printf("-");
                else printf("%\4");
            }

            printf("\r");

            Sleep(100);
        }

        for(int i = 0; i < LOADING_BAR_LENGTH; i++)
        {
            for(int j = 0; j < LOADING_BAR_LENGTH; j++)
            {
                if(j > i) printf("%\4");
                else printf("-");
            }

            printf("\r");

            Sleep(100);
        }
    }

    return 0;
}
