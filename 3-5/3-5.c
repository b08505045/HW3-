#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int index;
    long long num;
}node;

void merge(node *n, int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1, n2 = r - m;
    node *L = malloc(n1 * sizeof(node)), *R = malloc(n2 * sizeof(node));
    for(i = 0; i < n1; i++)
        L[i] = n[l + i];
    for(j = 0; j < n2; j++)
        R[j] = n[m + 1 + j];
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if(L[i].num <= R[j].num){
            n[k] = L[i];
            i++;
        }
        else{
            n[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        n[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        n[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(node *n, int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(n, left, mid);
        mergeSort(n, mid + 1, right);
        merge(n, left, mid, right);
    }
}

long long mod(long long t, long long q){
    if(t > 0)
        return t % q;
    else if(t == 0) return 0;
    else
        return t % q + q;
}

long long fact(long long n){
    int f = 1;
    for(int i = 1; i <= n; i++){
        f = f * i;
    }
    return f;
}

int main() {
    long long D = 94, Q = 18014398777917439, H = D % Q, h = 1;
    int k, l, flag;
    scanf("%d %d %d", &k, &l, &flag);
    char **s = malloc(k * sizeof(char*));
    for(int i = 0; i < k; i++){
        s[i] = malloc((l + 1) * sizeof(char));
        scanf("%s", s[i]);
        s[i][l] = '\0';
    }

    node *Rabin = malloc(k * sizeof(node)), *similar = malloc(k * sizeof(node));
    long long temp = 0;
    int *index = malloc(k * sizeof(int)); // sorted array's element's original index
    // construct Rabin[] and same[]
    for(int i = 0; i < k; i++){
        for(int j = 0; j < l; j++){
            temp = mod(D * temp + (s[i][j] - '!'), Q);
        }
        Rabin[i].num = temp;
        Rabin[i].index = i;
        temp = 0;
    }
    //---------------------------------------------------------------------------
    // for(int i = 0; i < k; i++){
    //     printf("%lld ", Rabin[i].num);
    // }
    // printf("\n");
    //---------------------------------------------------------------------------
    int j = l - 1;
    if(!flag){
        int x, y; // two index x, y
        int find = 0; // find, stop! (since only need either one pair)
        while(!find && j >= 0){
            //---------------------------------------------------------------------------
            // printf("discard index : %d\n", j);
            // for(int i = 0; i < k;i++){
            //     printf("%c ", s[i][j]);
            // }
            // printf("\n");
            //---------------------------------------------------------------------------
            for(int i = 0; i < k; i++){
                similar[i].num = mod(Rabin[i].num - (s[i][j] - '!') * h, Q);
                similar[i].index = i;
            }
            mergeSort(similar, 0, k - 1);
            for(int i = 0; i < k - 1; i++){
                if(similar[i].num == similar[i + 1].num){
                    x = similar[i].index;
                    y = similar[i + 1].index;
                    find = 1;
                    break;
                }
            }
            if(find) break;
            h = mod(h * H, Q);
            j--;
        }
        
        if(find)
            printf("Yes\n%d %d\n", x, y);
        else
            printf("No\n");
    }
    else{
        long long num_of_pairs = 0, num_of_same, consec, minus_consec, num_of_minus;
        int m = 0, minus_m;
        int a, minus_a;
        // calculate number of same

        // copy Rabin[i]'s value to same
        node *same = malloc(k * sizeof(node));
        for(int i = 0; i < k; i++){
            same[i] = Rabin[i];
        }
        mergeSort(same, 0, k - 1);
        while(m < k - 1){
            if(same[m].num == same[m + 1].num){
                consec = 1;
                a = m;
                while(a < k - 1){
                    if(same[a].num == same[a + 1].num){
                        consec++;
                    }
                    else
                        break;
                    a++;
                }
                num_of_pairs += (consec * (consec - 1)) / 2;
                m = a + 1;
            }
            else
                m++;
        }
        num_of_same = num_of_pairs;
        // printf("num of pairs : %lld, num of same : %lld\n", num_of_pairs, num_of_same);


        // calculate number of similar
        // printf("\nsimilar :\n");
        while(j >= 0){
            // printf("h = %d\n", h);
            m = 0;
            //---------------------------------------------------------------------------
            // printf("discard ");
            // printf("index : %d\n", j);
            // for(int i = 0; i < k;i++){
            //     printf("%c ", s[i][j]);
            // }
            // printf("\n");
            //---------------------------------------------------------------------------
            for(int i = 0; i < k; i++){
                similar[i].num = mod(Rabin[i].num - (s[i][j] - '!') * h, Q);
                similar[i].index = i;
            }
            //---------------------------------------------------------------------------
            // for(int i = 0; i < k; i++){
            //     printf("%d ", similar[i].num);
            // }
            // for(int i = 0; i < k; i++){
            //     printf("%d ", similar[i].index);
            // }
            // printf("\n");
            //---------------------------------------------------------------------------
            mergeSort(similar, 0, k - 1);
            //---------------------------------------------------------------------------
            // for(int i = 0; i < k; i++){
            //     printf("%d ", similar[i].num);
            // }
            // for(int i = 0; i < k; i++){
            //     printf("%d ", similar[i].index);
            // }
            // printf("\n\n");
            //---------------------------------------------------------------------------
            while(m < k - 1){
                if(similar[m].num == similar[m + 1].num){
                    // printf("similar at %d, %d\n", m, m + 1);
                    // printf("same at discard index %d when %d!\n", j, m);
                    consec = 1;
                    same[0] = Rabin[similar[m].index];
                    a = m;
                    while(a < k - 1){
                        if(similar[a].num == similar[a + 1].num){
                            same[consec] = Rabin[similar[a + 1].index];
                            consec++;
                        }
                        else
                            break;
                        a++;
                    }
                    // printf("consec : %d\n", consec);
                    num_of_pairs += (consec * (consec - 1)) / 2;
                    // printf("plus : %d\n", fact(consec) / (fact(2) * fact(consec - 2)));
                    m = a + 1;
                    //---------------------------------------------------------------------------
                    // for(int i = 0; i < consec; i++){
                    //     printf("%d ", same[i].num);
                    // }
                    // printf("\n");
                    //---------------------------------------------------------------------------
                    mergeSort(same, 0, consec - 1);
                    //---------------------------------------------------------------------------
                    // for(int i = 0; i < consec; i++){
                    //     printf("%d ", same[i].num);
                    // }
                    // printf("\n");
                    //---------------------------------------------------------------------------
                    minus_m = 0;
                    num_of_minus = 0;
                    while(minus_m < consec - 1){
                        if(same[minus_m].num == same[minus_m + 1].num){
                            minus_consec = 1;
                            minus_a = minus_m;
                            while(minus_a < consec - 1){
                                if(same[minus_a].num == same[minus_a + 1].num){
                                    minus_consec++;
                                }
                                else
                                    break;
                                minus_a++;
                            }
                            minus_m = minus_a + 1;
                            // printf("minus_consec : %d\n", minus_consec);
                            num_of_minus += (minus_consec * (minus_consec - 1)) / 2;
                        }
                        else
                            minus_m++;
                    }
                    // printf("num_of_minus : %d\n", num_of_minus);
                    num_of_pairs -= num_of_minus;
                }
                else
                    m++;
            }
            h = mod(h * H, Q);
            j--;
        }
        if(num_of_pairs)
            printf("Yes\n%lld\n", num_of_pairs);
        else
            printf("No\n");
    }
}
