#!/bin/bash

function go_to_dirname
{
    echo "Go to working directory..."
    cd $( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
    if [ $? -ne 0 ]
    then
        echo "go_to_dirname failed";
        exit 1
    fi
    echo "-> Current directory is" $(pwd)
}

function libft
{    
    echo "Start unittesting on "$(uname -s)
    echo ""
    echo "[libft]"
    nosetests test_libft.py
    ret=$?
    echo "[/libft]"
    
}

function get_next_line
{
    echo "[get next line]"
    nosetests test_gnl.py
    ret=$?
    echo "[/get next line]"
    return ${ret}
}

function ft_ls
{
    echo "[ls]"
    nosetests test_ls.py    
    ret=$?
    echo "[/ls]"
    return ${ret}
}

function computorv1
{
    echo "[computorv1]"
    nosetests test_computorv1.py test_sample.py
    ret=$?
    echo "[/computorv1]"
    return ${ret}
}

function libftASM
{
    echo "[libftASM]"
    nosetests test_libftasm.py
    ret=$?
    echo "[/libftASM]"
    return ${ret}
}

function run_tests
{
    declare -i code=0
    cd tests
    
    libft
    code=($?+code)    
    
    get_next_line
    code=($?+code)

    ft_ls
    code=($?+code)
    
    computorv1    
    code=($?+code)
    
    libftASM
    code=($?+code)

    return ${code}
}

function main
{    
    go_to_dirname
    run_tests
    return $?
}

main
exit $?
