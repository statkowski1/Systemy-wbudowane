#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczba = 0;
    int gray = 0;
    while(1)
    {
        for(int i = 7; i >= 0; i--)
        {
            printf("%d", (gray >> i) & 1);
        }
        printf("\n");
        if(liczba == 255)
        {
            break;
        }
        liczba++;
        gray = liczba ^ (liczba >> 1);
        usleep(900000);
    }
    return 0;
}
