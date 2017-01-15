#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>


extern char **environ;
int setenv_1(const char *name, const char *value, int overwrite);
int set_env(char *name);
int unsetenv_1(const char *name);

int
main(int argc, char *argv[])
{
    // Test setenv
    assert(setenv_1("HOME", "home/crinne", 1) == 0);
    assert(setenv_1("HOME", "home/crinne", 0) == -1);
    assert(setenv_1("HOME_NOT_EXISTS", "home/crinne", 0) == 0);
    assert(getenv("HOME_NOT_EXISTS") != NULL );

    // Test unsetenv
    assert(unsetenv_1("ENV NOT EXISTS") == 0);
    assert(unsetenv_1("BAD=INPUT") == -1);
    assert(unsetenv_1("HOME") == 0);
    assert(getenv("HOME") == NULL);

    exit(EXIT_SUCCESS);
}

int
setenv_1(const char *name, const char *value, int overwrite )
{
    unsigned long num = strlen(name) + strlen(value);
    int return_value;

    char *buffer = malloc(num+1);
    assert(buffer != NULL);
    strcpy(buffer, name);
    strcat(buffer, "=");
    strcat(buffer, value);

    if (overwrite) {
        return_value = set_env(buffer);
    } else {
        if (getenv(name) == NULL) {
            return_value = set_env(buffer);
        } else {
            return_value = -1;
        }
    }

    free(buffer);
    return return_value;
}

int
set_env(char *name)
{
    if (putenv(name) == 0) {
        return 0;
    } else {
        return -1;
    }
}

int
unsetenv_1(const char *name)
{
    /* check that no equal sign is added */
    if (strstr(name, "=") != NULL) {
        return -1;
    }

    /* if env is not set at all return 0 */
    char *value = getenv(name);
    if (value == NULL) {
        return 0;
    }

    /* build a buffer in a form of name=value */
    unsigned long num = strlen(name) + strlen(value);

    char *buffer = malloc(num+1);
    assert(buffer != NULL);
    strcpy(buffer, name);
    strcat(buffer, "=");
    strcat(buffer, value);

    /*  Go through environ list and if find environment variable
    then make it equal to NULL*/
    char **ep;

    for (ep = environ; *ep != NULL; ep++) {
        if (strcmp(*ep, buffer) == 0) {
            *ep = NULL;
        }
    }

    free(buffer);

    return 0;
}
