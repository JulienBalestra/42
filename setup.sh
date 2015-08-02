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
        git clone https://github.com/JulienBalestra/moulitest.git moulitest
        if [ $? -ne 0 ]
        then
            echo "can't use git"
            exit 2
        fi
    else
        git -C moulitest pull
    fi
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

function setup_libft
{
    echo "Setup libft..."
    if [ ! -d libft ]
    then        
        git clone https://github.com/JulienBalestra/libft.git libft
        if [ $? -ne 0 ]
        then
            echo "can't use git"
            exit 2
        fi
    else  
        git -C libft pull
    fi
}

function setup_computor
{
    echo "Setup libft..."
    if [ ! -d computor ]
    then        
        git clone https://github.com/JulienBalestra/computor.git computor
        if [ $? -ne 0 ]
        then
            echo "can't use git"
            exit 2
        fi
    else  
        git -C computor pull
    fi
}

function setup_libftASM
{
    echo "Setup libftASM..."
    if [ ! -d libftASM ]
    then        
        git clone https://github.com/JulienBalestra/libftASM.git libftASM
        if [ $? -ne 0 ]
        then
            echo "can't use git"
            exit 2
        fi
    else    
        git -C libftASM pull
    fi
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
    setup_libft
    setup_libftASM
    setup_computor
    setup_moulitest
    create_config
    return $?
}

main
exit $?
