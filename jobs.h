#ifndef JOBS_H
#define JOBS_H

#include <sys/types.h>

#define MAX_JOBS 50

typedef struct {
  int id;
  pid_t pid;
  char cmd[256];
  int running;
} Job;

void add_job(pid_t pid, const char* cmd);
void list_jobs();
Job* find_job(int id);
void reap_background_processes();

#endif
