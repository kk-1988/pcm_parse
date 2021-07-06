#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getADTSframe(unsigned char* buffer, int buf_size, unsigned char* data ,int* data_size)
{
    int size = 0;

    if(!buffer || !data || !data_size )
    {
        return -1;
    }

    while(1)
    {
        if(buf_size < 7)
        {
            return -1;
        }

        //sync words
        if((buffer[0] == 0xff) && (buffer[1] & 0xf0) == 0xf0)
        {
            size |= ((buffer[3] & 0x03 ) << 11);
            size |= buffer[4] << 3;
            size |=((buffer[5] & 0xe0) >> 5);
            break;
        }
        --buf_size;
        ++buffer;
    }

    if(buf_size < size)
    {
        return 1;
    }

    memcpy(data, buffer, size);
    *data_size = size;

    return 0;
}

//aac 解析
void simplest_aac_parse(char *url)
{
    int data_size = 0;
    int size = 0;
    int cnt = 0;
    int offset = 0;

    FILE *myout = stdout;
    
    unsigned char *aacframe = (unsigned char *)malloc(1024*5);
    unsigned char *aacbuffer = (unsigned char *)malloc(1024 * 1024);

    FILE *ifile = fopen(url, "rb+");
    if(!ifile)
    {
        printf("Open file error\r\n");
        return -1;
    }

    printf("-----+- ADTS Frame Table -+------+\n");
	printf(" NUM | Profile | Frequency| Size |\n");
	printf("-----+---------+----------+------+\n");

    while(!forf(ifile))
    {
        data_size = fread(aacbuffer + offset, 1, 1024 * 1024 - offset, ifile);
        unsigned char *input_data = aacbuffer;

        while(1)
        {
            int ret = getADTSframe(input_data, data_size, aacframe, &size);
        }
    }
}

int main(int argc,char *argv[])
{
    printf("simplest_aac_parse...\r\n");
    simplest_aac_parse("nocturne.aac");
}