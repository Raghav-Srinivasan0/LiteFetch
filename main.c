#include <sys/sysinfo.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <stdbool.h>
#include "main.h"

int main(int argc, char** argv)
{
	struct sysinfo info;
	sysinfo(&info);
	char* buf;
	FILE* f;
    if (argc >= 2)
        f = fopen(argv[1],"r");
    else
        f = fopen("art.txt","r");
    if (f == NULL)
    {
        printf(RED);
        printf("A file error has occurred. Check the path to the artfile");
        printf(RESET);
        return 1;
    }
	int c;
    bool ctrlChar = false;
    while ((c = fgetc(f)) != EOF)
    {
        if (!ctrlChar)
            printf("%c",(char)c);
        else
        {
            switch((char)c)
            {
                case 'u': printf("%ld",info.uptime);
                          break;
                case 'p': printf("%hu",info.procs);
                          break;
                case 't': printf("%lu",info.totalram);
                          break;
                case 'f': printf("%lu",info.freeram);
                          break;
                case 's': printf("%lu",info.sharedram);
                          break;
                case 'b': printf("%lu",info.bufferram);
                          break;
                case 'r': printf(RESET);
                          break;
                case 'k': printf(BLACK);
                          break;
                case 'g': printf(GREEN);
                          break;
                case 'y': printf(YELLOW);
                          break;
                case 'l': printf(BLUE);
                          break;
                case 'm': printf(PURPLE);
                          break;
                case 'n': printf(CYAN);
                          break;
                case 'w': printf(WHITE);
                          break;
                case 'd': printf(RED);
                          break;
                default:
                          printf("~%c",(char)c);
            }
            ctrlChar=false;
        }
        if ((char)c == '~')
        {
            ctrlChar=true;
            printf("%c",(char)8);
        }
    }
    fclose(f);
	return 0;
}
