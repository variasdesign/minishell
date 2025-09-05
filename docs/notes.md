# Notes

# Allowed functions summary
## Readline library functions
- readline → Reads a line from standard input, shows a prompt, and allows interactive editing. Returns a char * with the input.
  - Returns: char * with the input string.
  - Parameters: (const char *prompt) - The prompt string to display.
- rl_clear_history → Clears the stored command history.
  - Returns: void.
  - Parameters: None.
- rl_on_new_line → Tells readline a new line has started (to refresh the prompt).
  - Returns: void.
  - Parameters: None.
- rl_replace_line → Replaces the current input line with another string.
  - Returns: int (0 on success, -1 on failure).
  - Parameters: (const char *text, int clear_existing) - The string to replace the current line with, and a flag to clear the existing line.
- rl_redisplay → Forces readline to redraw the prompt and the current line.
  - Returns: void.
  - Parameters: None.
- add_history → Adds a line to the command history.
  - Returns: int (0 on success, -1 on failure).
  - Parameters: (const char *line) - The line to add to the history.

## Input/Output
 - printf → Prints formatted text to standard output.
   - Returns: int - The number of characters written, or a negative value if an error occurred.
   - Parameters: (const char *format, ...) - The format string and subsequent arguments.
 - write → Writes raw data to a file descriptor (stdout, stderr, files, pipes…).
   - Returns: ssize_t - The number of bytes written, or -1 if an error occurred.
   - Parameters: (int fd, const void *buf, size_t count) - File descriptor, buffer with data, and number of bytes to write.
 - strerror → Returns the error message string for a given errno.
   - Returns: char * - A pointer to the error message string.
   - Parameters: (int errnum) - The error number.
 - perror → Prints a custom message followed by the errno description.
   - Returns: void.
   - Parameters: (const char *s) - A custom message to print before the system error message.

## Memory management
 - malloc → Allocates dynamic memory.
   - Returns: void * - A pointer to the allocated memory, or NULL if allocation fails.
   - Parameters: (size_t size) - The number of bytes to allocate.
 - free → Frees memory allocated with malloc.
    - Returns: void.
    - Parameters: (void *ptr) - A pointer to the memory block to free.

## Files and directories
 - access → Checks file permissions or existence.
   - Returns: int - 0 if access is permitted, -1 if not.
   - Parameters: (const char *pathname, int mode) - Pathname of the file, and access mode flags.
 - open → Opens a file and returns a file descriptor.
  - Returns: int - A file descriptor, or -1 if an error occurred.
  - Parameters: (const char *pathname, int flags, ...) - Pathname of the file, flags, and optional mode.
 - read → Reads data from a file descriptor.
   - Returns: ssize_t - Number of bytes read, 0 if end of file, -1 if an error occurred.
   - Parameters: (int fd, void *buf, size_t count) - File descriptor, buffer to store data, and maximum number of bytes to read.
 - close → Closes a file descriptor.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (int fd) - The file descriptor to close.
 - unlink → Deletes a file.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (const char *pathname) - The path of the file to delete.
 - stat / lstat / fstat → Retrieve file information (permissions, size, timestamps…).
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (const char *pathname/fd, struct stat *statbuf) - Pathname (for stat/lstat) or file descriptor (for fstat), and a pointer to a stat structure to store the file information.
 - opendir → Opens a directory.
    - Returns: DIR * - A pointer to a DIR structure, or NULL on error.
    - Parameters: (const char *name) - The name of the directory.
 - readdir → Reads entries from a directory.
    - Returns: struct dirent * - A pointer to a structure representing a directory entry, or NULL at the end of the directory or on error.
    - Parameters: (DIR *dirp) - A pointer to a DIR stream.
 - closedir → Closes a directory.
    - Returns: int - 0 on success, -1 on error.
    - Parameters: (DIR *dirp) - A pointer to a DIR stream.

## Processes
 - fork → Creates a new child process.
   - Returns: pid_t - The PID of the child process in the parent, 0 in the child, and -1 on error.
   - Parameters: None.
 - execve → Replaces the current process with a new executable.
   - Returns: This function does not return on success; it replaces the current process image. Returns -1 on error.
   - Parameters: (const char *pathname, char *const argv[], char *const envp[]) - Path to the executable, array of arguments, and array of environment variables.
 - wait / waitpid / wait3 / wait4 → Wait for a child process to finish and retrieve its status.
   - Returns: pid_t - The PID of the terminated child process, or -1 on error.
   - Parameters: Varies slightly, but generally (pid_t pid, int *status, int options) - Process ID to wait for, pointer to store child status, and options.
 - exit → Terminates the current process.
   - Returns: This function does not return.
   - Parameters: (int status) - The exit status of the process.
 - kill → Sends a signal to a process (not only to kill it; can also stop, continue, etc.).
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (pid_t pid, int sig) - Process ID to send the signal to, and the signal number.

## Signals
 - signal → Sets a basic handler for a signal.
   - Returns: __sighandler_t (a pointer to the signal handler function) or SIG_ERR on error.
   - Parameters: (int signum, __sighandler_t handler) - Signal number and the signal handler function.
 - sigaction → More advanced and reliable way to handle signals.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (int signum, const struct sigaction *act, struct sigaction *oldact) - Signal number, pointer to the new action, and pointer to store the old action.
 - sigemptyset → Initializes an empty signal set.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (sigset_t *set) - Pointer to the signal set to initialize.
 - sigaddset → Adds a signal to a signal set.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (sigset_t *set, int signum) - Pointer to the signal set, and the signal number to add.

## File descriptors & pipes
 - dup → Duplicates a file descriptor to the lowest available one.
   - Returns: int - The new file descriptor, or -1 on error.
   - Parameters: (int oldfd) - The existing file descriptor to duplicate.
 - dup2 → Duplicates a file descriptor into a specific one (used in redirections).
   - Returns: int - The new file descriptor on success, or -1 on error.
   - Parameters: (int oldfd, int newfd) - The existing file descriptor, and the desired new file descriptor.
 - pipe → Creates a unidirectional communication channel (pipe) between processes.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (int pipefd[2]) - An array of two integers where the read and write ends of the pipe will be stored.
     
 ## Working directory
 - getcwd → Returns the current working directory path.
   - Returns: char * - A pointer to the current working directory path, or NULL on error.
   - Parameters: (char *buf, size_t size) - Buffer to store the path, and the size of the buffer.
 - chdir → Changes the current working directory.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (const char *path) - The path to the new working directory.

## Terminal & TTY
 - isatty → Checks if a file descriptor refers to a terminal.
   - Returns: int - 1 if fd is an open file descriptor referring to a terminal, 0 otherwise. Returns -1 on error.
   - Parameters: (int fd) - The file descriptor to check.
 - ttyname → Returns the terminal name for a given file descriptor.
   - Returns: char * - The name of the terminal, or NULL on error.
   - Parameters: (int fd) - The file descriptor.
 - ttyslot → Returns the terminal slot number associated with the process.
   - Returns: int - The slot number of the terminal, or 0 if it cannot be determined.
   - Parameters: None.
 - ioctl → Performs low-level control operations on devices (often terminals).
   - Returns: Varies depending on the request. Generally, 0 on success, -1 on error.
   - Parameters: (int fd, unsigned long request, ...) - File descriptor, request code, and optional arguments.
 - tcsetattr → Sets terminal attributes (canonical mode, echo, etc.).
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (int fd, int optional_actions, const struct termios *termios_p) - File descriptor, actions to take, and pointer to termios structure.
 - tcgetattr → Gets terminal attributes.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (int fd, struct termios *termios_p) - File descriptor and pointer to a termios structure to store attributes.

## Termcap functions (terminal control)
Used to move the cursor, clear screen, handle colors, etc.
 - tgetent → Initializes the termcap database for the current terminal.
    - Returns: int - 1 if the database was found and opened, 0 if not found, -1 if an error occurred.
    - Parameters: (char *bp, const char *name) - Buffer for termcap data, and the name of the terminal.
 - tgetflag → Gets a boolean capability of the terminal.
   - Returns: int - The value of the boolean capability (0 or 1), or -1 if not found.
   - Parameters: (char ch) - The first character of the capability name.
 - tgetnum → Gets a numeric capability of the terminal.
   - Returns: int - The numeric value of the capability, or -1 if not found.
   - Parameters: (char ch) - The first character of the capability name.
 - tgetstr → Gets a control sequence string for the terminal.
   - Returns: char * - A pointer to the capability string, or NULL if not found.
   - Parameters: (char ch, char **area) - The first character of the capability name, and a pointer to the buffer area.
 - tgoto → Builds a cursor-movement control sequence.
   - Returns: char * - A pointer to the generated character string.
   - Parameters: (int x, int y) - The column and row to move to.
 - tputs → Outputs a termcap string to the terminal.
   - Returns: int - 0 on success, -1 on error.
   - Parameters: (const char *str, int affcnt, int (*putc)(int)) - The capability string, the number of lines affected, and a function to output characters.
