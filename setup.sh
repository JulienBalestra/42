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

function is_dir
{    
    if [ ! -d moulitest ]
    then
        return 0
    fi
    return 1
}

function setup_moulitest
{
    echo "Setup moulitest..."
    if [ ! -d moulitest ]
    then        
        git clone https://github.com/jbalestra/moulitest.git moulitest
        if [ $? -ne 0 ]
        then
            echo "can't use git"
            exit 2
        fi
    else
        echo "-> Already downloaded"
    fi
}

function create_config
{
    echo "Check config..."
    path=$(pwd)
    mv moulitest/config.ini moulitest/config.ini.old 2> /dev/null
    while read line
    do
        output=${line/"@"/$path/}
        echo $output >> moulitest/config.ini
    done < requirements/moulitest.config
    echo "-> Config set"
}

function run_test
{
    echo "Start unittesting..."
    path=$(pwd)
    echo "libft :"
    python  $path/tests/test_libft.py
    return $?
}

function main
{
    # Requirements
    go_to_dirname
    setup_moulitest
    create_config
    run_test
    return $?
}

main
exit $?
