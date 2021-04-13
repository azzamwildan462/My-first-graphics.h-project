#include <stdio.h>

int main()
{
    int d, pembagi, hasil = 0;
    scanf("%d", &d);
    if (d == 1)
    {
        printf("1");
        return 0;
    }
    pembagi = d / 2;
    printf("%d\n", d);
    while (1)
    {
        if (pembagi <= 1)
            break;
        if (d % pembagi == 0)
            printf("%d\n", pembagi);
        pembagi--;
    }
    printf("1");

    return 0;
}