#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int simplest_pcm16le_cut_singlechannel(char *url, int start_num, int dur_num)
{
    FILE *fp = fopen(url, "rb+");
    FILE *fp1 = fopen("output_cur.pcm", "wb+");
    FILE *fp_stat = fopen("output_cut.txt","wb+");

    unsigned char *sample = (unsigned char *)malloc(2);

    int cnt = 0;
    while(!feof(fp)){
        fread(sample, 1, 2, fp);
        if(cnt > start_num && cnt <= (start_num + dur_num))
        {
            fwrite(sample,1,2, fp1);

            short samplenum = sample[1];
            samplenum = samplenum * 256;
            samplenum = samplenum + sample[0];

            fprintf(fp_stat, "%6d,", samplenum);
            if(cnt%10 == 0)
                fprintf(fp_stat, "\n", samplenum);
        }    

        cnt++;
    }

    free(sample);
    fclose(fp);
    fclose(fp1);
    fclose(fp_stat);

    return 0;
}

int main(int argc, char *argv[])
{
    printf("simplest_pcm16le_cut_singlechannel...\r\n");
    simplest_pcm16le_cut_singlechannel("drum.pcm", 3000, 120);
    return 0;
}