#!/bin/ksh
USAGE="usage: lab1"
IFS=""

param="null"

get_parameter() {
    echo $1
    read param
}

name_dir() {
    if /bin/pwd 2>>$HOME/lab1_err 1>/dev/null
    then
	/bin/pwd | awk -F"/" '{
            if($(NF)=="") print $0;
            else print $(NF);
        }'
    else
	echo "Failed to show a directory name" >&2
    fi
}

ls_dir() {
    ls . 2>>$HOME/lab1_err || echo "Failed to show the contents" >&2
}

print_time() {
    LANG=en_US.UTF-8
    export LANG
    
    date '+%a %h %e %H:%M %Z %Y' 2>>$HOME/lab1_err || echo "Failed to show a time" >&2
}

cat_file() {
    get_parameter "Enter a file name"
    name=$param

    cat -- "$name" 2>>$HOME/lab1_err || echo "Failed to show a file" >&2
}

remove_file() {
    get_parameter "Enter a file name"
    name=$param
    echo "Are you sure? (yes/no)"
    read res
    case $res in
	yes) #$name=$(echo $name | sed 's|^ $|./\ |')
             (rm -- "$name" 2>>$HOME/lab1_err && echo "Removed file: $name") || echo "Failed to delete file" >&2 ;;
        no) echo "Canceled" ;;
        *) echo "Unknown choice" ;;
    esac
}

quit_script() {
    exit 0
}

show_menu() {
    echo "1. Current directory name"
    echo "2. Working directory contents"
    echo "3. Current time"
    echo "4. View a file"
    echo "5. Remove a file"
    echo "6. Quit"
    echo "Please, select an item:"
}


echo "(^D to exit)"
show_menu

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
    show_menu
done

