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

function config_moulitest
{
    mv moulitest/config.ini moulitest/config.ini.old 2> /dev/null
    while read line
    do
        output=${line/"@"/$path/}
        echo $output >> moulitest/config.ini
    done < requirements/moulitest.config

}

function config_pip
{
    source env/bin/activate
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
    export LC_ALL=C
    echo "-> Config set"
}

function run_test
{
    declare -i ret=0
    cd tests
    echo "Start unittesting on "$(uname -s)
    echo ""
    echo "[libft]"
    nosetests test_libft.py
    ret=($?+ret)
    echo "[/libft]"
    echo ""
    echo "[get next line]"
    nosetests test_gnl.py
    ret=($?+ret)
    echo "[/get next line]"
    echo ""
    echo "[ls]"
    nosetests test_ls.py
    ret=($?+ret)
    echo "[/ls]"
    echo ""
    echo "[computorv1]"
    nosetests test_computorv1.py test_sample.py
    ret=($?+ret)
    echo "[/computorv1]"
    echo ""
    echo "[libftASM]"
    nosetests test_libftasm.py
    ret=($?+ret)
    echo "[/libftASM]"
    echo ""
    echo "Again, full stack"
    nosetests test_libft.py test_gnl.py test_ls.py test_computorv1.py test_sample.py test_libftasm.py
    ret=($?+ret)
    return $ret
}

function main
{
    # Requirements
    go_to_dirname
    path=$(pwd)
    setup_moulitest
    create_config
    run_test
    return $?
}

main
exit $?
