        #include <stdio.h>
        int main(void) {
        FILE *f;
        f = fopen("file","wb");
        printf("%d",f != NULL);
        fclose(f);
        return 0;
    }
