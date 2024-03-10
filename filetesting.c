# include <stdio.h>
# include <string.h>

void dectobin(int n){
    if(n>1) dectobin(n>>1);
    printf("%d",n&1);
}

int main(){
    int n=65;
    dectobin(n);
}