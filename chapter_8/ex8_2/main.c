#include <stdio.h>
#include <stdlib.h>
#include <pwd.h> //getpwnam, getpwuid
#include <string.h>


struct passwd
*_getpwnam(char *name) 
{
  struct passwd *pwd;
  while ((pwd = getpwent()) != NULL) {
    if ((strcmp(pwd->pw_name, name)) == 0) {	  
	break;       
      }
  }
  endpwent();
  return pwd;
}

int
main(int argc, char *argv[])
{
  
  struct passwd *pwd;

  pwd = _getpwnam("caspar");
  if (pwd == NULL) {
    printf("No name found\n");
    exit(EXIT_FAILURE);
  }
 
  printf("name: %9s \nwith id: %d\n",
	 pwd->pw_name,
	 pwd->pw_uid);

  
  exit(EXIT_SUCCESS);
}



