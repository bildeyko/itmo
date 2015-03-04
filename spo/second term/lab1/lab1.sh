#!/bin/ksh

param="null"

get_parameter() {
    echo $1
    read param
}

name_dir() {
    echo "Current directory name:"

    pwd | awk -F"/" '{print $NF}'
}

ls_dir() {
    echo "Contents of working directory:"

    ls
}

print_time() {
    LANG=en_US.UTF-8
    export LANG
    echo "Current time:"

    date '+%a %h %e %H:%M %Z %Y'
}

cat_file() {
    get_parameter "Enter a file name"
    name=$param
    echo "Showed file: $param"

    cat $name
}

remove_file() {
    get_parameter "Enter a file name"
    name=$param
    echo "Are you sure? (y/n)"
    read res
    case $res in
	y) echo "Removed file: $name"; rm "$name" ;;
        n) echo "Canceled" ;;
        *) echo "Unknown choice" ;;
    esac
}

quit_script() {
    exit 0
}


echo "(^D to exit)"
echo "1. Print a current directory name"
echo "2. Print contents of working directory"
echo "3. Print current time"
echo "4. View a file"
echo "5. Remove a file"
echo "6. Quit the program"
echo "Please, select an item:"

#wait input
while read com
do
    case $com in
        1) name_dir ;;
        2) ls_dir ;;
        3) print_time ;;
        4) cat_file ;;
        5) remove_file ;;
        6) quit_script ;;
        *) echo "Unknown command" ;;
    esac
    echo ""
    echo "1. Print a current directory name"
    echo "2. Print contents of working directory"
    echo "3. Print current time"
    echo "4. View a file"
    echo "5. Remove a file"
    echo "6. Quit the program"
    echo "Please, select an item:"
done

