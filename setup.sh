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

function create_config
{
    echo "Check config..."
    config_pip
    config_moulitest
    export LC_ALL=C    
    echo "-> Config set"
}

function run_test
{
    cd tests
    echo "Start unittesting on "$(uname -s)
    echo ""
    echo "[libft]"
    nosetests test_libft.py
    echo "[/libft]"
    echo ""
    echo "[get next line]"
    nosetests test_gnl.py
    echo "[/get next line]"
    echo ""
    echo "[ls]"
    nosetests test_ls.py
    echo "[/ls]"
    echo ""
    echo "[computorv1]"
    nosetests test_computorv1.py test_solver.py
    echo "[/computorv1]"
    echo ""
    return $?
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
