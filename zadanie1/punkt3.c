#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczba = 0;
    int gray = 0;
    int gray_tab[8];
    int j = 0;
    while(1)
    {
        if(liczba==255)
        {
            liczba = 0;
        }
        for(int i = 7; i >= 0; i--)
        {
            gray_tab[j] = (gray >> i) & 1;
            j += 1;
        }
        j = 0;
        for(int i=0; i<8; i++)
        {
            printf("%d", gray_tab[i]);
        }
        printf("\n");
        liczba += 1;
        gray = liczba ^ (liczba >> 1);
        usleep(900000);
    }
    return 0;
}
