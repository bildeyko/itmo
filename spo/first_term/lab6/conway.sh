#!/bin/ksh
FIELDFILE="field"

nawk 'BEGIN{
	size = 45;
	generation = 1;
	loadField();
	drawField();

	while(1)
	{
		newGeneration();
		generation ++;
		drawField();
		for(i=0;i<1000000;i++)
	}
}

function loadField() {
	curRow=0;
	while ((getline str < "'"$FIELDFILE"'") > 0)
	{
		split(str,r,",");
		if(curRow<size)
			for(i=0;i<size;i++)
				field[curRow,i] = r[i+1];
		curRow++;
	}
}

function drawField() {
	alive = 0;
	for(i=0;i<size*2;i++)
		printf "="
	print
	for(i=0; i<size; i++)
	{
		printf "|"
		for(j=0;j<size;j++)
			if(field[i,j]) {
				printf "# "
				alive ++;
			}
			else
				printf "  "
		printf "|"
		print
	}
	for(i=0;i<size*2+2;i++)
		printf "-"
	print
	printf("Generation: %d\tAlive: %d\n", generation,alive);
}

function newGeneration() {
	for(i=0;i<size;i++)
	{
		for(j=0;j<size;j++)
		{
			countNegh = countNeighbors(i,j);
			newGen[i,j]=(field[i,j]?(countNegh~/[23]/):(countNegh==3))
		}
	}
	for(i=0;i<size;i++)
		for(j=0;j<size;j++)
			field[i,j]=newGen[i,j]
}

function countNeighbors(x,y) {
	dirs[0,0]=-1; dirs[0,1]=-1
	dirs[1,0]=0; dirs[1,1]=-1
	dirs[2,0]=1; dirs[2,1]=-1
	dirs[3,0]=-1; dirs[3,1]=0
	dirs[4,0]=1; dirs[4,1]=0
	dirs[5,0]=-1; dirs[5,1]=1
	dirs[6,0]=0; dirs[6,1]=1
	dirs[7,0]=1; dirs[7,1]=1
	count = 0;
	for(z=0;z<8;z++)
		count += (x+dirs[z,0]<size && y+dirs[z,1]<size &&
			  x+dirs[z,0]>=0 && y+dirs[z,1]>=0 &&
			  field[x+dirs[z,0], y+dirs[z,1]])
	return count
}
'
