#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define PATH_MAXLEN 128
char homePath[PATH_MAXLEN];
char workPath[PATH_MAXLEN];

void deleteFilesInDirectory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // 디렉토리 열기
    dir = opendir(path);
    if (dir == NULL) {
        fprintf(stderr, "opendir error for %s\n", path);
        exit(1);
    }

    // 디렉토리 내의 파일 순회
    while ((entry = readdir(dir)) != NULL) {
        // 현재 디렉토리(.)나 상위 디렉토리(..)는 무시
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, "init.txt")) {
            continue;
        }

        // 파일 경로 생성
        char filePath[1024];
        strcpy(filePath, path);
        strcat(filePath, "/");
        strcat(filePath, entry->d_name);

        // 파일 삭제
        if (remove(filePath) != 0) {
            fprintf(stderr, "remove error for %s\n", filePath);
        } else {
            // printf("Deleted: %s\n", filePath);
        }
    }

    closedir(dir);
}

char *GetHomePath(void) { return homePath; }
char *GetWorkPath(void) { return workPath; }

int main(void) {
    sprintf(homePath, "%s", getenv("HOME"));
    sprintf(workPath, "%s/semteul_project", GetHomePath());

    char resultPath[PATH_MAXLEN];
    char codePath[PATH_MAXLEN];

    sprintf(resultPath, "%s/result", GetWorkPath());
    sprintf(codePath, "%s/compile/code", GetWorkPath());

    deleteFilesInDirectory(resultPath);
    deleteFilesInDirectory(codePath);
}