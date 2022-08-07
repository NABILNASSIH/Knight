#include <stdio.h>
//#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"


int cur_knight, new_knight;

// Initialize a new Game .
Item *initGame()
{
  int i;
  Item *node;

	char *initial = (char*)malloc(MAX_BOARD*sizeof(char));
		initial[0] = 1 ;
	for (int i=1; i<MAX_BOARD; i++) initial[i] = 0;

    node = nodeAlloc();
	initBoard(node, initial);
    node->depth = 0;
	node->blank = 0 ;

  return node;
}
// initialize node's state from a given board
void initBoard(Item *node, char *board) {
	assert( node );
	int i;
	
	node->size = MAX_BOARD;
     node->board = calloc(MAX_BOARD, sizeof(char));
  
	/* Copy board */
	 for (i = 0; i<MAX_BOARD; i++)
	 {
        node->board[i] = board[i];
    }

}

// Return 0 si le cavalier est bien placer 

double evaluateBoard(Item *node) {
    if(node->board[MAX_BOARD-1] == 1)
        return 0 ; // FIN DU JEU
    else
        return 1 ; // CHERCHE ENCORE
}
int position(int i, int j){
    return i*WH_BOARD+j;
}
    
// print a board


void printBoard( Item *node )
{
  int i, j;
  assert(node);
	printf("\n");
	for (j=0 ; j<WH_BOARD; j++){
    if (j==0)
      printf(" ___");
      else
      printf("____");}
  printf("\n");

  for (i=0 ; i < MAX_BOARD ; i++) {
    if (i%WH_BOARD == 0)printf("|");
      
    printf("%2d |", node->board[i]);
    if (((i+1)%WH_BOARD) == 0) {
			printf("\n");
	for (j=0; j<WH_BOARD; j++)
        if (j==0)
          printf(" ___");
        else
          printf("____");
        printf("\n");
		}
  }
	printf("\n");

}	
// Test if position pos is valid with respect to node's state
// knight -> the position already visited
 int isValidPosition( Item *node, int pos )
{
    int i, j, ii, jj ;
    cur_knight = node->blank ;
    ii = cur_knight / WH_BOARD;
    jj = cur_knight % WH_BOARD;
	i= pos /WH_BOARD;
    j= pos % WH_BOARD;
 
    if((abs(ii-i) *abs( jj-j))==2 ) return 1;     // POSITION VALIDE
	
	 return 0; // POSITION INVALIDE

}	

   
 
// Return a new item where a new Knight is added at position pos if possible. NULL if not valid
Item *getChildBoard( Item *node, int num_pos )
{
    Item *child_p = NULL;
    
	if ( isValidPosition(node, num_pos) == 1 ) 
	{
		new_knight = num_pos ;
        /* allocate and init child node */
        child_p = nodeAlloc() ;
        initBoard(child_p, node->board) ;

		/* Make move */
        child_p->board[cur_knight] = 0;
        child_p->board[new_knight] = 1;
        child_p->blank = new_knight ;
       

		/* link child to parent for backtrack */
        child_p->parent = node;
        
        /* Value of depth */
        child_p->depth = node->depth +1 ;
        
        /* Value of cost */
        child_p->f = child_p->depth ;     
    }
    
	return child_p;
}




// TEST LIST
/*
int main()
{ 

   Item *node;
   node=initGame();
   Item *node1;
   Item *node2;
   int A;
int i;
   node=initGame();
   printBoard( node);


  
    A=isValidPosition( node, 13 );
	printf("%d",A);
	printf("\n");
    A=isValidPosition( node, 8 );
	printf("%d",A);
   printf("\n");
	printf("//////////////////////");
    node1=getChildBoard( node, 8 );
	getChildBoard( node1, 12 );
	getChildBoard( node1, 16 );
	getChildBoard( node1, 0 );
	getChildBoard( node1, 4);
	return 0;

}
*/
