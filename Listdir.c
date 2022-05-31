#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <time.h>
void printFileProperties(struct stat stats, char *flag);
void listFiles(const char *path);
void getinfo(char *);
char *pathname[100];
char path[100];

int main(int argc, char *argv[])
{
    struct stat stats;

    if (stat(argv[1], &stats) == 0)
    {
        printFileProperties(stats, argv[2]);
    }
    else
    {
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", path);
    }
    return 0;
}

void printFileProperties(struct stat stats, char *flag)
{
    struct tm dt;
    int qbit = 0, nofilebit = 0;
    int day, mon, year, count = 0;
    printf("Enter data Mon and year\n");
    scanf("%d%d%d", &day, &mon, &year);

    struct dirent *dp;
    DIR *dir = opendir(path);

    if (!dir)
        return;
    while ((dp = readdir(dir)) != NULL)
    {

        if (strcmp(flag, "-c") == 0)
        {
            dt = *(gmtime(&stats.st_ctime));
        }
        else if (strcmp(flag, "-m") == 0)
        {
            dt = *(gmtime(&stats.st_mtime));
        }
        else if (strcmp(flag, "-a") == 0)
        {
            dt = *(gmtime(&stats.st_atime));
        }
        else if (strcmp(flag, "-s") == 0)
        {
            printf("\nFile size: %lld", stats.st_size);
            qbit++;
        }
        else
            dt = *(gmtime(&stats.st_mtime));

        if (qbit == 0)
        {
            if (dt.tm_mday >= day || dt.tm_mon >= mon || dt.tm_year >= year)
            {
                printf("\n Date: - %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900,
                       dt.tm_hour, dt.tm_min, dt.tm_sec);
                printf(" Name = %s \t ", dp->d_name);
                count++;
            }
            else
                nofilebit++;
        }
        stat(dp->d_name, &stats);
    }
    if (nofilebit)
        printf("no other files expect %d\n", count);
    closedir(dir);
}
