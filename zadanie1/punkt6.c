#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczba = 99;
    while(1)
    {
        if(liczba<0)
        {
            liczba = 99;
        }
        int bcd[8];
        int tmp[2];
        tmp[0] = liczba/10;
        tmp[1] = liczba%10;
        int tmp2 = tmp[0];
        for(int i=3; i>=0; i--)
        {
            bcd[i] = tmp2%2;
            tmp2 = tmp2/2;
        }
        tmp2 = tmp[1];
        for(int i=7; i>=4; i--)
        {
            bcd[i] = tmp2%2;
            tmp2 = tmp2/2;
        }
        printf("liczba = %d  ", liczba);
        for(int i=0; i<8; i++)
        {
            printf("%d", bcd[i]);
        }
        printf("\n");
        liczba -= 1;
        usleep(900000);
    }
    return 0;
}
