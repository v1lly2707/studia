#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>   
#include <grp.h>   

void printDetails(struct dirent *pDirEnt, char *dir_path) 
{
    struct stat file_stat;
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", dir_path, pDirEnt->d_name);

    if(stat(file_path, &file_stat) == -1) 
    {
        fprintf(stderr, "stat() failed on %s: %s\n", file_path, strerror(errno));
        return;
    }

    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    struct passwd *pwd = getpwuid(file_stat.st_uid);
    struct group *grp = getgrgid(file_stat.st_gid);

    if(pwd != NULL) 
    {
        printf(" %s", pwd->pw_name);
    } 
    else 
    {
        printf(" %d", file_stat.st_uid);
    }

    if(grp != NULL) 
    {
        printf(" %s", grp->gr_name);
    } 
    else 
    {
        printf(" %d", file_stat.st_gid);
    }

    printf(" %lu", file_stat.st_nlink);
    printf(" %5ld", file_stat.st_size);

    char time_buf[80];
    struct tm *time_info = localtime(&file_stat.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", time_info);
    printf(" %s", time_buf);

    printf(" %s\n", pDirEnt->d_name);
}

void listDir(char *dir_path, int long_format, int recursive) 
{
    DIR *pDIR;
    struct dirent *pDirEnt;

    pDIR = opendir(dir_path);

    if (pDIR == NULL) 
    {
        fprintf(stderr, "opendir() failed on %s: %s\n", dir_path, strerror(errno));
        exit(-1);
    }

    while ((pDirEnt = readdir(pDIR)) != NULL) 
    {
        if (strcmp(pDirEnt->d_name, ".") == 0 || strcmp(pDirEnt->d_name, "..") == 0)
            continue;

        if (long_format) 
        {
            printDetails(pDirEnt, dir_path);
        } 
        else 
        {
            printf("%s\n", pDirEnt->d_name);
        }

        if(recursive && pDirEnt->d_type == DT_DIR) 
        {
            char new_dir_path[1024];
            snprintf(new_dir_path, sizeof(new_dir_path), "%s/%s", dir_path, pDirEnt->d_name);
            printf("\n%s:\n", new_dir_path);
            listDir(new_dir_path, long_format, recursive);
        }
    }

    closedir(pDIR);
}

int main(int argc, char *argv[]) 
{
    int long_format = 0;
    int recursive = 0;
    char *dir_path = ".";

    for(int i = 1; i < argc; i++) 
    {
        if(strcmp(argv[i], "-l") == 0) 
        {
            long_format = 1;
        } 
        else if(strcmp(argv[i], "-R") == 0) 
        {
            recursive = 1;
        } 
        else 
        {
            dir_path = argv[i];
        }
    }

    listDir(dir_path, long_format, recursive);

    return 0;
}
