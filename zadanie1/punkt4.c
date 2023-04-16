#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczba = 255;
    int gray = 0;
    int gray_tab[8];
    int j = 0;
    while(1)
    {
        gray = liczba ^ (liczba >> 1);
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
        printf("   liczba=%d\n", liczba);
        if(liczba==0)
        {
            liczba = 255;
        }
        liczba -= 1;
        usleep(90000);
    }
    return 0;
}
