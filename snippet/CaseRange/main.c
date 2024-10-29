#include <stdio.h>


int main()
{
    char ch = 0;

    scanf("%c", &ch);

    switch (ch)
    {
        case '0' ... '9':
            printf("ch from '0' to '9': %c\n", ch);
            break;

        case 'a' ... 'z':
            printf("ch from 'a' to 'z': %c\n", ch);
            break;

        case 'A' ... 'Z':
            printf("ch from 'A' to 'Z': %c\n", ch);
            break;

        default:
            printf("ch in other range: %c\n", ch);
            break;
    }


    return 0;
}
