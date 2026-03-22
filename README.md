_This project has been created as part of the 42 curriculum by sjolliet_

# Pipex - 42 Common Core

## Description

**pipex** is a project that recreates the behavior of Unix pipes in C.

The program executes shell-like commands by using system calls such as `fork`, `pipe`, `dup2`, and `execve` to redirect input and output between multiple processes.

It mimics the following shell command:

```bash
< infile cmd1 | cmd2 > outfile
```
Which means:

- The input is read from a file
- The first command is executed
- Its output is passed through a pipe
- The second command is executed
- The final result is written into an output file

The program handles:

- File descriptor management
- Process creation and synchronization
- Command execution using environment paths

If an error occurs, the program exits with an appropriate error message.

### Bonus
The bonus part extends the program with:

1. Support for multiple commands:

    ```bash
    < infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
    ```

2. Implementation of here_doc, which behaves like:

    ```bash
    << LIMITER cmd1 | cmd2 >> outfile
    ```
    In this mode:

    - The program reads from standard input until the limiter is reached
    - The output is appended to the file instead of overwriting it

## Instructions

### Compilation
Clone the repository and compile the project using make:

```bash
git clone <repository_url>
cd <project_name>
make
```

To compile the bonus part:

```bash
make bonus
```

### Usage

**Mandatory**

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Example: 

```bash
./pipex infile "grep hello" "wc -l" outfile
```

Equivalent shell command:

```bash
< infile grep hello | wc -l > outfile
```

**Bonus**

1. Muliple commands:

    ```bash
    ./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
    ```

2. Here_doc:

    ```bash
    ./pipex here_doc LIMITER "cmd1" "cmd2" outfile
    ```

    Example:

    ```bash
    ./pipex here_doc EOF "cat" "wc -l" outfile
    ```

**Handling quoted arguments**

Arguments enclosed in single quotes are treated as a single argument, even if they contain spaces.

Escaped single quotes inside quoted arguments are also supported.

For example:

```bash
./pipex infile "grep 'error: invalid user\'s input'" "wc -l" outfile
```

Will be interpreted internally as:

```bash
< infile grep "error: invalid user's input" | wc -l > outfile
```

Note that only single quotes are supported (double quotes are not handled).

The behavior may differ slightly from a real shell in edge cases.

## Resources

- https://medium.com/@abkabex/pipex-42-009811947a59
- https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/
- https://en.wikipedia.org/wiki/Here_document
- https://www.youtube.com/@CodeVault

AI tools were used as learning and productivity aids for :

- Understanding system calls (pipe, fork, dup2, execve)
- Debugging file descriptor and process management issues
- Fixing Makefile issues
- Answering conceptual questions about pipes and here_doc
- Improving the structure and formatting of this README
