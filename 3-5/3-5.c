#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define d 89
#define q 6312646216567629137
  
int main(){
    char *c = malloc(10000000 * sizeof(char));
    scanf("%s", c);
    // printf("%s\n",c);
    int length = strlen(c);
    // printf("length : %d\n", length);
    char *s = malloc(length * sizeof(char));
    strcpy(s, c);
    // printf("input : %s\n", s);
    free(c);
    // printf("%s\n", s);
    // printf("first : %c, last : %c\n", first, last);
    // for(int i = 0; i < length; i++){
    //     printf("%c", s[i]);
    // }
    int find = 0;
    int i; // the last index of first sub-palindrome
    for(i = length - 1; i >= 0; i--){
        if(s[i] == s[0]){
            find = 1;
            for(int k = 1; k <= i / 2; k++){
                if(s[k] != s[i - k]){
                    find = 0;
                    break;
                }
            }
        }
        if(find) break;
    }
    // damn goooooooood
    if(i == length - 1){
        printf("%d\n%s\n", 0, s);
    }
    // OK FINE
    else{
        find = 0;
        int j; // the first index of last sub-palindrome
        for(j = i; j < length; j++){
            if(s[length - 1] == s[j]){
                find = 1;
                for(int k = j + 1; k < (j + length - 1) / 2; k++){
                    if(s[k] != s[length - 1 - k + j]){
                        find = 0;
                        break;
                    }
                }
            }
            if(find) break;
        }
        // printf("Start!\n");
        //compare
        int first_len = i + 1, last_len = length - j;
        // printf("i : %d, j : %d\n", i, j);
        // printf("first_len : %d, last_len : %d\n", first_len, last_len);
        if(first_len > last_len){
            printf("%d\n", length - first_len);
            for(int k = length - 1; k > i; k--){
                printf("%c", s[k]);
            }
            printf("%s\n", s);
        }
        else if(first_len < last_len){
            printf("%d\n", length - last_len);
            printf("%s", s);
            for(int k = j - 1; k >= 0; k--){
                printf("%c", s[k]);
            }
            printf("\n");
        }
        else{
            printf("%d\n", length - first_len);
            for(int k = length - 1; k > i; k--){
                printf("%c", s[k]);
            }
            printf("%s\n", s);
            printf("%s", s);
            for(int k = j - 1; k >= 0; k--){
                printf("%c", s[k]);
            }
            printf("\n");
        }
    }
    return 0;
}
