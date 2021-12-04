Name: Rodrigo Onate Garcia
CPSC 351
California State University, Fullerton

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>

std::string alpNum;
std::stringstream readIn;
bool check = true;
bool check2 = true;

void *alpha_thread(void *param);
void *numeric_thread(void *param);

int main(int argc, char *argv[]){

  pthread_t tid;
  pthread_t tid2;
  pthread_attr_t attr;
  pthread_attr_t attr2;


  if(argc != 2){
    fprintf(stderr, "usage: ./a.out <string value>\n");
    return -1;
  }

  readIn << argv[1];
  readIn >> alpNum;

  pthread_attr_init(&attr);
  pthread_attr_init(&attr2);

  pthread_create(&tid, &attr, alpha_thread, NULL);
  pthread_create(&tid2, &attr2, numeric_thread, NULL);

  pthread_join(tid, NULL);
  pthread_join(tid2, NULL);

}

void *alpha_thread(void *param){

  while(readIn){
    if(isalpha(alpNum[0])){
      std::cout << "Alpha:   " << alpNum << std::endl;
      check = true;
    }else{
      check = false;
      check2 = false;
      if(!readIn) break;
      while(check2 == false);
    }
    if(check){
      readIn >> alpNum;
    }
  }
  check2 = false;
  pthread_exit(0);
}

void *numeric_thread(void *param){

  while(readIn){
    if(isdigit(alpNum[0])){
      std::cout << "Numeric: " << alpNum << std::endl;
      check = true;
    }else{
      check = false;
      check2 = true;
      if(!readIn) break;
      while(check2 == true);
    }
    if(check){
      readIn >> alpNum;
    }
  }
  check2 = true;
  pthread_exit(0);
}
