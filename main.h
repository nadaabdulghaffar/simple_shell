#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#define BUFF_SIZE 1024

extern char **environ;

char **tokenize(char *command, ssize_t num_charin);
int execute_command(char **argv);
void print_env(void);
int is_emtyln(char *Buffer);
void free_argv(char **argv);
void free_buffer(char *Buffer);
void comments_handle(char *Buffer);
void Exit_check(char *Buffer, ssize_t buffer_size, char **argv);
char *search_path(char *command);
char **_split(char *str, char *sep);
char *_getenv(char *env_var);
unsigned int delim_check(char c, const char *str);
char *_strtok(char *str, const char *delim);
#endif
