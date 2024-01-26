#include <sys/sysinfo.h>
#include <stdio.h>
#include <linux/kernel.h>
#include <stdbool.h>
#include "main.h"

void ram_handler(unsigned long ram)
{
    float new_ram = (float)ram;
    unsigned int count = 0;
    char* postfix;
    while (new_ram >= 1000)
    {
        new_ram /= 1000;
        count++;
    }
    switch(count)
    {
        case 0: postfix = "";
                break;
        case 1: postfix = "KB";
                break;
        case 2: postfix = "MB";
                break;
        case 3: postfix = "GB";
                break;
        case 4: postfix = "TB";
                break;
        default: postfix = "ERROR";
    }
    printf("%0.3f %s", new_ram, postfix);
}

void time_handler(long uptime)
{
    unsigned long hours = uptime/3600;
    unsigned short minutes = (uptime%3600)/60;
    unsigned short seconds = (uptime%60);
    printf("%lu:%hu:%hu",hours,minutes,seconds);
}

int main(int argc, char** argv)
{
	struct sysinfo info;
	sysinfo(&info);
	char* buf;
	FILE* f;
    if (argc >= 2)
        f = fopen(argv[1],"r");
    else
        f = fopen("/bin/art.txt","r");
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
                case 'u': time_handler(info.uptime);
                          break;
                case 'p': printf("%hu",info.procs);
                          break;
                case 't': ram_handler(info.totalram);
                          break;
                case 'f': ram_handler(info.freeram);
                          break;
                case 's': ram_handler(info.sharedram);
                          break;
                case 'b': ram_handler(info.bufferram);
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
