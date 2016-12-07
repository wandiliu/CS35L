#Word Problems 

The short answer section of the practice exam.

####1. What's the difference between ```sed``` and ```grep```? 
-      sed edits/replaces
-      grep finds 

####2.1 What does the following script print out? (Prob2.txt)
```
#!/bin/grep is
this
is
```
*Note*: If the bash prompt errors out to `-bash: ./Prob2.txt: /bin/grep: bad interpreter: No such file or directory`, try to run the code on the linux server

####2.2 What about ```#! /usr/bin/env python```?

Correct output: 
```
SyntaxError: invalid syntax
```

**Explanation**: Python has a different syntax, you at least need to call the main function to execute

####3. What's a symbolic link (soft link), and how is it different from a non-symbolic (hard) link? 
-      A symbolic link contains the name(reference) of the file it's pointing to
-      A hard link's file has the same inode as the original file, therefore it's the same data block on the hard drive and doesn't waste space!

####4. When you don't know how to do something in Linux, what should you do first?
-      use ```man``` to look at manuals for commands
-      use ```apropos``` to search for commands whose descriptions contain a certain keyword
-      use ```whatis``` to search for commands whose **names** contain a certain keyword/phrase

####5. What's stored on a thread's (or process' for single-threaded applications) **stack**?
-      Local variables/buffers
-      Function arguments
-      return addresses
-      old base pointers

####5.1 What is buffer overflow?
In short, a buffer overflow is caused by the manipulation of a computer's memory to control program execution. They're mainly **stack based** or **heap based**.
Some languages, such as C and C++, are prone to buffer overflows as they have no built-in protection against accessing or overwriting data.
-    A buffer overflow happens when 
     1.	       A program (malicious) attempts to put more data (take up more memory) than the buffer is supposed to hold
     2.	        A program attempts to put the data in a memory area (what's set aside for the function) that's past the buffer
     -		 This can crash the program, corrupt data, or cause the execution of malicious code
-    It's a **software security vulnerability**
-    In a classic buffer overflow, the call stack is overwritten and the function's return pointer is set to transfer control to malicious code when it returns
-    Buffer overflow typically happens in 
     1.     External Data: Programs that relies on external data to control its behavior
     2.     Program that depends on the properties of data that's external to the scope of the code
     3.     Programs that're overly complex, whose behavior the programmer cannot actually predict

####6. As part of a class project you and a partner share access to an svn repository hosted on the class server. One night, without your knowledge, your partner adds a backdoor (a secret piece of code allowing remote control of the project) to the project repository. However, you do not realize this until after the project is turned in. How can you show (with reasonable certainty) that you did not add the back door to the project? List the specific commands you would use and what useful information they would provide.

Because it's not a distributed version control system, we can use ```svn log``` which shows you the author information of the commit 

####7. In 2009 an attack on SSL (Secure Socket Layer) Certificates was published online that allowed spoofing of domain names. This attack allowed a malicious site to publish valid security certificates which appeared to be for a different site. For example, www.goodsite.com.evilsite.com (a subdomain of evilsite.com) would claim to be www.goodsite.com by having a non-printable null character (“www.goodsite.com\0.evilsite.com”) in its name. Given that every domain name is exactly 32 characters (with null byes on the end when less than 32 characters are used), eliminate this spoofing vulnerability from the following function:
```c
/* Returns 0 when the certificate is valid for the site and non-zero otherwise*/ int isValidForSite(char* domainName, char* certificateDomainName)
{
return strcmp(domainName, certificateDomainName);
}
```
**Answer**:
```c
#include <stdio.h>

int isValidForSite(char* domainName, char* certificateDomainName)
{
for (int i = 0; i < 32; i++){
    if (*(domainName+i)==*(certificateDomainName+i)){
      continue;
    }
    if (*(certificateDomainName+i)=='\0')
      {
      if (*(domainName+i) != '\0'){
        return 1;
	}
	else {
	  continue;
      }
    }
}
 return 0;
}
```
####8. SSH is a widely used network protocol that allows for secure (in most typical situations) communication between two systems. SSH allows for both Public Key (where a client's public key is stored on the host) and Password based authentication which you saw in Lab 7. List a set of circumstances where Public Key authentication would be the most secure method and a set of circumstances where Password based authenticated would be the most secure.
Let's answer this by contradiction. Assuming that we have someone recording our keystrokes, they could easily access our ssh key. Therefore, we probably would want to use a Public Key. If we have someone who's capable of accessing our .ssh folder, then we want to have a password authentication step as a final layer.

####9. which of the following bash commands would be most appropriate to compile a project and print one line summary of the build status? Justify your answer by critiquing all three commands.

a. make || echo “Build failed!” && echo “Build succeeded”
-  This command will compile the project, then regardless of its output, output both "Build failed!" and "Build succeeded". This is pretty bad because it doesn't give us the correct build status.

**b. make && echo “Build Succeeded” || echo “Build failed!”**
-  This command first try to execute the project, then if it was successful, it will output the left `echo` statment, which is bundled together with `make` through an `&&` condition. If make was unsuccessful, the bundle in its entirety would not execute, which means the right echo statement, which is also the other `||` option, will be outputted.

c. make || echo “Build succeeded” && echo “Build failed!”
-  This command will try the execute the project. If it succeeds, the other half of the `||` will not execute, which means that we will get no status of "successful compilation". What's worse is that if the program failed to `make`, the command will output *both* “Build succeeded” **and **  “Build failed!”...***terrible***

####10. Write a     command that replaced every phone number in ./contact.html with its digit-only form. The format to consider is (ddd)-ddd-dddd. For example, (555)-555-5555 becomes 5555555555. Ignore phone numbers formatted incorrectly (for example, too many digits).
To do this we need to have basic knowledge of ```sed``` (edit command) and Regex expressions. We want to remove the '(', ')', and '-' characters, and keep all the numerals. We have two options - create a filter for only numerals, or remove all the non-numeric characters.
   1. To remove all the non-numeric characters, we specify then in square brackets `[]`:
```
$ sed 's/[()-]//g'
``` 
   2.	To specify for only numerals, we use \1 to \9.

####11. You have a file called one_mb which is exactly 1 megabyte in size. You want to create from it a file of exactly 128 megabytes in size. Please write a shell script to do this with at most 9 lines and no loops, if statements, recursion, or any other logic control structures. Each command, including parameters, must be less than 100 characters in length. (max 9 lines)
```
#!/bin/bash
file="$1"
newfile="$2"
cat $file $file > $newfile
cat $newfile $newfile > $file
cat $file $file > $newfile
cat $newfile $newfile > $file
cat $file $file > $newfile
cat $newfile $newfile > $file
cat $file $file > $newfile
```

#####NOTE:
	1.	Bash scripts should begin with #!/bin/bash
	2.	files are fed in as arguments, where $0 is the script itself, $1 is the first argument, and so on
	3.	for cat, > is replacing all previous content, while >> appends to previous content
	4.	Remember to deference using $
	5.	To try this out yourself, execute the following in your shell:
	
```sh
$ chmod +x Prob11.txt #give the file execution rights
$ ls -l #to see that 128_mb.txt is currently 0 bytes, and one_mb.txt is one byte
$ ./Prob11.txt one_mb.txt 128_mb.txt #execute the script with the above files as arguments
$ ls -l #check the files again, this time, 128_mb.txt should be 128 bytes! 
```
####12a. Make a class Point 3 that represents a 3-dimensional point. A constructor is optional, but yo\
u must implement the function distance2(...) that will compute the distance squared (e.g. (x_1 - x_2)^\
2 + (y_1-y_2)^2 + (z_1-z_2)T between the current point and given point and return it.

Solution:
```py
#!/usr/bin/env python
import os 
import sys

class Point3:
    def __init__(self, x, y, z):
        self.x = x;
        self.y = y;
        self.z = z;    
    def distance2(self, p2):
        return (self.x - p2.x)**2 + (self.y - p2.y)**2 + (self.z - p2.z)**2
```

####12b. We'll come back to this

####12c. We'll come back to this too

####13. The following C function counts the number of unique positive integer divisors given a number n has (not including 1 or n). For example, if the number 12 is given the function will return 4 since 12 can be divided by 21, 3, 4, and 5. speed up this function by parallelizing it and doing all work in 3 child threads. Use pthread_create and pthread_join to manage your threads. You may add additional functions and global variables if needed. Do not attempt to improve the algorithm (i.e. still use exhaustive search). You may assume that all operations are atomic, meaning you can perform operations such as g_divisorCount__ without worrying about synchronization.
[code omitted]
Write your new function(s) below:

Solution:
Not sure because the function wasn't posted :( BUT because we know that we need 3 child threads, we'll simply divide up the testing algorithm (call that foo, whatever it is), which probably looks at all the numbers from 1 to the number itself, and seeing if original_num%factor_num == 0. So, we will need a function that takes in, we'll call it ```void *foo(int *obj)```, and the original function ```main()```.
``` 
void * foo (void * obj) //obj will store the 
{
int partition = *(int *) obj;
//some code here;
for (int i = partition; i < original_num; i += nthreads){
//original algorithm here;
}
}

int main (int argc, char **argv){

    //set up the threads;
    nthreads = 4;
    pthread_t thread_id[nthreads];
    int *gaps = malloc(sizeof(int)*nthreads);
    for (int i = 0; i < nthreads; i++){
    gaps[i] = i;
    int ret = pthread_create(&thread_id[i], NULL, run, (void*)(gaps+i));
    if (ret){
       fprint(stderr, "Not able to create new thread");
       }
    }
    for (int i = 0; i < nthreads; i++){
    	pthread_join(thread_id[i]; NULL);
    } 
}
```

####14. Given the following buggy C program to compute factorials (main.c):
```
#include ,stdio.h>
int factorial(int n) {
return n* factorial (n-1); }
```
[Rest of code omitted]
And the following patch to correct the buggy program (called fix.patch): [patch omitted]
Notice the typo of “Fractorial” on line 29 on the patch which should be “Factorial”> Please make a patch that can be applied to “fix.patch” and fix the typo (you do not need to use all lines) on the next page.

Solution:
```
#include <stdio.h>

int factorial(int n) {
if (n > 1){
   return n* factorial (n-1); 
}
else{
	return 1; //base case
}
}
```
#####How to apply a patch:
diff –u original_file modified_file

--- path/to/original_file

+++ path/to/modified_file

@@ -l,s +l,s @@
–    @@: beginning of a hunk
–    l: beginning line number
–    s: number of lines the change hunk applies to for each file
–    A line with a:
  - sign was deleted from the original 
  + sign was added to the original
  else: stayed the same 