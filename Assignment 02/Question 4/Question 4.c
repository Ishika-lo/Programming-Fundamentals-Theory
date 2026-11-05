#include <stdio.h>
int getValidDays(){
    int days;
    do{
        printf("Number of days: ");
        scanf("%d", &days);
    } while (days<1 || days >7);
    return days;
}

float calculateDailySales(int dayNumber){
    int orders;
    float amount, total =0.0, max_amount =-1.0;
    
    printf("Day %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);
    
    printf("Order amounts: ");
    for (int i =0; i <orders; i++){
        do {
            scanf("%f", &amount);
            if (amount <= 0){
                printf("Amount must be greater than zero. Try again: ");
            }
        } while (amount <=0);
        
        total =total +amount;
        if (amount>max_amount){
            max_amount =amount;
        }
    }
    
    float avg = total/orders;
    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", avg);
    printf("Highest order: Rs. %.2f\n\n", max_amount);
    
    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays){
    float max_sales =-1.0;
    int best_day =1;
    
    for (int i =0; i <numberOfDays; i++){
        if (dailySales[i] >max_sales){
            max_sales =dailySales[i];
            best_day = i+1;
        }
    }
    return best_day;
}

void displayBarChart(float dailySales[], int numberOfDays){
    printf("===== DAILY SALES BAR CHART =====\n");
    for (int i =0; i <numberOfDays; i++){
        printf("Day %d: ", i + 1);
        int stars =(int)(dailySales[i]/100);
        for (int j =0; j <stars; j++){
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main(){
    int days =getValidDays();
    float dailySales[7];
    float total_festival_sales =0.0;
    
    for (int i =0; i <days; i++){
        dailySales[i] =calculateDailySales(i +1);
        total_festival_sales += dailySales[i];
    }
    
    int best_day =findHighestSalesDay(dailySales, days);
    
    printf("===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", total_festival_sales);
    printf("Day with highest sales: Day %d\n", best_day);
    printf("Highest daily sales: Rs. %.2f\n\n", dailySales[best_day - 1]);
    
    displayBarChart(dailySales, days);
    
    return 0;
}
