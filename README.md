# 🐚 my-shell — A POSIX-like UNIX Shell in C

## Overview

**my-shell** is a custom UNIX-like command-line shell implemented in **C**, designed to understand, demonstrate and explore core **Operating Systems concepts** such as process creation, job control, inter-process communication, and signal handling.

The project was built as a **systems-level learning exercise**, focusing on *how a real shell works internally*, rather than just executing commands.

---

## Motivation

Modern shells (bash/zsh) hide a lot of OS complexity. This project aims to:

* Understand **process lifecycle management** using `fork`, `exec`, and `wait`
* Implement **job control** for foreground and background processes
* Explore **pipes and I/O redirection** using file descriptors
* Learn how shells handle **scripts and user interaction**

---

## Features

* Execution of external commands
* Built-in commands (e.g. `cd`, `exit`, `jobs`, `fg`)
* Background process execution using `&`
* Job control and job listing
* Pipelining using `|`
* Input and output redirection
* Script execution support
* Custom shell prompt / UI utilities

---

## Architecture Overview

```text
            ┌──────────────┐
            │   shell.c    │
            │  (main loop) │
            └──────┬───────┘
                   ↓
            ┌──────────────┐
            │   ui.c       │
            │  (prompt)   │
            └──────┬───────┘
                   ↓
            ┌──────────────┐
            │  parser.c   │
            │ (tokenizer) │
            └──────┬───────┘
                   ↓
        ┌─────────────────────┐
        │     exec.c           │
        │ fork / exec / pipes  │
        └──────┬────────┬──────┘
               ↓        ↓
        Built-ins     jobs.c
                       │
                Background jobs
```

---

## Code Structure

| File       | Description                                             |
| ---------- | ------------------------------------------------------- |
| `shell.c`  | Entry point; main REPL loop of the shell                |
| `parser.c` | Tokenizes input, detects pipes and redirections         |
| `exec.c`   | Handles command execution using `fork()` and `execvp()` |
| `jobs.c`   | Manages background jobs and job control                 |
| `script.c` | Executes shell scripts line by line                     |
| `ui.c`     | Handles prompt display and UI-related helpers           |
| `Makefile` | Build automation                                        |

---

## OS Concepts Used

### 🔹 Process Creation

* `fork()` is used to create child processes
* `execvp()` replaces the child process image
* Parent process waits using `wait()` or `waitpid()`

### 🔹 Job Control

* Background processes are tracked in a job table
* Each job is assigned an ID
* `fg` brings background jobs to the foreground

### 🔹 Inter-Process Communication (Pipes)

* `pipe()` creates communication channels
* `dup2()` redirects stdin/stdout between processes
* Multiple commands can be chained using `|`

### 🔹 I/O Redirection

* Input redirection using `<`
* Output redirection using `>`
* File descriptors are managed manually

### 🔹 Script Execution

* Script files are read line-by-line
* Each line is executed as a shell command

---

## Example Usage

```bash
$ ls | grep txt > files.txt
$ sleep 10 &
$ jobs
[1] Running sleep 10
$ fg 1
```

---

## Build & Run

```bash
make
./myshell
```

---

## Limitations

* No command history or line editing
* No tab auto-completion
* Limited POSIX compliance
* Parser does not handle complex quoting or escaping

---

## Future Improvements which I wish to do

* Command history using `readline`
* Tab completion
* Better signal handling (`SIGINT`, `SIGTSTP`)
* Environment variable support
* Improved parser using `lex/yacc`

---

<img width="1919" height="992" alt="Screenshot 2025-12-16 043312" src="https://github.com/user-attachments/assets/0380a712-98fd-4891-82e6-8e228cdf52bd" />


## Author

**DrownedDragon512**
