#include <stdio.h>

int main(){
    int rows,seats;
    printf("Enter number of rows: ");
    scanf("%d",&rows);
    printf("Enter number of seats per row: ");
    scanf("%d", &seats);

    int cinema[100][100];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < seats; j++) {
            printf("Enter 1 if Row %d Seat %d is booked, 0 if empty: ", i, j);
            scanf("%d", &cinema[i][j]);
        }
    }

    // Display seating plan
    printf("\nSeating Plan\n");
    for (int i=0; i<rows;i++){
        printf("R%d: ",i);
        for (int j =0; j<seats;j++){
            if (cinema[i][j] ==0){
                printf("O ");
            } else{
                printf("X ");
            }
        }
        printf("\n");
    }

    // Availability report
    int total_free= 0;
    printf("Free seats per row: ");
    for (int i = 0;i<rows;i++){
        int row_free =0;
        for (int j =0; j<seats;j++){
            if(cinema[i][j]==0){
                row_free++;
                total_free++;
            }
        }
        printf("%d ",row_free);
    }
    printf("Total free: %d\n",total_free);

    // Group booking
    int k;
    printf("\nEnter number of customers sitting together: ");
    scanf("%d", &k);

    if (k <=0 || k >seats) {
        printf("Invalid group size.\n");
        return 0;
    }

    // Figure out the search order (middle out)
    int order[100];
    int mid = rows/2;
    order[0] =mid;
    int index =1;
    for (int dist = 1; dist <= rows; dist++){
        if (mid - dist >= 0){
            order[index]= mid - dist;
            index++;
        }
        if (mid + dist<rows){
            order[index] =mid + dist;
            index++;
        }
    }

    // Search for seats
    int found =0;
    for (int i = 0;i <rows &found == 0;i++){
        int r = order[i];
        
        // Very simple logic: check every possible starting seat
        for (int start_seat =0;start_seat<=seats -k && found ==0;start_seat++){
            int is_empty =1;
            
            // Check if the next k seats are all 0
            for (int x =0; x <k;x++){
                if (cinema[r][start_seat+x] ==1){
                    is_empty =0; 
                    break;
                }
            }
            
            // If they are all empty, book them!
            if (is_empty ==1) {
                for (int x =0; x <k;x++){
                    cinema[r][start_seat+x] =1;
                }
                printf("Group of %d seated in Row %d, Seats %d to %d\n", k, r, start_seat, start_seat + k - 1);
                found = 1;
            }
        }
    }

    if (found ==0){
        printf("No suitable block of %d consecutive seats found.\n", k);
    } else {
        printf("\n Updated Seating Plan\n");
        int new_total_free =0;
        for (int i =0; i<rows; i++){
            printf("R%d: ", i);
            for (int j = 0; j<seats;j++){
                if (cinema[i][j] ==0){
                    printf("O ");
                    new_total_free++;
                } else {
                    printf("X ");
                }
            }
            printf("\n");
        }
        printf("Remaining free seats: %d\n", new_total_free);
    }

    return 0;
}
