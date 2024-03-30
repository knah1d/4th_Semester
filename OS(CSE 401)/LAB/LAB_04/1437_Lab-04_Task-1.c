#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h>


int main() {
    int n, sum_odd = 0, sum_even = 0;
    printf("Enter a number: ");
    scanf("%d", &n);
    pid_t pid = fork();  
    if(pid==0) {
        for(int i=1; i<=n; i+=2) {
            sum_odd+=i;
        }
        printf("sum_odd = %d\n", sum_odd);
        printf("PID of child: %d\n\n", getpid());
    }  
    else if(pid>0) {
        for(int i=2; i<=n; i+=2) {
            
            sum_even+=i;

        }
        printf("sum_even = %d\n", sum_even);
        printf("PID of parent: %d\n", getpid());
    }

    return 0;
}
