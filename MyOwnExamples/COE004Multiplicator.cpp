//COE004Summator -  given numbers

#include <stdio.h>

int main()
{
    int sum = 0, counter = 0, input = 0;

    while(scanf("%d", &input) == 1)
    {
        sum += input;
        counter++;
    }

    if(counter != 0) printf("%d", sum / counter);

    return 0;
}


