#!/bin/ksh

echo "1. Print name of current directory"
echo "2. Print content of working directory"
echo "3. Print current time"
echo "4. Print file"
echo "5. Remove file"
echo "6. Quit"

param="null"

get_parameter() {
    echo $1
    read param
}

item_1() {
    echo input $1
    echo Current directory:
    pwd | awk -F"/" '{print $NF}'
}

item_2() {
    echo Content of working directory:
    ls
}

item_3() {
    LANG=en_US.UTF-8
    export LANG
    echo Current time:

    date '+%a %h %e %H:%M %Z %Y'
}

item_4() {
    get_parameter "Enter a file name"
    name=$param
    echo "name: $name"

    cat $name
}

item_5() {
    get_parameter "Enter a file name"
    name=$param
    echo "File: $name"

    rm "$name"
}

item_6() {
    exit 0
}

#wait input
while read com
do
    case $com in
        1) item_1 "lalal" ;;
        2) item_2 ;;
        3) item_3 ;;
        4) item_4 ;;
        5) item_5 ;;
        6) item_6 ;;
        *) echo error ;;
    esac
done

