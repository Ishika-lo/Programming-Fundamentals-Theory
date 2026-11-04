#include <stdio.h>
void inputReadings(int sensors, int hours, int temp[][100]){
    for (int i =0; i <sensors;i++){
        printf("Sensor %d readings:\n", i+1);
        for (int j =0; j <hours; j++){
            scanf("%d", &temp[i][j]);
        }
    }
}

float analyzeSensor(int readings[],int hours, int sensorNum){
    int total =0, critical =0, warning =0;
    int max =readings[0]; 
    int min =readings[0]; 
    int current_streak =0;
    int max_streak =0;

    for (int i =0; i <hours; i++){
        int r =readings[i];
        total =total + r;
        
        if (r >max) max =r;
        if (r <min) min =r;
        
        if (r >=40){
            critical++;
        } else if (r >=35 && r <=39){
            warning++;
        }
        
        if (r >=35){
            current_streak++;
            if (current_streak >max_streak){
                max_streak =current_streak;
            }
        } else {
            current_streak =0;
        }
    }

    float avg =(float)total /hours;
    printf("Sensor %d: Total %d Avg=%.2f Max %d Min %d Critical=%d Warning %d Longest hot streak=%d\n",
           sensorNum, total, avg, max, min, critical, warning, max_streak);
           
    return avg; 
}

void findHighestAverage(float averages[], int sensors){
    float highest =averages[0];
    int best = 1;

    for (int i =0; i <sensors; i++){
        if (averages[i] >highest){
            highest =averages[i];
            best = i+ 1; 
        }
    }
    
    printf("Highest average: Sensor %d (%.2f)\n", best, highest);
}

int main(){
    int sensors, hours;
    printf("Enter sensors: ");
    scanf("%d", &sensors);
    printf("Enter hours: ");
    scanf("%d", &hours);

    int temp[100][100];
    float averages[100]; 

    inputReadings(sensors, hours, temp);
    printf("\n");

    for (int i = 0; i < sensors; i++) {
        averages[i] = analyzeSensor(temp[i], hours, i + 1); 
    }

    findHighestAverage(averages, sensors);
    return 0;
}
