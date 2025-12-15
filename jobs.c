#include "jobs.h"
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

static Job jobs[MAX_JOBS];
static int job_count = 0;
static int next_job_id = 1;

static void update_jobs() {
    int status;
    for (int i = 0; i < job_count; i++) {
        if (jobs[i].running) {
            if (waitpid(jobs[i].pid, &status, WNOHANG) > 0)
                jobs[i].running = 0;
        }
    }
}

void reap_background_processes() {
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0);
}

void add_job(pid_t pid, const char *cmd) {
    if (job_count >= MAX_JOBS) return;

    jobs[job_count].id = next_job_id++;
    jobs[job_count].pid = pid;
    strncpy(jobs[job_count].cmd, cmd, 255);
    jobs[job_count].cmd[255] = '\0';
    jobs[job_count].running = 1;
    job_count++;
}

void list_jobs() {
    update_jobs();
    for (int i = 0; i < job_count; i++) {
        printf("[%d] %s %s\n",
               jobs[i].id,
               jobs[i].running ? "Running" : "Done",
               jobs[i].cmd);
    }
}

Job* find_job(int id) {
    for (int i = 0; i < job_count; i++)
        if (jobs[i].id == id)
            return &jobs[i];
    return NULL;
}
