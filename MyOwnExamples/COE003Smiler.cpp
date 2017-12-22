//COE003Smiler - prints smiles

#include <stdio.h>

const int LOADING_BAR_LENGTH = 10;

int main()
{
    printf("%\0\n");
    printf("%\1\n");
    printf("%\2\n");
    printf("%\3\n");
    printf("%\4\n");
    printf("%\5\n");
    printf("%\6\n");
    printf("%05c\n", 'x');

    return 0;
}
