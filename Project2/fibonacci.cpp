Name: Rodrigo Onate Garcia
CPSC 351
California State University, Fullerton

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <vector>
// unsgined int type vector
std::vector<size_t> fibNums;

void *fibonacci_thread(void *param);

int main(int argc, char *argv[]){

  pthread_t tid;
  pthread_attr_t attr;

  if(argc != 2){
    fprintf(stderr, "usage: ./a.out <integer value>\n");
    return -1;
  }

  if(atoi(argv[1]) < 0){
    fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
    return -1;
  }
  // initializing attribute
  pthread_attr_init(&attr);
  // creating thread and passing value from console to the thread
  pthread_create(&tid, &attr, fibonacci_thread, argv[1]);
  // waiting for child to finish
  pthread_join(tid, NULL);

  printf("Fibonacci sequence: \n");
  int j;
  // Loop to print all the values allocated in the vector from fibonacci_thread
  for(size_t disp : fibNums){
    std::cout << disp << "  ";
  }

  std::cout << "\n";

  return 0;
}

void *fibonacci_thread(void *param){

  size_t nums = atoi((char*)param);

  if(nums == 0){;
  }else if(nums == 1){
    fibNums.push_back(0);
  }else if(nums == 2){
    fibNums.push_back(0);
    fibNums.push_back(1);
  }else{
    fibNums.push_back(0);
    fibNums.push_back(1);
    for(size_t i = 0; i < nums-2; i++){
      fibNums.push_back(fibNums[i] + fibNums[i+1]);
    }
  }
  pthread_exit(0);
}
