#include <stdio.h>
#include <stdlib.h>

int main()
{
    while(1)
    {
        int kolejka[8] = {0, 0, 0, 0, 0, 0, 0, 1};
        int i = 7;
        while(1)
        {
            usleep(900000);
            for(int i=0; i<8; i++)
            {
                printf("%d", kolejka[i]);
            }
            printf("\n");
            if(kolejka[6]==1&&kolejka[7]==1)
            {
                break;
            }
            if(i-1>0 || kolejka[i-1]==0)
            {
                kolejka[i] = 0;
                kolejka[i-1] = 1;
                i -= 1;
            }
            if(i-1<0 || kolejka[i-1]==1)
            {
                i = 7;
                usleep(900000);
                for(int i=0; i<8; i++)
                {
                    printf("%d", kolejka[i]);
                }
                printf("\n");
                kolejka[7] = 1;
            }
        }
    }
    return 0;
}
