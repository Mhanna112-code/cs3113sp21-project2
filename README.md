Marc Hanna



program to read, store and print out unicode characters and their reoccurrences in a text file



example usage: open example.txt, makefile and project0.c in terminal, insert text into "example.txt" file, compile project0.c using the make all rule attached in the makefile, then enter the command cat example.txt | ./project0 to feed stdout of example.txt into stdin of the project0 exectable 
to retest program on different text, modify "example.txt" with updated text, enter make clean to delete old project0 executable then repeat above process



code didn't fully pass all the gradescope tests; probably doesn't correctly print out all possible printable unicode characters
assumed I can use a character pointer pointing to the unsigned character values of unicode bytes and "%s" to print out unicode characters
