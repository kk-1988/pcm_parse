#include <stdio.h>
#include <string.h>

int simplest_pcm16le_to_wave(const char *pcmpath,int channels,int sample_rate,const char *wavepath)
{
    typedef struct WAVE_HEADER{
        char fccID[4];
        unsigned int dwSize;
        char fccType[4];
    }WAVE_HEADER;

    typedef struct WAVE_FMT{
        char fccID[4];
        unsigned int dwSize;
        unsigned short wFormatTag;
        unsigned short wChannels;
        unsigned int  dwSamplesPerSec;
        unsigned int  dwAvgBytesPerSec;
        unsigned short wBlockAlign;
        unsigned short uiBitPerSample;
    }WAVE_FMT;

    typedef struct WAVE_DATA{
        char fccID[4];
        unsigned int dwSize;
    }WAVE_DATA;

    if(channels == 0 || sample_rate == 0)
    {
        channels = 0;
        sample_rate = 44100;
    }

    int bits = 16;
    WAVE_HEADER  pcmHEADER;
    WAVE_FMT    pcmFMT;
    WAVE_DATA   pcmDATA;

    unsigned short m_pcmData;
    FILE *fp,*fpout;

    fp = fopen(pcmpath, "rb");
    if(fp == NULL)
    {
        printf("open pcm file error\n");
        return -1;
    }

    fpout=fopen(wavepath,   "wb+");
    if(fpout == NULL) {    
        printf("create wav file error\n");  
        return -1; 
    }     

    //WAVE_HEADER
    memcpy(pcmHEADER.fccID, "RIFF", strlen("RIFF"));
    memcpy(pcmHEADER.fccType, "WAVE", strlen("WAVE"));
    fseek(fpout, sizeof(WAVE_HEADER), 1);

    //WAVE_FMT
    pcmFMT.dwSamplesPerSec = sample_rate;
    pcmFMT.dwAvgBytesPerSec = pcmFMT.dwSamplesPerSec * sizeof(m_pcmData);
    pcmFMT.uiBitPerSample = bits;
    memcpy(pcmFMT.fccID, "fmt ", strlen("fmt "));
    pcmFMT.dwSize = 16;
    pcmFMT.wBlockAlign = 2;
    pcmFMT.wChannels = channels;
    pcmFMT.wFormatTag = 1;

    fwrite(&pcmFMT, sizeof(WAVE_FMT), 1, fpout);

    //WAVE_DATA
    memcpy(pcmDATA.fccID, "data", strlen("data"));
    pcmDATA.dwSize = 0;
    fseek(fpout, sizeof(WAVE_DATA), SEEK_CUR);

    fread(&m_pcmData, sizeof(unsigned short), 1, fp);
    while(!feof(fp))
    {
        pcmDATA.dwSize += 2;
        fwrite(&m_pcmData, sizeof(unsigned short), 1, fpout);
        fread(&m_pcmData, sizeof(unsigned short), 1, fp);
    }

    pcmHEADER.dwSize = 44 + pcmDATA.dwSize;

    rewind(fpout);
    fwrite(&pcmHEADER, sizeof(WAVE_HEADER), 1, fpout);
    fseek(fpout, sizeof(WAVE_FMT), SEEK_CUR);
    fwrite(&pcmDATA, sizeof(WAVE_DATA), 1, fpout);

    fclose(fp);
    fclose(fpout);

    return 0;
}

int main(int argc,char *argv[])
{
    printf("simplest_pcm16le_to_wave parse...\r\n");
    simplest_pcm16le_to_wave("NocturneNo2inEflat_44.1k_s16le.pcm",2,44100,"output_nocturne.wav");
    return 0;
}