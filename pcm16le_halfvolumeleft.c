/*
* 左声道音量降低一半
*/
#include <stdio.h>
#include <stdlib.h>

int simplest_pcm16le_halfvolumeleft(char *url)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_halfleft.pcm","wb+");
    int cnt = 0;

    unsigned char *sample = (unsigned char *)malloc(4);

    while(!feof(fp))
    {
        short *samplenum = NULL;
        fread(sample, 1, 4, fp);

        samplenum = (short *)sample;
        *samplenum = *samplenum / 2;
        //L
        fwrite(sample, 1, 2, fp1);
        //R
        fwrite(sample + 2,1,2,fp1);
        cnt++;
    }

    printf("Sample Cnt:%d\n",cnt);

    free(sample);
    fclose(fp);
    fclose(fp1);

    return 0;
}

int main(int argc,char *argv[])
{
    printf("pcm16le half volume left...\r\n");
    simplest_pcm16le_halfvolumeleft("NocturneNo2inEflat_44.1k_s16le.pcm");
    return 0;
}