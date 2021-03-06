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
    ./libft/run_test.sh
    ret_libft=$?
    echo "[/libft]"
    return ${ret_libft}
}

function get_next_line
{
    echo "[get next line]"
    cd tests
    nosetests test_gnl.py
    ret_get_next_line=$?
    echo "[/get next line]"
    cd -
    return ${ret_get_next_line}
}

function ft_ls
{
    echo "[ls]"
    cd tests
    nosetests test_ls.py
    ret_ft_ls=$?
    echo "[/ls]"
    cd -
    return ${ret_ft_ls}
}

function computorv1
{
    echo "[computorv1]"
    nosetests computor/srcs/tests/
    ret_computorv1=$?
    echo "[/computorv1]"
    return ${ret_computorv1}
}

function libftASM
{
    echo "[libftASM]"
    nosetests tests/test_libftasm.py
    ret_libftASM=$?
    echo "[/libftASM]"
    return ${ret_libftASM}
}

function minishell
{
    echo "[minishell]"
    ./minishell/run_test.sh
    ret_minishell=$?
    echo "[/minishell]"
    return ${ret_minishell}
}

function 21sh
{
    echo "[21sh]"3
    ./21sh/run_test.sh
    ret_21sh=$?
    echo "[/21sh]"
    return ${ret_21sh}
}

function run_tests
{
    # Locale for /bin/ls implementation (merge sort by ASCII)
    export LC_ALL=C
    
    declare -i code=0
    
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

    minishell
    code=($?+code)

    21sh
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
