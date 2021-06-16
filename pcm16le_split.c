#include <stdio.h>
#include <stdlib.h>

int simplest_pcm16le_split(char *url)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_1.pcm", "wb+");
    FILE *fp2 = fopen("output_r.pcm", "wb+");
    unsigned char *sample = (unsigned char *)malloc(4);

    while(!feof(fp))
    {
        fread(sample, 1, 4, fp);
        //L
        fwrite(sample,1,2,fp1);
        //W
        fwrite(sample+2,1,2,fp2);
    }

    free(sample);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);

    return 0;
}

int main(int argc,char *argv[])
{
    printf("pcm16le split...\r\n");
    simplest_pcm16le_split("NocturneNo2inEflat_44.1k_s16le.pcm");
    return 0;
}