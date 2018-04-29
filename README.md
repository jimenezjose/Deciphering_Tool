# Deciphering Tool
## Inspired by _Ghost In The Wires_ by Kevin Mitnick

At the beginning of every chapter of _Ghost in the Wires_, Mitnick proposes a cipher underneath the chapter header. 
This program is intended to be a tool to crack such ciphers; providing information such as character frequency, 
word count (if the cipher contains space characters), and alphabet shifts to crack Ceasar Ciphers. Currently I am working
on identifying reccurring patterns characters in the cipher.

### How to Compile

Assumming that the project is downloaded on your home directory. 
On your terminal change to the Deciphering_Tool directory ("cd ~/Deciphering_Tool") and enter the command "make". "make"  executes the first target in the makefile if all dependencies are up to date. 

## How to Run the Program

After you have successfully compiled, a file named "Decipher" will be created (this is the executable file). To run the program, enter the command "./Decipher".  
