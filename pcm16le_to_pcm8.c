#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simplest_pcm16le_to_pcm8(char *url)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_8.pcm","wb+");

    int cnt = 0;

    unsigned char *sample = (unsigned char *)malloc(4);

    while(!feof(fp))
    {
        short *samplenum16 = NULL;
        char samplenum8 = 0;
        unsigned char samplenum8_u = 0;
        fread(sample, 1, 4, fp);
        //(-32768-32768)
        samplenum16 = (short *)sample;
        samplenum8 = (*samplenum16)>>8;
        //(0-255)
        samplenum8_u = samplenum8 + 128;
        //L
        fwrite(&samplenum8_u,1,1,fp1);

        samplenum16 = (short *)(sample + 2);
        samplenum8=(*samplenum16)>>8;
		samplenum8_u=samplenum8+128;

        //R
        fwrite(&samplenum8_u,1,1,fp1);
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
    printf("pcm16le convert to pcm8...\r\n");
    simplest_pcm16le_to_pcm8("NocturneNo2inEflat_44.1k_s16le.pcm");
    return 0;
}