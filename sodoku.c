
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>


#define NUM_CHILD_THREADS 27  
#define	MAX 100

int sodokuArray[9][9] = { {2,6,2,5,6,7,4,4,5},{2,3,2,8,1,5,7,4,8},{5,4,7,8,8,7,5,5,4},{1,1,8,7,5,9,7,4,5},{6,3,5,2,7,5,8,6,3},{0,9,0,7,5,4,6,3,7},{2,4,5,6,6,7,3,4,2},{8,8,9,3,4,8,4,6,3},{4,2,6,8,5,6,3,2,5} };
bool rowCheck[9];
bool colCheck[9];
bool subgridCheck[9];
int sodoku[9][9];

typedef struct { 
int topRow;
int  bottomRow;
int leftCol;
int rightCol;
} index_param;  

void *runner(void *param);

int main(){
/*
FILE * fp;
char line[MAX];
*/
int i, j;
int c;
bool result;

/* initialize thread arrays */
pthread_t tid[NUM_CHILD_THREADS];
pthread_attr_t attr_tid[NUM_CHILD_THREADS];
index_param index_tid[NUM_CHILD_THREADS];



/*
fp = fopen("sodokupuzzle.txt", "r");

	while(!feof(fp)){
	printf("pass");
	j = 0;
	fgets(line, MAX, fp);
	char* piece = strtok(line, " ");
		while(piece != NULL){
			printf("%s", piece);
			sodoku[i][j] = atoi(piece);
			printf("%d", sodoku[i][j]);
			piece = strtok(NULL, " ");
			j += 1;
}
	printf("\n");
	i += 1;
}
fclose(fp);
*/

/*initialize Column Params*/
for(i = 0; i < 9; i++){
	index_tid[i].topRow = 0;
	index_tid[i].bottomRow = 9;
	index_tid[i].leftCol = i;
	index_tid[i].rightCol = i;
}

/*Initialize  Row Params*/
for(i = 9; i < 18; i++){
	index_tid[i].topRow = i;
	index_tid[i].bottomRow = i;
	index_tid[i].leftCol = 0;
	index_tid[i].rightCol = 9;
}

/*Initialize Subgrid Params*/
c = 18;

for(i = 0; i < 3; i++){
	for(j = 0; j < 3; j++){
		index_tid[c].topRow = (i * 3);
		index_tid[c].bottomRow = (i * 3) + 2;
		index_tid[c].leftCol = (j * 3);
		index_tid[c].rightCol = (j * 3) + 2;
		c += 1; 
}

}

for(i = 0; i < NUM_CHILD_THREADS; i++){
	pthread_attr_init(&(attr_tid[i]));
}

for(i = 0; i < NUM_CHILD_THREADS; i++){
	pthread_create(&(tid[i]), &(attr_tid[i]), runner, &(index_tid[i]));
}

for(i = 0; i < NUM_CHILD_THREADS; i++){
	pthread_join(tid[i], NULL);
}

/* Checks if any of the checks are false after the threads run. */
result = true;
for(i = 0; i < 9; i++){
	if(colCheck[i] == false){
		result = false;
}
	if(rowCheck[i] == false){
		result = false;
}
	if(subgridCheck[i] == false){
		result = false;
}
}

if(result == true){
	printf("\n\n Sodoku Puzzle is Valid !");
}else{
	printf("\n\n Sodoku Puzzle is invalid !");
}

}

void *runner(void *param)
{
	index_param *inP;
	int top;
	int bottom;
	int left;
	int right;
	int i, j;
	int c = 0;
	pthread_t self;
	int checkSelf[9] = {1,2,3,4,5,6,7,8,9};
	int numFind = 0;
	int gridNum = 0;
	int found;
	bool valid = false;
	char* finalResult;
	int result = 0;
	char* type[] = {"Row: ", "Column: ", "Subgrid: " };
	
	
	inP = (index_param *)param;
	top = inP->topRow;
	bottom = inP->bottomRow;
	left = inP->leftCol;
	right = inP->rightCol;

	self = pthread_self();

	for(i = top; i <= bottom; i++){
		for(j = left; j <= right; j++){
			for(c = 0; c < 9; c++){
				if(sodokuArray[i][j] == checkSelf[c]){
					numFind += 1;
					checkSelf[c] = 0;
}
}
}
}

if(numFind == 9){
	valid = true;
}

if(valid == true){
	finalResult = "Valid!";
}else{
	finalResult = "Invalid!";
}

if(top == bottom){
	rowCheck[top] = valid;
	result = 0;
}else if(left == right){
	colCheck[left] = valid;
	result = 1;
}else{
	gridNum += (((top/3)*3) + (left/3));
	subgridCheck[gridNum] = valid;
	result = 2;
}

printf("%s %u Top Row: %d Bottom Row: %d Left Column: %d Right Column: %d %s\n", type[result], (unsigned int)self, top, bottom, left, right, finalResult);
pthread_exit(0);
}
