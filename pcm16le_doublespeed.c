#include <stdio.h>
#include <stdlib.h>

int simplest_pcm16le_doublespeed(char *url)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_doublespeed.pcm", "wb+");

    int cnt = 0;

    unsigned char *sample = (unsigned char *)malloc(4);

    while(!feof(fp))
    {
        fread(sample, 1, 4, fp);

        if(cnt % 2 != 0)
        {
            //L
            fwrite(sample, 1, 2, fp1);
            //R
            fwrite(sample + 2, 1, 2, fp1);
        }

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
    printf("pcm16le doublespeed parse...\r\n");
    simplest_pcm16le_doublespeed("NocturneNo2inEflat_44.1k_s16le.pcm");
    return 0;
}