#include <stdio.h>
#include <stdlib.h>


int main(){
  int cupcakes;
  int testcase;
  // int i; // for loop
  scanf("%d", &testcase);
  /*
  for(i=0; i<testcase;i++){
    scanf("%d", &cupcakes);
    printf("%d\n",cupcakes/2+1);
  }
  */
  do {
    scanf("%d", &cupcakes);
    printf("%d\n", cupcakes/2+1);
  } while(--testcase);
  /*
  while(testcase--){
    scanf("%d", &cupcakes);
    printf("%d\n", (cupcakes/2)+1);
  }
  */
  return 0;
}