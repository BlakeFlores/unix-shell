
The following is a guide on how the code will run:

Before running, compile the source code using the attached makefile

 1. On program execution, the command prompt will appear and wait for user input
 2. The user will input commands into the command prompt
 	-	If there is a syntax error or if there is an invalid command, the command prompt will nor run and display "exec failed"
 	-	Otherwise, the command(s) will be ran. A list of valid command is available in /usr/bin. Examples of commands that could be ran include:
 		- echo [arg]: display [arg] in the commands prompt
 		- ls: display the content of the current folder
 		- mkdir [arg]: create a directory named [arg] in the current directory
 	-	The command prompt will support connectors such as ||, &&, and ;. This will allow users to enter multiple commands on a single line and to provide a simple and/or functionality.
 3. A special exit command has been created to exit the shell. Once the exit command has been entered, the command shell will be exited.
 4. The input redirection operator '<' accepts input from its right hand operator and sends it to its left hand operator. 
 5. The output redirection operator '> and >>' sends an output from its left hand operator to its right hand operator. The '>>' appends to the file or creates one if it does not exist while the '>' operator will always create the file and write to it, whether or not the file already exists.
 6. The piping operator '|' feeds the input from the left side and sends it to the right hand side which will simulate as if a user had inputted what was on the left side.

# Current Bugs

* Connectors do not function properly:
```javascript
$ echo A && echo B || echo C && echo D; exit
$A
B
```

*Quotes do not work correctly due to the new code changes
