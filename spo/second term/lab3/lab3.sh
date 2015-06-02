#!/bin/ksh
USAGE="usage: lab3 file"

file_name=$1

if [[ -d "$file_name" || -z "$file_name" ]]; then
    echo $USAGE
    exit
fi
if [[ ! -a "$file_name" ]]; then
    echo error: file not found
    echo $USAGE
    exit
fi
if [[ "$file_name" = -* ]]; then
    file_name=./$file_name
fi	

owner_perm=$(ls -lb "$file_name" | cut -c4)
group_perm=$(ls -lb "$file_name" | cut -c7)
all_perm=$(ls -lb "$file_name" | cut -c10)
owner_name=$(ls -lb "$file_name" | awk '{print $3}')
group_name=$(ls -lb "$file_name" | awk '{print $4}')
group_id=$(getent group | awk -F: "
{if(\$1 == \"$group_name\") {print \$3; exit}}")

result_str=''

if [[ $owner_perm = "x" ]]; then
    result_str=$owner_name\\\n
fi
if [[ $result_str != '' ]]; then
    result_str=$result_str
fi
if [[ $group_perm = "x" ]]; then
    result_str=$result_str$(getent passwd | awk -F: "
{if(\$4 == \"$group_id\" && \$1 != \"$owner_name\") printf \"%s\\\n\",\$1}")
    result_str=$result_str$(getent group | awk -F: "
BEGIN{
arrLen = 0
split(\"\", arr)
}
{
	flag = 0
	if(\$3 == \"$group_id\"){
		n = split(\$4, usrs, \",\")
		for(i=1; i<=n; i++) {
			for(k=0; k<arrLen; k++) 
				if(arr[k] == usrs[i]) 
					flag ++
			if(flag == 0) {				
				arr[arrLen] = usrs[i]
				arrLen++
				printf (\"%s\\\n\",usrs[i]) 
			}
			flag=0
		}
	}
}")
fi

if [[ $all_perm = "x" ]]; then
    users=$(getent passwd | awk -F: "
{if(\$1 != \"$owner_name\" && \$4 != \"$group_id\") printf \"%s\\\n\",\$1}")
	users=${users%\\\n}
    result_str=$result_str$(echo $users | gawk "
{
	c=0
	\"groups \"\$0 | getline grs
	close (\"groups \"\$0)
	n = split(grs, a, \" \")
	for(i=2; i<=n; i++) 
	   if(a[i] == \"$group_name\") 
	       c++
	if(c == 0)
	    printf \"%s\\\n\",\$0
}")
fi

echo ${result_str%\\\n}