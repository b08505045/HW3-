// Rabin-Karp
// find first and last palindrome by using pattern p and string t, p will vary, and palindrome will be p + t (t + p)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long mod(long long t, long long q){
    if(t > 0)
        return t % q;
    else if(t == 0) return 0;
    else
        return t % q + q;
}

int main(){
    char *s = malloc(10000000 * sizeof(char));
    scanf("%s", s);
    int length = strlen(s);
    
    unsigned long long D = 94, Q = 18014398777917439, H = D % Q;
    long long p = mod(s[0] - '!', Q), t = p, h = 1, temp; // t = string comapre to pattern, p = pattern
    int tf = length - 1, tl; // index t begin, which will be the last (or first) index of palindrome
    int j = 0, k = length - 1; // last (or first) index of first and last p
    int m = 0, M = 0;

    // find first palindrome
    int same = 1;
    while(1){
        // find first index of tf
        for(tf; tf >= 0; tf--){
            if(s[tf] == s[0]) break;        
        }
        // printf("tf now : %d\n", tf);
        int i = tf;
        // Let's find !
        while(i > j + 2){
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
                same = 0;
                // printf("p : %lld\n", p);
                // printf("i now : %d\n", i);
                // find new start index of t that t = p
                int repeat = 0;
                while(tf != j){
                    if(!repeat){
                        int dif = m - M;
                        for(int a = 0; a < dif; a++)
                            h = mod(h * H, Q); // (A * B) mod C = (A mod C * B mod C) mod C
                        M = m;
                    }
                    for(tf; tf > j;){
                        t = mod(D * (t - (s[tf] - '!') * h) + (s[--i] - '!'), Q);
                        tf--;
                        if(s[tf] == s[0])
                            break;
                    }
                    // printf("tf : %d, i : %d\n", tf, i);
                    // printf("t : %lld\n", t);
                    if(t == p){
                        // printf("Let's compare\n");
                        same = 1;
                        repeat = 0;
                        // if t = p, check character one by one
                        for(int a = 0; a <= tf - i; a++){
                            if(s[a] != s[tf - a]){
                                same = 0;
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
        // i and j encounter
        if(same) break;
        else{
            same = 1;
            p = mod(s[0] - '!', Q);
            t = p;
            h = 1;
            m = 0;
            M = 0;
            j = 0;
            tf--;
            // printf("tf : %d\n", tf);
        }
    }
    //------------------------------------------------------------printf first palindrome
    // printf("%lld\n", tf + 1);
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
        same = 1;
        // printf("Fine\n-------------------------------------\n");
        p = mod(s[length - 1] - '!', Q); // p now start from s's last
        t = p;
        h = 1;
        m = 0;
        M = 0;
        k = length - 1;
        tl = 1;
        // printf("init t : %lld, init p : %lld\n", t, p);
        while(1){
            // find first index of tl
            for(tl; tl < length; tl++){
                if(s[tl] == s[length - 1]) break;
            }
            int i = tl;
            // Let's find !
            while(i < k - 2){ 
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
                    same = 0;
                    // printf("t != p\n");
                    int repeat = 0;
                    // find new start index of t that t = p
                    while(tl != k){
                        if(!repeat){
                            int dif = m - M;
                            for(int a = 0; a < dif; a++)
                                h = mod(h * H, Q); // (A * B) mod C = (A mod C * B mod C) mod C
                            M = m;
                        }
                        for(tl; tl < k;){
                            t = mod(D * (t - (s[tl] - '!') * h) + (s[++i] - '!'), Q);
                            tl++;
                            if(s[tl] == s[length - 1])
                                break;
                        }
                        if(t == p){
                            same = 1;
                            // printf("Let's compare\n");
                            repeat = 0;
                            // printf("break?\n");
                            for(int a = 0; a <= i - tl; a++){
                                if(s[tl + a] != s[length - 1 - a]){
                                    same = 0;
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
            if(same) break;
            else{
                same = 1;
                p = mod(s[length - 1] - '!', Q);
                t = p; 
                h = 1;
                m = 0;
                M = 0;
                k = length - 1;
                tl++;
            }
        }
        // printf("tf : %d, tl : %d\n", tf, tl);
        int dis_f = tf + 1, dis_l = length - tl;
        // printf("dis_f : %d, dis_l : %d\n", dis_f, dis_l);
        if(dis_f > dis_l){
            // printf("f > l\n");
            int add_length = length - dis_f;
            printf("%d\n", add_length);
            char *add = malloc((add_length + 1) * sizeof(char));
            for(int i = 0; i < add_length; i++){
                add[i] = s[length - 1 - i]; 
            }
            add[add_length] = '\0';
            printf("%s%s\n", add, s);
        }
        else if (dis_f < dis_l){
            int add_length = length - dis_l;
            printf("%d\n", add_length);
            char *add = malloc((add_length + 1) * sizeof(char));
            for(int i = 0; i < add_length; i++){
                add[i] = s[add_length - 1 - i];
            }
            add[add_length] = '\0';
            printf("%s%s\n", s, add);
        }
        else{
            int add_length = length - dis_l;
            printf("%d\n", add_length);
            char *add_1 = malloc((add_length + 1) * sizeof(char));
            for(int i = 0; i < add_length; i++){
                add_1[i] = s[length - 1 - i]; 
            }
            add_1[add_length] = '\0';
            char *add_2 = malloc((add_length + 1) * sizeof(char));
            for(int i = 0; i < add_length; i++){
                add_2[i] = s[add_length - 1 - i];
            }
            add_2[add_length] = '\0';
            printf("%s%s\n%s%s\n", add_1, s, s, add_2);
        }
    }
    //------------------------------------------------------------printf last palindrome
    // for(int i = length - 1; i >= tl; i--){
    //     printf("%c", s[i]);
    // }
    // printf("\n");
    //------------------------------------------------------------
    return 0;
}
