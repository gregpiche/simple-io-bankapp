# Simple I/O bankapp in C

## Background

This program was developed for an assignment in the course "Introduction to Software Systems" at McGill University. The objective of the project was to develope a bank app that can handle the three basic operations: create an account, deposit funds to an account and withdraw funds from an account. All opereations would be inputed to the command line interface and error message would print on the command line whereas account updates would be made in the `bankdata.csv` file. In the 

To compile the program, ensure that gcc is installed on your device and run `gcc -o bankapp bankapp.c` in the directory where the C source code is located. To view contents of data, execute `cat bankdata.csv`. In the file, entries beginning with `AC` are accounts and entries beginning with `TX` are transactions.

## Commands

For creating an account: `./bankapp -a ACCTNUM 'NAME'`  
e.g. `./bankapp -a 1209 John Doe `<br/><br/>

For depositing funds: `./bankapp -d ACCTNUM DATE AMT`  
e.g. `./bankapp -d 1024 2020-02-12 334.52`<br/><br/>

For withdrawing funds: `./bankapp -w ACCTNUM DATE AMT`  
e.g. `./bankapp -w 1024 2020-02-13 123.02`<br/><br/>

## Error checking

For each command there is error checking to ensure proper use. For all commands, the program ensures that the file exists in the current directory and that the correct number of arguments are used. For creating an account, it checks whether the account number already exists in the system and adds the account if the account doesn't exist. For both depositing funds and withdrawing funds, the program checks to verify that there exists an account with that number. There is an additional check for withdrawing funds to ensure that the account has enough funds to withdrawn the inputted amount. 
