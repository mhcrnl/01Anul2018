    #include <stdio.h>
    int main(void) {
        int i = 5, j = 16;
        while(j >= 0) {
                i /= 2;
                j -= i / 2;
        }
        printf("%d",i + j);
        return 0;
    }
