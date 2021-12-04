Name: Rodrigo Onate Garcia
CPSC 351
California State University, Fullerton

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  pid_t  pid;
	/* fork another process */
	pid = fork();
	if (pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		exit(-1);
	}
	else if (pid == 0) { /* child process */
    pid_t pid2;
    pid2 = fork();

    if(pid2 < 0){
      fprintf(stderr, "Fork Failed");
  		exit(-1);
    }
    else if(pid2 == 0){ /* Grandchild process*/

     execlp("/bin/firefox", "firefox", NULL); // opens Mozilla
     // once Mozilla is closed the Grandchild will terminate and
     // keep going to the child and then parent

    }
    else{ /* Child will wait for the Grandchild to complete*/
      
      wait(NULL);
      printf("\n Grandchild Complete \n");
    }
	}
	else {
	/* parent will wait for the child to complete */
		wait(NULL);
		printf("\n Child Complete \n");
		exit(0);
	}
}
