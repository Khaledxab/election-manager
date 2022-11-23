#include "gest.h"





int main(){
    // animation in starting
    int i;
    printf("\t\t");
    char AppStarting[100] = "Application is Starting....";
    for(i=0;i<strlen(AppStarting);i++){
        printf("%c",AppStarting[i]);
    }
    system("cls");


    while(isRunning == true){
        Menu();
        char *str[100];
        char option;
        scanf("%s",&str);
        option = str[0];
        switch(option){
            case '0':
                Exit();
                break;
            case '1':
                AddNewUSER();
                break;
            case '2':
                ShowAllUSERs();
                break;
            case '3':
                SearchUSER();
                break;
            case '4':
                EditUSER();
                break;
            case '5':
                DeleteUSER();
                break;
            case '6':
                DeleteAllUSERs();
                break;
            case '7':
                system("cls");
                break;
            default:
                ErrorAndRestart("Option not found!");
                break;
        }
    }

    return 0;
}


void Menu(){
    printf("\n\t **** My-USER Management System Using C ****\n");
    printf("\n\t\t\tMAIN MENU\n");
    printf("\t\t=====================\n");
    printf("\t\t[1] Add a new USER\n");
    printf("\t\t[2] Show all USERs\n");
    printf("\t\t[3] Search for USER\n");
    printf("\t\t[4] Edit a USER\n");
    printf("\t\t[5] Delete a USER\n");
    printf("\t\t[6] Delete All USER\n");
    printf("\t\t[0] Exit\n\t\t=================\n\t\t");
    printf("Enter the choice:");
}

void AddNewUSER(){
    system("cls");
    printf("\n\t\t **** Add new USER ****\n\n");
    char Name[20];
    char Phone[20];
    char Email[30];
    char NewUSER[100];
    NewUSER[0] = 0;
    printf("*Name should be unique and maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }
    if(AlreadyExists(Name,'n') == 1){
        ErrorAndRestart("!!!!Name Already Exists!!!");
        return;
    }
    printf("\n*Phone should be unique and maximum 20 characters long.\n");
    printf("Enter The Phone Number: ");
    scanf("%s",Phone);
    if(strlen(Phone) > 20){
        ErrorAndRestart("!!!!Phone Length Error!!!!");
        return;
    }
    if(AlreadyExists(Phone,'p') == 1){
        ErrorAndRestart("!!!!Phone Number Already Exists!!!");
        return;
    }
    printf("\n*Email should be unique and maximum 30 characters long.\n");
    printf("Enter The Email: ");
    scanf("%s",Email);
    if(strlen(Email) > 30){
        ErrorAndRestart("!!!!Email Length Error!!!!");
        return;
    }
    if(AlreadyExists(Email,'e') == 1){
        ErrorAndRestart("!!!!Email Already Exists!!!");
        return;
    }
    strcat(NewUSER,Name);
    strcat(NewUSER,"\n");
    strcat(NewUSER,Phone);
    strcat(NewUSER,"\n");
    strcat(NewUSER,Email);
    strcat(NewUSER,"\n");

    FILE *allUSERTxtFile = fopen("result.txt","a"); // create file and open in append mood
    fprintf(allUSERTxtFile,NewUSER); // store USER in file
    fclose(allUSERTxtFile); // close the file
    printf("\nUSER Added Successfully!\n");
    GoBackOrExit();
}

void ShowAllUSERs(){
    system("cls");
    printf("\n\t\t **** All USERs ****\n\n");
    FILE* AllUSERTextFile;
    int LineLength = 300;
    char Line[LineLength];

    printf("|====================|====================|==============================|\n");
    printf("|        Name        |    Phone Number    |          Email               |\n");
    printf("|====================|====================|==============================|\n");

    AllUSERTextFile = fopen("result.txt", "r");
    int TotalUSER = 0;
    int LineCount = 0;
    while(fgets(Line, LineLength, AllUSERTextFile)) {
        LineCount++;
        if(LineCount==1){
            // name
            PrintLineWithSpace(Line,'n');
        }else if(LineCount == 2){
            // phone
           PrintLineWithSpace(Line,'p');
        }else if(LineCount == 3){
            // email
            PrintLineWithSpace(Line,'e');
            LineCount=0;
            TotalUSER++;
        }
    }
    printf("You Have Total %d USERs.\n\n",TotalUSER);
    fclose(AllUSERTextFile);
    GoBackOrExit();
}

void PrintLineWithSpace(char *Name[20],char USERInfo){
    int i;
    char *FormatedName = NULL;
    FormatedName = strdup(Name);
    int FormatedNameLenght = strlen(FormatedName);

    int TotalSpace = 0;
    if(USERInfo == 'n'){
        TotalSpace = 20 - FormatedNameLenght; // name
    }else if(USERInfo == 'p'){
        TotalSpace = 20 - FormatedNameLenght; // phone
    }else if(USERInfo == 'e'){
        TotalSpace = 30 - FormatedNameLenght; // email
    }

    printf("|");
    for(i=0;i<FormatedNameLenght-1;i++){
        printf("%c",FormatedName[i]);
    }

    for(i=0;i<=TotalSpace;i++){
        printf(" ");
    }

    if(USERInfo == 'e'){
        printf("|\n");
        printf("|--------------------|--------------------|------------------------------|\n");
    }
}

void SearchUSER(){
    system("cls");
    printf("\n\t\t **** Search USER ****\n\n");

    int FoundUSER = 0;
    char Name[100];
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name: ");
    scanf(" %[^\n]s",Name);
    if(strlen(Name) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }
    strcat(Name,"\n");

    FILE* AllUSERFile;
    int LineLength = 255;
    char Line[LineLength];
    AllUSERFile = fopen("result.txt", "r");
    int LineCount = 0;
    int NeedToPrintLine = 0;
    while(fgets(Line, LineLength, AllUSERFile)) {
       LineCount++;
        if(LineCount == 1 && strcmp(Name, Line) == 0){
            FoundUSER = 1;
            NeedToPrintLine = 3;
        }
        if(NeedToPrintLine > 0){
            if(LineCount==1){
                printf("\nUSER information of %s",Name);
                printf("\nName: %s",Line);
                NeedToPrintLine = 2;
            }else if(LineCount == 2){
                printf("Phone: %s",Line);
                NeedToPrintLine = 1;
            }else if(LineCount == 3){
                printf("Email: %s\n",Line);
                NeedToPrintLine = 0;
            }
        }
        if(LineCount == 3){
            LineCount=0;
        }
    }
    fclose(AllUSERFile);
    if(FoundUSER == 0){
        printf("\nSorry no USER found for %s\n",Name);
    }
    GoBackOrExit();
}

void EditUSER(){
    system("cls");
    printf("\n\t\t **** Edit USER ****\n\n");

    int LineCount = 0;
    int FoundUSER = 0;
    int SkipLines = 0;
    char GivenName[100];
    char NewName[100];
    char NewPhone[20];
    char NewEmail[100];
    char NewFullUSER[300];
    NewFullUSER[0] = 0;
    printf("*Name should be maximum 20 characters long.\n");
    printf("Enter The Name which one you want to edit: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
        return;
    }

    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLength = 255;
    char Line[LineLength];
    OurExistingFile = fopen("result.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(Line, LineLength, OurExistingFile)) {
        LineCount++;

        if(LineCount == 1 && strcmp(GivenName, Line) == 0){
            // we found the USER
            FoundUSER = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            if(LineCount == 1){
                printf("\n*New Name should be unique and maximum 20 characters long.\n");
                printf("Old Name is: %s",Line);
                printf("New Name(0 for skip): ");
                scanf(" %[^\n]s",NewName);
                if(strcmp(NewName, "0") == 0){
                    strcat(NewFullUSER,Line);
                }else{
                    if(strlen(NewName) > 20){
                        ErrorAndRestart("!!!!Name Length Error!!!");
                        return;
                    }
                    if(AlreadyExists(NewName,'n') == 1){
                        ErrorAndRestart("!!!!Name Already Exists!!!");
                        return;
                    }
                    strcat(NewFullUSER,NewName);
                    strcat(NewFullUSER,"\n");
                }
                SkipLines = 2;
            }else if(LineCount == 2){
                printf("\n*New Phone should be unique and maximum 20 characters long.\n");
                printf("Old Phone is: %s",Line);
                printf("New Phone(0 for skip): ");
                scanf("%s",NewPhone);
                if(strcmp(NewPhone, "0") == 0){
                    strcat(NewFullUSER,Line);
                }else{
                    if(strlen(NewPhone) > 20){
                        ErrorAndRestart("!!!!Phone Length Error!!!");
                        return;
                    }
                    if(AlreadyExists(NewPhone,'p') == 1){
                        ErrorAndRestart("!!!!Phone Already Exists!!!");
                        return;
                    }
                    strcat(NewFullUSER,NewPhone);
                    strcat(NewFullUSER,"\n");
                }
                SkipLines = 1;
            }else if(LineCount == 3){
                printf("\n*New Email should be unique and maximum 30 characters long.\n");
                printf("Old Email is: %s",Line);
                printf("New Email(0 for skip): ");
                scanf("%s",NewEmail);

                if(strcmp(NewEmail, "0") == 0){
                    strcat(NewFullUSER,Line);
                }else{
                    if(strlen(NewEmail) > 30){
                        ErrorAndRestart("!!!!Email Length Error!!!");
                        return;
                    }
                    if(AlreadyExists(NewEmail,'e') == 1){
                        ErrorAndRestart("!!!!Email Already Exists!!!");
                        return;
                    }
                    strcat(NewFullUSER,NewEmail);
                    strcat(NewFullUSER,"\n");
                }
                SkipLines = 0;
                fprintf(NewTempFile,NewFullUSER);
            }
        }else{
            fprintf(NewTempFile,Line);
        }

        if(LineCount == 3){
            LineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundUSER == 0){
        printf("USER Not Found!\n");
        remove("temp-file.txt");
    }else{
        printf("\nUSER Updated Successfully!\n\n");
        remove("result.txt");
        rename("temp-file.txt", "result.txt");
    }
    GoBackOrExit();
}

void DeleteUSER(){

    system("cls");
    printf("\n\t\t **** Delete USER ****\n\n");

    int lineCount = 0;
    int FoundTheUSER = 0;
    int SkipLines = 0;
    char GivenName[100];
    printf("\n*Name should be maximum 20 characters long.\n");
    printf("Enter The Name which one you want to delete: ");
    scanf(" %[^\n]s",GivenName);
    if(strlen(GivenName) > 20){
        ErrorAndRestart("!!!!Name Length Error!!!");
    }
    strcat(GivenName,"\n");

    FILE* OurExistingFile;
    FILE* NewTempFile;
    int LineLenght = 300;
    char line[LineLenght];
    OurExistingFile = fopen("result.txt", "r");
    NewTempFile = fopen("temp-file.txt", "w");
    while(fgets(line, LineLenght, OurExistingFile)) {
        lineCount++;

        if(lineCount == 1 && strcmp(GivenName, line) == 0){
            // we found the USER
            FoundTheUSER = 1;
            SkipLines = 3;
        }

        if(SkipLines > 0){
            SkipLines--;
        }else{
            fprintf(NewTempFile,line);
        }

        if(lineCount == 3){
            lineCount = 0;
        }
    }
    fclose(NewTempFile);
    fclose(OurExistingFile);

    if(FoundTheUSER == 0){
        printf("\nUSER Not Found!\n\n");
        remove("temp-file.txt");
    }else{
        printf("\nUSER Deleted Successfully!\n\n");
        remove("result.txt");
        rename("temp-file.txt", "result.txt");
    }
    GoBackOrExit();
}

void DeleteAllUSERs(){
    system("cls");
    printf("\n\t\t **** Delete All The USERs ****\n\n");

    char Option;
    getchar();
    printf("Are you sure want to delete all the USERs? (Y,N)?: ");
    scanf("%c",&Option);
    if(Option=='Y' || Option=='y'){
        int i;
        remove("result.txt");
        FILE *AllUSERTxtFile = fopen("result.txt","a");
        fclose(AllUSERTxtFile);

        char Deleting[100] = "Deleting....";
        for(i=0;i<strlen(Deleting);i++){
            printf("%c",Deleting[i]);
        }
        printf("\nSuccessfully Deleted All USERs!\n\n");

    }
    GoBackOrExit();
}

bool AlreadyExists(char *GivenLine[30],char USERInfo){
    char *ThisLine[35];
    ThisLine[0] = 0;
    strcat(ThisLine,GivenLine);
    strcat(ThisLine,"\n");
    int FileLineNumber = 0;
    if(USERInfo == 'n'){
        FileLineNumber = 1; // name
    }else if(USERInfo == 'p'){
        FileLineNumber = 2; // phone
    }else if(USERInfo == 'e'){
        FileLineNumber = 3; // email
    }


    FILE* AllUSERFile;
    int LineLength = 300;
    char Line[LineLength];
    AllUSERFile = fopen("result.txt", "r");
    int LineCount = 0;
    int TotalUSER = 0;
    int Found = 0;
    while(fgets(Line, LineLength, AllUSERFile)) {
       LineCount++;
        if(LineCount == FileLineNumber && strcmp(ThisLine, Line) == 0){
            Found = 1;
        }
        if(LineCount == 3){
            LineCount = 0;
        }
    }
    fclose(AllUSERFile);
    if(Found == 1){
        return true;
    }else{
        return false;
    }
}

void ErrorAndRestart(char *error[100]){
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0;i<10;i++){
        printf(".");
    }
    system("cls");
    main();
}

void GoBackOrExit(){
    char option;
    getchar();
    printf("Go Back(b)? or Exit(0)?");
    scanf("%c",&option);
    if(option=='0'){
        Exit();
    }else{
        system("cls");
    }
}




void Exit(){
    getchar();
    printf("Are You Sure Want to Exit? (Y,N): ");
    char YesOrNO;
    scanf("%c",&YesOrNO);
    if(YesOrNO == 'Y' || YesOrNO == 'y'){
        system("cls");
        printf("Visit www.CodeCartBd.com for more.\n");
        printf("Visit www.insideTheDiv.com for more.\n");

        char ThankYou[100] = "=====Thank You=====\n";
        char SeeYouSoon[100] = "=====See You Soon=====\n";
        int i=0;
        for(i=0;i<strlen(ThankYou);i++){
            printf("%c",ThankYou[i]);
        }
        for(i=0;i<strlen(SeeYouSoon);i++){
            printf("%c",SeeYouSoon[i]);
        }
        isRunning =  false;
    }
}