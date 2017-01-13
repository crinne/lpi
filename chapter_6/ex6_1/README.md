**Exercise**

Compile the program in main.c, and list its size using ls –l. Although the program contains an array (mbuf) that is around 10 MB in size, the executable file is much smaller than this. Why is this?

**Answer**
array mbuf is uninitalized, it will be filled with "0" on runtime.
