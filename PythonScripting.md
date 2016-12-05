##Python Notes & Demos

####CS35L Lab Questions
1. Evoking scripts on empty files
2. Difference between Python 2 and Python 3
3. ```string``` and ```locale``` modules


###PROS OF PYTHON
- more structure and support for programs than shell
- more error checking than C, being a **high level language**
- more *built-in high level data structures* (dictionaries, flexible arrays) than C
- more general data types, open to larger problem domain than Awk or Perl
- code can be split up into Python *modules* and reused in other programs
- comes with standard modules (ie. system calls, sockets, and I/O)
- **interpreted language**: saves time during development
  - does not need compilation or linking
  - interactive interpreter allows function testing in bottom-up development
- *saves space* - perform tasks with shorter code
  - built-in data structures
  - indentation instead of brackets for statements
  - no function or variable declaration needed 
- **extensible**: new built-in functions and modules can be added to the interpreter
  - critical operations can be performed at maximal speed
  - python programs can be linked to libraries that are only available in binary
  - python interpreter can be linked to applications written in other languages and used as extension or command language 

###THE PYTHON INTERPRETER 
####Invoking the Interpreter

* whereabouts: ```/usr/bin/python``` 
* entering: ```python```
* exiting: ```Ctrl + d```

2 ways:
1. reading & executing commands directly
  * ```python -c "command" [arg] ... ```
    * executes the command
  * ```python -m module [arg] ... ```
    * executes the source code of the module
2. executing a script from a file argument/file standard input 
  * ```python <file``` reads file before execution, program reaches end-of-file immediately
    * input requests are satisfied from ```file```
  * ```python file``` input requests are satisfied by standard inpput from the interpreter 
  
####Passing Arguments
The script name and additional arguments that you want to pass to the script is represented through a list of strings ```[]``` represented by the variable ```sys.argv```. 
* length >= 1
* with no script/arguments, ```sys.argv[0]``` = ""
* with standard input (no script given, script name = "-"), ```sys.argv[0]``` = "-"
* in the case of -c commands and -m modules, ```sys.argv[0]``` is set to c and *module name*, respectively
  * the additional options after -c and -m are **not** processed by the interpreter, but stored by ```sys.argv[0]``` to be handled by the command or module

####Interpreter's Error Handling
An error invokes an **error message** and a **stack trace**
* file input errors causes printing of stack trace & exit with nonzero status 
* interrupt characters:
  * ```Ctrl + c``` or ```DEL```
  * ```KeyboardInterrupt``` exception: caused by typing an interrupt while command is executing, handled by a try statement

####Executables
Like shell scripts, Python scripts can be made directly into an executable by the following line:
```shell
#! /usr/bin/env python
```
Remember to give execution permission to the script with ```chmod```

```bash
chmod +x scipt.py
```

####
