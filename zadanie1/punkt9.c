#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    int lfsr = 0b1110011;
    while(1)
    {
        int lfsr_tab[8] = {0, 0, 0, 0, 0, 0, 0, 0};
        int bit = ((lfsr >> 0) ^ (lfsr >> 3) ^ (lfsr >> 4) ^ (lfsr >> 6)) & 1;
        lfsr = (lfsr >> 1) | (bit << 5);
        int tmp_bin = lfsr;
        for(int i=7; i>=2; i--)
        {
            lfsr_tab[i] = tmp_bin%2;
            tmp_bin = tmp_bin/2;
        }
        printf("%d\n", lfsr);
        for(int i=0; i<8; i++)
        {
            printf("%d", lfsr_tab[i]);
        }
        printf("\n");
        usleep(900000);
    }
    return 0;
}
