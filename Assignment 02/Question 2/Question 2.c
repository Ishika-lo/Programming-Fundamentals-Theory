#include <stdio.h>
int sumOfDivisors(int num){
    int sum =0;
    for (int i =1; i <= num/2; i++){
        if (num%i==0){
            sum+=i;
        }
    }
    return sum;
}

int main(){
    int n;
    printf("Enter limit (n): ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);
    
    int total_pairs =0;
    
    for (int i =1; i<=n; i++){
        int sum1 =sumOfDivisors(i);
        
        if (sum1 >i &&sum1<= n){
            int sum2 =sumOfDivisors(sum1);
            if (sum2== i){
                printf("(%d, %d)\n", i, sum1);
                total_pairs++;
            }
        }
    }
    
    printf("Total pairs: %d\n", total_pairs);
    return 0;
}
