#include "ui.h"
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>

void print_description() {
    printf(
        "\n"
        "================= ABOUT =================\n"
        "Name        : Anant Joshi (drowneddragon)\n"
        "Background  : Systems programming enthusiast\n"
        "Focus       : C, Operating Systems, Linux\n\n"

        "================ PROJECT =================\n"
        "Project     : Custom Unix Shell (myshell)\n"
        "Language    : C (POSIX compliant)\n"
        "Platform    : Linux / WSL\n\n"

        "================ FEATURES ================\n"
        "✔ Basic command execution (ls, mkdir, rm...)\n"
        "✔ Built-in commands (cd, exit, jobs, fg)\n"
        "✔ Pipes (|)\n"
        "✔ I/O redirection (<, >, >>)\n"
        "✔ Background processes (&)\n"
        "✔ Job control\n"
        "✔ Script execution (.sh files)\n"
        "✔ Custom prompt & ASCII art\n\n"

        "============= CONNECTION =================\n"
        "This project represents my journey into\n"
        "how real shells work internally using\n"
        "fork(), exec(), wait(), pipes, and signals.\n\n"

        "Type 'goat' 🐐 to see the GOAT 😄\n"
        "==========================================\n\n"
    );
}


void print_prompt() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    struct passwd *pw = getpwuid(getuid());
    printf("%s@%s$ ", pw->pw_name, cwd);
    fflush(stdout);
}

void print_startup_banner() {
    printf(
        "[̲̅d̲̅][̲̅r̲̅][̲̅o̲̅][̲̅w̲̅][̲̅n̲̅][̲̅e̲̅][̲̅d̲̅]"
        "[̲̅d̲̅][̲̅r̲̅][̲̅a̲̅][̲̅g̲̅][̲̅o̲̅][̲̅n̲̅]\n\n"
    );
}

void print_goat() {
    printf(
        "⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⡀\n"
        "⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⡇\n"
        "⠀⠀⠀⠀⠀⣀⣤⣾⣿⣟\n"
        "⠀⠀⠀⠀⣾⣿⡿⠿⠿⠿⣿⣦\n"
        "⠀⠀⠀⢸⣿⣿⡇⢠⡄⢀⣿⣿⡄              CR7\n"
        "⠀⠀⠀⣿⡟⣿⣿⣿⠃⣸⣿⣿⣧              Goat\n"
        "⠀⠀⢸⣿⠁⣸⣿⡟⠀⣿⣿⡌⢿⣧\n"
        "⠀⠀⣾⡇⠀⣿⣿⣃⣸⣿⣿⣿⠈⠻⣷⣄⡀\n"
        "⠀⢠⡟⠀⢠⣿⣿⣿⣿⣿⣿⣿⣧⠀⠈⢿⡦\n"
        "⠀⠀⠀⠀⣾⣿⣿⣿⠛⠛⣿⣿⣿⣧\n"
        "⠀⠀⠀⢸⣿⡿⠋⠁⠀⠀⠀⠈⠻⣿⣿⡄\n"
        "⠀⠀⣰⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣧\n"
        "⠀⣼⣿⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣧\n"
        "⣸⡿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢿⣇\n"
    );
}
