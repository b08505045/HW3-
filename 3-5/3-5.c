// find first and last palindrome by using pattern p and string t, p will vary, and palindrome will be p + t (t + p)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define D 94 // number of total inputs
#define Q 7393913 // mod q

long long mod(long long t, long long q){
    if(t >= 0)
        return t % q;
    else
        return t % q + q;
}

int main(){
    char *c = malloc(10000000 * sizeof(char));
    scanf("%s", c);
    int length = strlen(c);
    char *s = malloc(length * sizeof(char));
    strcpy(s, c); // s will be the input
    free(c);
    
    long long t, p, h, temp; // t = string comapre to pattern, p = pattern
    int tf = length - 1, tl = 1; // index t begin, which will be the last (or first) index of palindrome
    p = mod(s[0] - '!', Q);
    t = p;
    int j = 0, k = length - 1; // last (or first) index of first and last p
    int m = 0;

    // find first palindrome
    while(1){
        // find first index of tf
        for(tf; tf >= 0; tf--){
            if(s[tf] == s[0]) break;
        }
        // printf("tf now : %d\n", tf);
        int i = tf;
        // Let's find !
        while(i != j && i != j + 1){
            temp = mod(D * t + (s[i - 1] - '!'), Q);
            // if current t = p
            if(temp == mod(D * p + (s[j + 1] - '!'), Q) && s[i - 1] == s[j + 1]){
                t = temp;
                p = mod(D * p + (s[j + 1] - '!'), Q);
                j++;
                m++;
                i--;
            }
            // if t != p
            else{
                // printf("p : %lld\n", p);
                // printf("i now : %d\n", i);
                // find new start index of t that t = p
                int repeat = 0;
                while(1){
                    if(!repeat){
                        if(m <= 9)
                            h = mod(pow(D, m), Q);
                        else{
                            h = mod(D, Q);
                            for(int a = 1; a < m; a++)
                                h = mod(h, mod(D, Q)); // (A * B) mod C = (A mod C * B mod C) mod C
                        }
                    }
                    for(i; i > j;){
                        t = mod(D * (t - (s[tf] - '!') * h) + s[--i] - '!', Q);
                        tf--;
                        if(s[tf] == s[0])
                            break;
                    }
                    // printf("tf : %d, i : %d\n", tf, i);
                    // printf("t : %lld\n", t);
                    if(i == j) break;
                    else if(t == p){
                        // printf("Let's compare\n");
                        repeat = 0;
                        for(int a = 0; a <= tf - i; a++){
                            if(s[a] != s[tf - a]){
                                repeat = 1;
                                break;
                            }
                        }
                    }
                    else repeat = 1;
                    if(!repeat){
                        // printf("break!\n");
                        break;
                    }
                }
            }
        }
        int same = 0;
        // i and j encounter
        if(t == p){
            same = 1;
            for(int a = 0; a <= j; a++){
                if(s[a] != s[tf - a]){
                    same = 0;
                    break;
                }
            }
        }
        if(same) break;
        else{
            p = s[0] - '!';
            t = p;
            m = 0;
            j = 0;
            tf = i;
        }
    }
    //------------------------------------------------------------printf first palindrome
    // printf("%lld\n", tf);
    // for(int i = 0; i <= tf; i++){
    //     printf("%c", s[i]);
    // }
    // printf("\n");
    //------------------------------------------------------------

    // whole string is palindrome ! damn goooooooood
    if(tf == length - 1)
        printf("%d\n%s\n", 0, s);
    // OK FINE
    else{
        p = s[length - 1] - '!'; // p now start from s's last
        t = p;
        m = 0;
        while(1){
            // find first index of tl
            for(tl; tl < length; tl++){
                if(s[tl] == s[length - 1]) break;
            }
            int i = tl;
            // Let's find !
            while(i != k && i != k - 1){ 
                temp = mod(D * t + (s[i + 1] - '!'), Q);
                // if current t = p
                if(temp == mod(D * p + (s[k - 1] - '!'), Q) && s[i + 1] == s[k - 1]){
                    t = temp;
                    p = mod(D * p + (s[k - 1] - '!'), Q);
                    k--;
                    m++;
                    i++;
                }
                // if t != p
                else{
                    int repeat = 0;
                    // find new start index of t that t = p
                    while(!repeat){
                        if(!repeat){
                            if(m <= 9)
                                h = mod(pow(D, m), Q);
                            else{
                                h = mod(D, Q);
                                for(int a = 1; a < m; a++)
                                    h = mod(h, mod(D, Q)); // (A * B) mod C = (A mod C * B mod C) mod C
                            }
                        }
                        for(i; i < k;){
                            t = mod(D * (t - (s[tl] - '!') * h) + (s[++i] - '!'), Q);
                            tl++;
                            if(s[tl] == s[length - 1])
                                break;
                        }
                        if(i == k) break;
                        else if(t == p){
                            // printf("Let's compare\n");
                            repeat = 0;
                            for(int a = 0; a <= i - tl; a++){
                                if(s[tl + a] != s[length - 1 - a]){
                                    repeat = 1;
                                    break;
                                }
                            }
                        }
                        else repeat = 1;
                        if(!repeat){
                            // printf("break!\n");
                            break;
                        }
                    }
                }
            }
            int same = 0;
            // i and j encounter
            if(t == p){
                same = 1;
                for(int a = 0; a <= length - k - 1; a++){
                    if(s[tl + a] != s[length - 1 - a]){
                        same = 0;
                        break;
                    }
                }
            }
            if(same) break;
            else{
                p = s[length - 1] - '!';
                t = p;
                m = 0;
                k = 0;
                tl = i;
            }
        }
    }
    //------------------------------------------------------------printf last palindrome
    // for(int i = length - 1; i >= tl; i--){
    //     printf("%c", s[i]);
    // }
    // printf("\n");
    //------------------------------------------------------------
    int dis_f = tf + 1, dis_l = length - tl;
    if(dis_f > dis_l){
        printf("%d\n", length - dis_f);
        for(int i = length - 1; i > tf; i--){
            printf("%c", s[i]);
        }
        printf("%s\n", s);
    }
    else if (dis_f < dis_l){
        printf("%d\n", length - dis_l);
        printf("%s", s);
        for(int i = tl - 1; i >= 0; i--){
            printf("%c", s[i]);
        }
        printf("\n");
    }
    else{
        printf("%d\n", length - dis_l);
        for(int i = length - 1; i > tf; i--){
            printf("%c", s[i]);
        }
        printf("%s\n", s);
        printf("%s", s);
        for(int i = tl - 1; i >= 0; i--){
            printf("%c", s[i]);
        }
        printf("\n");

    }
    return 0;
}
