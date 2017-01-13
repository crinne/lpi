#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h> /* setjump and longjmp */

/* array type suitable for holfing the information
    needed to restore a calling environment */
static jmp_buf env;

void
foo(int argc)
{
    if (argc) {
        /* setjmp saves the state */
        switch (setjmp(env)) {
            case 0: /* This is the return after the initial setjmp() */
                printf("Case 0\n");
                break;
            case 1:
                printf("Case 1\n");
                break;
            case 2:
                printf("Case 2\n");
                break;
        }
    }
}

int
main(int argc, char *argv[])
{
    foo(1);
    foo(0);
    longjmp(env, 0);
    exit(EXIT_SUCCESS);
}
