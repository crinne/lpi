**Exercise:** The tee command reads its standard input until end-of-file, writing a copy of the input
to standard output and to the file named in its command-line argument.
Implement tee using I/O system calls. By default, tee overwrites any existing file with
the given name. Implement the –a command-line option (tee –a file), which causes tee
to append text to the end of a file if it already exists.
