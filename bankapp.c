 /*
 Program to implement bankapp
 ****************************************************************
 Author       Dept.           Date            Noted
 ****************************************************************
 Gregory P    Software Eng.   MAR 10 2020     Initial version
 Gregory P    Software Eng.   MAR 11 2020     Missing deposit and withdrawn
 Gregory P    Software Eng.   MAR 12 2020     Code working
 **************************************************************** 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// this function verifies that no other account exists with the account number we want to add
int accountverification(char *accnum){
        FILE *q = fopen("bankdata.csv", "a+");
	char str[1024];
        while(!feof(q)){
                        fgets(str, 1024, q);
			if(feof(q)) break;  
                        const char s[2] = ",";
                        char *token;
                        token = strtok(str, s);
                        token = strtok(NULL, s);
                        if (strcmp(token, accnum) == 0){ //verifies that accnumber doesn't exist  
                              	fprintf(stderr, "Error, account number %s already exists\n", accnum);
                                fclose(q);    
                                exit(50);
                        }
                }
	fclose(q);
	return 0;
}

// accountexist verifies that an account does exist with the account number we entered
int accountexist(char *accnum){
        FILE *q = fopen("bankdata.csv", "a+");
        char str[1024];
        while(!feof(q)){
                       	fgets(str, 1024, q);
			if(feof(q)) break;
	                const char s[2] = ",";
                        char *token; 
			token = strtok(str, s);
                        token = strtok(NULL, s);
                        if (strcmp(token, accnum) == 0){ //verifies that accnumber doesn't exist        
                                fclose(q);
				return 0;       
			}
                }
	fprintf(stderr, "Error, account number %s does not exist\n", accnum);
        fclose(q);
	exit(50);
        return 0;
}

// Append new account to csv file 
int addAccount(char *accnum, char *name){
        FILE *q = fopen("bankdata.csv", "a+");
	char fname[30];
        strcpy(fname, name);
        fprintf(q, "%s,%d,%s\n", "AC", atoi(accnum), fname);
	fclose(q);
	return 0;
}

// deposits fund to the account
int deposit(char *accnum, char *date, char *amt){
	FILE *q = fopen("bankdata.csv", "a+");
	double amount = strtod(amt, NULL);
	fprintf(q, "%s,%d,%s,%.2f\n", "TX", atoi(accnum), date, amount);  
	fclose(q);
	return 0;
	}

// withdraws funds from the account
int withdraw(char *accnum, char *date, char *amt){
	FILE *q = fopen("bankdata.csv", "a+");
	double amount = strtod(amt, NULL);   
	fprintf(q, "%s,%d,%s,-%.2f\n", "TX", atoi(accnum), date, amount);	
	fclose(q);
	return 0;
	}

int hasfunds(char *accnum, char *amt){
        FILE *q = fopen("bankdata.csv", "a+");
        char str[1024];
	double balance = 0;
	double amount;
	amount = strtod(amt, NULL);
	while(!feof(q)){   
		fgets(str, 1024, q);
		if(feof(q)) break; 
		const char s[2] = ",";
                        char *token;
			token = strtok(str, s);
                        if (strcmp(token, "TX") == 0){ //verifies that entry is a transaction
	                	token = strtok(NULL, s);
				if (strcmp(token, accnum) == 0) {
					token = strtok(NULL, s);
					token = strtok(NULL, s);
					double val;
					val = strtod(token, NULL);
					balance = balance + val;
				}
			}		
	}
	if (amount > balance){
		fprintf(stderr, "Error, account number %s has only %.2f\n", accnum, balance);
		fclose(q);
		exit(60);
		return 0;
	}	
	fclose(q);
	return 0;  	
}

int main(int argc, char *argv[]){
	
	// if-statement that checks if first arg is a valid option
	if (argc < 2 || ((strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-d") != 0 && strcmp(argv[1], "-w") != 0))){
		fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
		exit(1);
	}

        // conditional that checks whether csv file is present in current directory
        FILE *q = fopen("bankdata.csv", "r");
        if(q == NULL){
                fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
                exit(100);
        }
        fclose(q);

	// 3 if-statements to check whether the appropriate number of args present when option is valid
	if (strcmp(argv[1], "-a") == 0 && argc != 4){
		fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n");
		exit(1);
	}
        if (strcmp(argv[1], "-d") == 0 && argc != 5){
                fprintf(stderr, "Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n");
                exit(1);
        }
        if (strcmp(argv[1], "-w") == 0 && argc != 5){
                fprintf(stderr, "Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n");
            	exit(1);
        }

	if (strcmp(argv[1], "-a") == 0){ // For new accoutns
		accountverification(argv[2]); // Verifies account doesn't exist
		addAccount(argv[2], argv[3]); // Adds the new account
	}
	if (strcmp(argv[1], "-d") == 0){ // To make a deposit
		accountexist(argv[2]); 
		deposit(argv[2], argv[3], argv[4]); // deposits funds to accoutn
	}
	if (strcmp(argv[1], "-w") == 0){ // To withdraw funds from accoutn
		accountexist(argv[2]);
		hasfunds(argv[2], argv[4]); 
		withdraw(argv[2], argv[3], argv[4]); // withdraw funds from account
	}

	return 0;
}

