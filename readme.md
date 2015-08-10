[![Build Status](https://travis-ci.org/JulienBalestra/42.svg?branch=master)](https://travis-ci.org/julienbalestra/42)

# 42 

Programming School


### Tavis CI
 
* libft
* get next line
* ls-Darwin
* ls-Linux
* computorv1
* libftASM

With more than **370 unit & functional tests**


Coding guidelines about the projects are available in ***subjects/*** root directory

## C

* Libft (108%)
* Get_Next_Line (111%)
* ft_ls (117%)


## Python

* Computor V1 (125%)


## Assembly

* LibftASM (current)


# Run everything

### Linux 

If needed, a virtualenv:

    sudo apt-get update -qq && sudo apt-get install python-virtualenv
    virtualenv env
    
Then if you are sudo (like I am in Travis containers):

    ./setup.sh
    ./run_tests.sh
    
Or find a way to have in $PATH:

* nosetests
* nasm
