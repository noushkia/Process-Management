# Process-Management
This is the second project of OS course offered at the University of Tehran.


# To Execute
Run the following command in the terminal:<br>
    `$ make`<br>
    `$ ./main.out`<br>

Make sure to add .csv test files to /testcases folder.

# Program FLow:
The program starts by executing main process. The main process will find testcase csv files within which there are comma seperated words.

Afterwards, it will execute mapper processes for each file which will map words of a given file and count their occurances in the file allocated to them.

Main will also execute a reducer process which will count total occurances of words in all testcase files. 

This process will use named pipe to recieve words count of each file calculated by mapper processes.

The mapper processes calculate total occurances of each word in a .csv file passed by main process using argv.

Finally, main will write the total occurances of each word passed by reducer process.
