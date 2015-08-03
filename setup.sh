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

function config_moulitest
{
    mv moulitest/config.ini moulitest/config.ini.old 2> /dev/null
    while read line
    do
        output=${line/"@"/$path/}
        echo $output >> moulitest/config.ini
    done < requirements/moulitest.config

}

function setup_submodules
{
    echo "Setup git submodules..."
    for module in computor libft libftASM moulitest get_next_line ls_darwin ls_linux
    do
        git submodule init ${module}
        git submodule update --remote ${module}
    done
    for sym in ls_darwin ls_linux
    do 
        ln -s libft ${sym}/libft
    done
}


function config_pip
{
    if [ -d env ]
    then
        source env/bin/activate
    fi
    pip install -r requirements/requirements.txt
    if [ $? -ne 0 ]
    then
        echo "failed to install the requirements"
        exit 2
    fi
}

function config_nasm
{
    nasm -h > /dev/null
    if [ $? -ne 0 ]
    then
        apt-get update -qq
        apt-get install nasm -y
        if [ $? -ne 0 ]
        then
            echo "failed to install nasm"
            exit 2
        fi
    fi
}

function create_config
{
    echo "Check config..."
    config_pip
    config_moulitest
    config_nasm
    echo "-> Config set"
}

function main
{
    # Requirements
    go_to_dirname
    path=$(pwd)
    setup_submodules
    create_config
    return $?
}

main
exit $?
