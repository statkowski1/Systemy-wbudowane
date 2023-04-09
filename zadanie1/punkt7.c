#include <stdio.h>
#include <stdlib.h>

int main()
{
    int waz[8] = {0, 0, 0, 0, 0, 1, 1, 1};
    for(int i=0; i<8; i++)
    {
        printf("%d", waz[i]);
    }
    printf("\n");
    usleep(900000);
    while(1)
    {
        for(int i=7; i>2; i--)
        {
            waz[i] = 0;
            waz[i-3] = 1;
            for(int j=0; j<8; j++)
            {
                printf("%d", waz[j]);
            }
            printf("\n");
            usleep(900000);
        }
        for(int i=0; i<5; i++)
        {
            waz[i] = 0;
            waz[i+3] = 1;
            for(int j=0; j<8; j++)
            {
                printf("%d", waz[j]);
            }
            printf("\n");
            usleep(900000);
        }
    }
    return 0;
}
