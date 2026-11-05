#include <stdio.h>
#include <string.h>

void displayMenu(){
    printf("\n=== Library Management System ===\n");
    printf("1. Register Member\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType){
    printf("Enter Name: ");
    scanf(" %[^\n]", name); 
    printf("Enter Student ID: ");
    scanf("%d", studentID); 
    printf("Enter Membership Type (1 for Student, 2 for Faculty): ");
    scanf("%d", memberType);
    printf("Registration Successful!\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks){
    printf("ID\tTitle\t\tCopies\n");
    for (int i = 0; i < totalBooks; i++){
        printf("%d\t%s\t\t%d\n", bookIDs[i], bookTitles[i], availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType){
    if (*borrowedCount >= 3){
        printf("Limit reached (Max 3).\n");
        return;
    }
    
    int reqID;
    printf("Enter Book ID: ");
    scanf("%d", &reqID);
    
    int found =0;
    for (int i =0; i <totalBooks; i++){
        if (bookIDs[i] ==reqID){
            found =1;
            if (availableCopies[i] >0){
                availableCopies[i] =availableCopies[i] -1;
                borrowedBookIDs[*borrowedCount] =reqID;
                *borrowedCount =*borrowedCount +1;
                printf("Borrowed!\n");
            } else{
                printf("No copies left.\n");
            }
        }
    }
    if (found == 0){
        printf("Invalid ID.\n");
    }
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine){
    int reqID, days;
    printf("Enter Book ID: ");
    scanf("%d", &reqID);
    
    int index = -1;
    for (int i = 0; i < *borrowedCount; i++){
        if (borrowedBookIDs[i] == reqID){
            index =i;
            break;
        }
    }
    
    if (index == -1){
        printf("Not borrowed.\n");
        return 0.0;
    }
    
    printf("Days kept: ");
    scanf("%d", &days);
    
    int allowedDays;
    if (memberType ==1){
        allowedDays =14;
    } else{
        allowedDays =30;
    }
    
    float currentFine =0.0;
    
    if (days >allowedDays){
        int extraDays =days - allowedDays;
        
        float finePerDay;
        if (memberType ==1){
            finePerDay =20.0;
        } else{
            finePerDay =10.0;
        }
        
        currentFine =extraDays *finePerDay;
        printf("Late! Fine: %.2f\n", currentFine);
        
        char code[20];
        printf("Enter code (if any): ");
        scanf(" %s", code);
        
        if (strcmp(code, "LIB2026") == 0){
            currentFine =currentFine*0.5;
            printf("Waiver applied. New fine: %.2f\n", currentFine);
        }
    }
    
    *totalFine = *totalFine+currentFine;
    
    for (int i =0; i<totalBooks; i++){
        if (bookIDs[i] == reqID){
            availableCopies[i] =availableCopies[i] +1;
            break;
        }
    }
    
    for (int i =index; i<(*borrowedCount)- 1; i++){
        borrowedBookIDs[i] = borrowedBookIDs[i+1];
    }
    *borrowedCount =*borrowedCount - 1;
    
    printf("Returned!\n");
    return currentFine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver){
    printf("Name: %s\n", name);
    printf("ID: %d\n", studentID);
    
    if (memberType ==1){
        printf("Type: Student\n");
    } else{
        printf("Type: Faculty\n");
    }
    
    printf("Borrowed: %d\n", borrowedCount);
    for (int i=0; i<borrowedCount; i++){
        printf(" - Book %d\n", borrowedBookIDs[i]);
    }
    printf("Total Fine: %.2f\n", fineAfterWaiver);
}

int main(){
    int bookIDs[] ={101, 102, 103, 104};
    char bookTitles[][50] = {"C Programming", "Data Structures", "Database Systems", "Computer Networks"};
    int availableCopies[] = {5, 3, 0, 4};
    int totalBooks = 4;
    
    char name[50] ="";
    int studentID =0, memberType =0, borrowedCount =0;
    int borrowedBookIDs[3];
    float totalFine = 0.0;
    
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice){
            case 1:
                registerMember(name, &studentID, &memberType);
                break;
            case 2:
                displayBooks(bookIDs, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                if (studentID == 0){
                    printf("Please register first!\n");
                } else {
                    borrowBook(bookIDs, bookTitles, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType);
                }
                break;
            case 4:
                if (studentID == 0){
                    printf("Please register first!\n");
                } else {
                    returnBook(bookIDs, availableCopies, totalBooks, borrowedBookIDs, &borrowedCount, memberType, &totalFine);
                }
                break;
            case 5:
                if (studentID == 0){
                    printf("Please register first!\n");
                } else {
                    displayMemberRecord(name, studentID, memberType, borrowedBookIDs, borrowedCount, totalFine, totalFine);
                }
                break;
            case 6:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (choice !=6);

    return 0;
}
