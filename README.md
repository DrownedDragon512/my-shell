# 🐚 Custom POSIX Linux Shell (myshell)

A lightweight, POSIX-compatible Linux shell implemented in **C**, designed to demonstrate core operating system concepts such as process creation, job control, inter-process communication, and file descriptor management.

---

## ✨ Features

- **Basic Command Execution**
  - Run standard Linux commands (`ls`, `pwd`, `mkdir`, `cat`, etc.)

- **Built-in Commands**
  - `cd` – change directory
  - `exit` – exit the shell
  - `jobs` – list background jobs
  - `fg <job_id>` – bring a background job to foreground
  - `goat` – displays custom ASCII art
  - `description` – prints project description

- **Piping**
  - Supports pipelines using `|`
  ```bash
  ls | wc -l
  ps aux | grep root | wc -l
