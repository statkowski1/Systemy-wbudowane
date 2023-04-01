#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczba;
    liczba = 0;
    while(1)
    {
        int tmp = liczba;
        if(liczba>255)
        {
            liczba = 0;
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
        liczba += 1;
        usleep(900000);
    }
    return 0;
}
