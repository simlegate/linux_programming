#include <stdlib.h>
#include <stdio.h>
int main(){
  printf("Running ps with system\n");
  system("ps ax");
  printf("done\n");
  exit(10);
}
