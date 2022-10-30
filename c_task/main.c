#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
int main(int argv,char** argc) {
    printf("Hello, World!\n");
    for(int i=0;i<argv;i++){
        printf("input %d\t%s\n",i,argc[i]);
    }
    int loop_count=0;
    while(1){
        loop_count++;
        printf("loop_count=%d\n",loop_count);
        sleep(1);
    }
    return 0;
}
