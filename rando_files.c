#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>

int reading; //to do error recordings
extern int errno;


int gen_rand_int(int size){//size is number of bytes, num is number of numbers desired
  int fb = open("/dev/random", O_RDONLY);
  int *buffer = (int *)(malloc(1*sizeof(int)));//do it one by one, 1 int at a time
  reading =  read(fb,buffer,size);

  if(reading == -1){
    printf("ERROR # %d \nERROR: ", errno);//, strerrno(errno));
  }
  
  close(fb);
  return *buffer;
}


int main(){
  //Using the fxn up top we generate random numbers
  int rand_values [10];//the holder of our random values
  int i;
  printf("Generating Random Numbers:\n");
  for(i=0; i<10; i++){
    rand_values[i]=gen_rand_int(4);
    printf("random %d: %d\n", i, rand_values[i]);
  }
  
  //Writing numbers to file
  int fd = open("value_deposit.txt", O_CREAT | O_WRONLY);
  reading = write(fd, rand_values, 40);//4 per int, 10 enteries

  if(!reading){
    printf("ERROR # %d \nERROR: ", errno);//, //strerrno(errno));
  }
  
  printf("Writing numbers to file, value_deposit.txt\n\n");
  close(fd);

  //Reading Numbers from file
  int file_values [10];
  int fp = open("value_deposit.txt", O_RDONLY);
  reading = read(fp, file_values, 40);
  printf("Reading numbers from file, value_deposit.txt\n\n");
  close(fp);

  if(!reading){
    printf("ERROR # %d \nERROR: ", errno);//, //strerrno(errno));
  }
  
  //Checking the numbers
  printf("Let's Check the Numbers\n");
  for(int i=0; i<10; i++){
    printf("random %d: %d\n", i, file_values[i]);
  }
  return 0;
}













  //-------------EXPERIMENTATION-NOTHING FOLLOWS-------------------
  /*
  int fd = open("me", O_CREAT | O_WRONLY, 0644);
  printf("%d\n", fd);
  int a [4];
  a[0]=2;
  a[1]=3;
  a[2]=5;
  a[3]=7;
  printf("%ld-num-\n",write(fd, a, 16));
  close(fd);

  int fp = open("me", O_RDONLY);
  int b [4];
  read(fp, b, 16);
  close(fp);
  printf("%d\n", b[0]);
  printf("%d\n", b[1]);
  printf("%d\n", b[2]);
  printf("%d\n", b[3]);

  */
  /*
  int fd = open("rand_nums.txt", O_CREAT | O_WRONLY);
  for(int i=0; i<10; i++){
    write(fd, rand_values, 40);
  }
  int file_values[10];
  for(int i=0; i<10; i++){
    read(fd, file_values, 4);
    
  }
  for(int i=0; i<10; i++){
    printf("%d:",file_values[i]);
  }
  close(fd);
  */  
