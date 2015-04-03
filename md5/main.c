#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#define BUF_SZ  2048

void usage(void)
{
    printf("The md5 value generation/comparision tool.\n");
    printf("md5 -g filename : to generate md5 file.\n");
    printf("md5 -c filename : to compare md5 value.\n");

    return;
}

static MD5_CTX md5_ctx;
static unsigned char md5[16];

int main(int argc, char** argv)
{
    FILE* fp;
    char* fn;
    int generate = -1;

    MD5Init(&md5_ctx);

    if (argc != 3)
    {
        usage();
        return -1;
    }

    /* parse argument */
    if (strcmp(argv[1], "-g") == 0) generate = 1;
    if (strcmp(argv[1], "-c") == 0) generate = 0;

    if (generate == -1)
    {
        usage();
        return -1;
    }

    fp = fopen(argv[2], "rb");
    if (fp)
    {
        uint8_t *buf_ptr;
        
        buf_ptr = (uint8_t*)malloc(BUF_SZ);
        if (buf_ptr)
        {
            int length;
            
            while (!feof(fp))
            {
                length = fread(buf_ptr, 1, BUF_SZ, fp);
                MD5Update(&md5_ctx, buf_ptr, length);
            }
            
            MD5Final(md5, &md5_ctx);
            free(buf_ptr);
        }

        fclose(fp);

        /* get the md5 file name */
        fn = (char*) malloc(strlen(argv[2] + 16));
        if (!fn)
        {
            printf("no memory!\n");
            return -1;
        }

        {
            char *ptr;

            strcpy(fn, argv[2]);
            ptr = strchr(fn, '.');
            if (ptr)
            {
                ptr ++;
            }
            else
            {
                /* no ext name */
                ptr = &fn[strlen(fn)];
                *ptr++ = '.';
            }

            /* with .md5 ext name */
            *ptr++ = 'm';
            *ptr++ = 'd';
            *ptr++ = '5';
            *ptr = '\0';
        }

        if (generate == 1)
        {
            /* generate md5 file */
            fp = fopen(fn, "wb+");
            free(fn); /* release filename memory */

            if (fp)
            {
                fwrite(md5, 1, sizeof(md5), fp);
                fclose(fp);
                
                return 0;
            }
        }
        else if (generate == 0)
        {
            unsigned char md5_temp[16];

            /* compare md5 file */
            fp = fopen(fn, "rb");
            free(fn); /* release filename memory */

            if (fp)
            {
                fread(md5_temp, 1, sizeof(md5_temp), fp);
                fclose(fp);
            }

            if (memcmp(md5, md5_temp, sizeof(md5)) == 0)
            {
                printf("md5 value is the same!\n");
                return 0;
            }
            else
            {
                printf("md5 value is different!\n");
                return -1;
            }
        }
    }
    else
    {
        printf("%s open failed!\n", argv[2]);
    }

    return -1;
}
