#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczba;
    liczba = 256;
    while(1)
    {
        int tmp = liczba;
        if(liczba<1)
        {
            liczba = 256;
        }
        int bin[8];
        for(int i=7; i>=0; i--)
        {
            bin[i] = tmp%2;
            tmp = tmp/2;
        }

        for(int i=0; i<8; i++)
        {
            printf("%d ", bin[i]);
        }
        printf("\n");
        liczba -= 1;
        usleep(10000);
    }
    return 0;
}
