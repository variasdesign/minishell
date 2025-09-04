# Notes

# Allowed functions summary
## Readline library functions
- readline → Reads a line from standard input, shows a prompt, and allows interactive editing. Returns a char * with the input.
- rl_clear_history → Clears the stored command history.
- rl_on_new_line → Tells readline a new line has started (to refresh the prompt).
- rl_replace_line → Replaces the current input line with another string.
- rl_redisplay → Forces readline to redraw the prompt and the current line.
- add_history → Adds a line to the command history.

## Input/Output
 - printf → Prints formatted text to standard output.
 - write → Writes raw data to a file descriptor (stdout, stderr, files, pipes…).
 - strerror → Returns the error message string for a given errno.
 - perror → Prints a custom message followed by the errno description.

## Memory management
 - malloc → Allocates dynamic memory.
 - free → Frees memory allocated with malloc.

## Files and directories
 - access → Checks file permissions or existence.
 - open → Opens a file and returns a file descriptor.
 - read → Reads data from a file descriptor.
 - close → Closes a file descriptor.
 - unlink → Deletes a file.
 - stat / lstat / fstat → Retrieve file information (permissions, size, timestamps…).
 - opendir → Opens a directory.
 - readdir → Reads entries from a directory.
 - closedir → Closes a directory.

## Processes
 - fork → Creates a new child process.
 - execve → Replaces the current process with a new executable.
 - wait / waitpid / wait3 / wait4 → Wait for a child process to finish and retrieve its status.
 - exit → Terminates the current process.
 - kill → Sends a signal to a process (not only to kill it; can also stop, continue, etc.).

## Signals
 - signal → Sets a basic handler for a signal.
 - sigaction → More advanced and reliable way to handle signals.
 - sigemptyset → Initializes an empty signal set.
 - sigaddset → Adds a signal to a signal set.

## File descriptors & pipes
 - dup → Duplicates a file descriptor to the lowest available one.
 - dup2 → Duplicates a file descriptor into a specific one (used in redirections).
 - pipe → Creates a unidirectional communication channel (pipe) between processes.

 ## Working directory
 - getcwd → Returns the current working directory path.
 - chdir → Changes the current working directory.

## Terminal & TTY
 - isatty → Checks if a file descriptor refers to a terminal.
 - ttyname → Returns the terminal name for a given file descriptor.
 - ttyslot → Returns the terminal slot number associated with the process.
 - ioctl → Performs low-level control operations on devices (often terminals).
 - tcsetattr → Sets terminal attributes (canonical mode, echo, etc.).
 - tcgetattr → Gets terminal attributes.

## Termcap functions (terminal control)
Used to move the cursor, clear screen, handle colors, etc.
 - tgetent → Initializes the termcap database for the current terminal.
 - tgetflag → Gets a boolean capability of the terminal.
 - tgetnum → Gets a numeric capability of the terminal.
 - tgetstr → Gets a control sequence string for the terminal.
 - tgoto → Builds a cursor-movement control sequence.
 - tputs → Outputs a termcap string to the terminal.
