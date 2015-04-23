#!/bin/ksh
USAGE="usage: lab2.2 min_users"
if ! echo $1 | /usr/xpg4/bin/egrep -q '^[0-9]+$'
then
	echo $USAGE
	exit
fi
getent group | sort -t: -k1 | nawk -F":" -v min=$1 '
BEGIN{
	arrLen = 0
}
{
	n = split($4, usr1, ",")
	gId = $3
	gName = $1
	if(checkGroup(gName) == 1)
	{
		command = "getent passwd"
		while((command | getline) > 0)
			if(gId == $4)
				n++
		close(command)	
		if(n > min)
			print gName " - " n
	}
	groups[arrLen++] = gName
}
function checkGroup(g) 
{
	for(i=0; i<arrLen; i++)
		if(groups[i] == g)
			return 0
	return 1
}
'