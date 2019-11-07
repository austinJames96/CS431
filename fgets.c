// Interactive Shell Program
// Austin Sypolt
// CS431
// 10/7/19

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <sys/wait.h> 

#define MAX 50
#define MaxStringSize 50

int n = 0;

int main() 
{ 
    printf("\n\nWelcome to the Interactive Shell Program!\n");
    printf("If you need a list of usable command please type 'help'.\n\n");
    char buf[MAX]; 
    fgets(buf, MAX, stdin);  
    

    int check = 0;
    checkCd(buf);
    echoMessage(buf);
    exitProgram(buf);
    helpFunc(buf);
    setPrompt(buf);
    
    while(n == 0){
        char str[1];
        printf("Do you wish to enter another command? (Y/N)\n");
        fgets(str, MAX, stdin);
        if(str[0] == 'N' ||  str[0] == 'n'){
            printf("Exiting Program\n");
            break;
            exit(0);
        }
        fgets(buf, MAX, stdin); 
     

        int check = 0;
        checkCd(buf);
        echoMessage(buf);
        exitProgram(buf);
        helpFunc(buf);
        setPrompt(buf);
    }

    return 0; 
} 

int checkCd(char buf[]){
    if(buf[0] == 'c' && buf[1] == 'd'){
            for(int i = 2; i<sizeof(buf); i++){
                //char dest[20] = "";
                //strcat(dest, buf[i]);
                //printf("%c\n", dest);
                //chdir(buf[3 + i]);
            }
    }
}

int echoMessage(char buf[]){
    if(buf[0] == 'e' && buf[1] == 'c' && buf[2] == 'h' && buf[3]  == 'o'){
        for (int i = 0; i < sizeof(buf); i++){
            printf("%c",buf[5+i]);
        }
        printf("\n\n");
    }
}

int exitProgram(char buf[]){
    if(buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3]  == 't'){
        printf("Exiting Program\n");
        exit(0);
    }
}

int helpFunc(char buf[]){
    if(buf[0] == 'h' && buf[1] == 'e' && buf[2] == 'l' && buf[3]  == 'p'){
        printf("\n\n***** Welcome to the help menu *****\n");
        printf("*****    List of commands      *****\n");
        printf("cd : Change directory (cd *dirname*)\n");
        printf("echo : Display message in prompt (echo *message*)\n");
        printf("exit : Exit the program\n");
        printf("set : Set shell variables (set PROMPT *promptName*)\n\n");
    }
}

int setPrompt(char buf[]){
    if(buf[0] == 's' && buf[1] == 'e' && buf[2] == 't'){
        char tempChar[sizeof(buf)-3];
        for (int i = 0; i < sizeof(buf); i++){
            tempChar[i] = buf[4+i];

            printf("%c :",tempChar[i]);
        }
    }
}

int continuePrompt(int n){
    char str[10];
    printf("Do you wish to enter another command? (Y/N)\n");
    fgets(str, MAX, stdin);
    if(str == 'y' || 'Y' || "Yes" || "yes"){
        printf("Repeat\n");
        n = 0;
    }
    else{
        n++;
    }
}