#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(){
    char *c = malloc(10000000 * sizeof(char));
    scanf("%s", c);
    int length = strlen(c);
    char *s = malloc((length + 1) * sizeof(char)), *rev_s = malloc((length + 1) * sizeof(char));
    strncpy(s, c, length); // s will be the input
    s[length] = '\0';
    free(c);
    
    for(int i = 0; i < length; i++){
        rev_s[i] = s[length - 1 - i];
    }
    rev_s[length] = '\0';
    
    int *pi_s = malloc(length * sizeof(int)), *pi_rev = malloc(length * sizeof(int));
    int len = 0;
    int f_len, l_len;

    pi_s[0] = 0;
    int i = 1, index = 0;
    // printf("length : %d\n", length);
    while(i < length){
        if(s[i] == s[index]){
            index++;
            pi_s[i] = index;
            i++;
        }
        else{
            if(index)
                index = pi_s[index - 1];
            else{
                pi_s[i] = 0;
                i++;
            }
        }
    }

    i = 0;
    index = 0;
    while(i < length){
        if(rev_s[i] == s[index]){
            index++;
            pi_rev[i] = index;
            i++;
        }
        else{
            if(index)
                index = pi_s[index - 1];
            else{
                pi_rev[i] = 0;
                i++;
            }
        }
    }

    f_len = length - pi_rev[length - 1];
    
    if(!f_len){
        printf("%d\n%s\n", 0, s);
    }
    else{
        pi_rev[0] = 0;
        i = 1;
        index = 0;
        while(i < length){
            if(rev_s[i] == rev_s[index]){
                index++;
                pi_rev[i] = index;
                i++;
            }
            else{
                if(index)
                    index = pi_rev[index - 1];
                else{
                    pi_rev[i] = 0;
                    i++;
                }
            }
        }

        i = 0;
        index = 0;
        while(i < length){
            if(s[i] == rev_s[index]){
                index++;
                pi_s[i] = index;
                i++;
            }
            else{
                if(index)
                    index = pi_rev[index - 1];
                else{
                    pi_s[i] = 0;
                    i++;
                }
            }
        }
        l_len = length - pi_s[length - 1];
        // printf("last : %d\n", l_len);
        if(f_len < l_len){
            int add_length = f_len;
            char *add = malloc((add_length + 1) * sizeof(char));
            for(int j = 0; j < add_length; j++){
                add[j] = s[length - 1 - j];
            }
            add[add_length] = '\0';
            printf("%d\n%s%s\n", add_length, add, s);
        }
        else if(f_len > l_len){
            int add_length = l_len;
            char *add = malloc((add_length + 1) * sizeof(char));
            for(int j = 0; j < add_length; j++){
                add[j] = s[add_length - 1 - j];
            }
            add[add_length] = '\0';
            printf("%d\n%s%s\n", add_length, s, add);
        }
        else{
            int add_length = f_len;
            char *add_1 = malloc((add_length + 1) * sizeof(char));
            char *add_2 = malloc((add_length + 1) * sizeof(char));
            for(int j = 0; j < add_length; j++){
                add_1[j] = s[length - 1 - j]; 
            }
            add_1[add_length] = '\0';
            for(int j = 0; j < add_length; j++){
                add_2[j] = s[add_length - 1 - j];
            }
            add_2[add_length] = '\0';
            printf("%d\n%s%s\n%s%s\n", add_length, add_1, s, s, add_2);
        }
    }
    return 0;
}
