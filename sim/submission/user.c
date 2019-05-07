#include "project.h"


int and[3][3]={{0,0,0},{0,1,2},{0,2,2}};
int nand[3][3]={{1,1,1},{1,0,2},{1,2,2}};
int or[3][3]={{0,1,2},{1,1,1},{2,1,2}};
int nor[3][3]={{1,0,2},{0,0,0},{2,0,2}};
int xor[3][3]={{0,1,2},{1,0,2},{2,2,2}};
int xnor[3][3]={{1,0,2},{0,1,2},{2,2,2}};
int inv[3]={1,0,2};
int from[3]={0,1,2};
int chartoint(char c)
{
if(c == 'x')
{
return 2;

}
else {return (c-'0');}

}

char inttochar(int c)
{
if(c == 2)
{
return 'x';

}
else {return c+'0';}

}
int shahrul(int gate,int a,int b)


{
if (gate==1)
{

return from[a];
}
if(gate==2)
{
return and[a][b];
}

if(gate==3)
{

return nand[a][b];
}
if(gate==4)
{
return or[a][b];
}
if(gate==5)
{
return nor[a][b];
}
if(gate==6)
{
return xor[a][b];
}
if(gate==7)
{
return xnor[a][b];
}
if(gate==8)
{
return from[a];
}
if(gate==9)
{
return inv[a];
}
if(gate==10)
{

return from[a];
}


}
int simulateCircuit( NODE* graph, int nodeCount, PATTERN* inputVector, int vectorCount, FILE* outputFile )
{
	int vectorLoopCount, circuitLoopCount;
int a;
	LIST* tempNode = NULL;
	int inputVectorCharacterPosition = 0; // variable to store the character position of the input vector
	char* trimmedVector = NULL; // use this variable to store the strtok (http://www.cplusplus.com/reference/cstring/strtok/) function result
	for ( vectorLoopCount = 0; vectorLoopCount < vectorCount; ++vectorLoopCount ) // loop through the input vectors
	{
		inputVectorCharacterPosition = 0; // start the input vector over

		// remove the \n\r from the input vector
		trimmedVector = strtok( inputVector[ vectorLoopCount ].piv, "\n\r" );

		// write the input vector to the output file (this is the only place the trimmedVector is used
		fprintf( outputFile, "Input Vector:\n%s\n", trimmedVector );
		fprintf( outputFile, "Output Vector:\n" );
printf("%s",trimmedVector);

		// loop through the circuit (graph)
		for ( circuitLoopCount = 0; circuitLoopCount <= nodeCount; circuitLoopCount++ )
		{
			if ( graph[ circuitLoopCount ].typ == INPT )
			{
			graph[ circuitLoopCount ].val = chartoint(trimmedVector[inputVectorCharacterPosition]);
			inputVectorCharacterPosition++;
// turn char into an int AND increment the input vector character
                          
			}
			else
			{
				if ( graph[ circuitLoopCount ].fin != NULL )
				{
					tempNode = graph[ circuitLoopCount ].fin;
					 a=graph[ tempNode->id ].val; // store this value to send to the propogation table
					while ( tempNode != NULL )
					{
					
						if ( tempNode->nxt != NULL )
						{
							
							a=shahrul(graph[ circuitLoopCount ].typ,a,graph[ tempNode->nxt->id ].val); // this is the second argument to the lookup table
						       
 						  
// call and store the return of the lookup table
							/*
							 * this must be able to handle multi-input gates! This is not as difficult as it sounds.
							 * Remember, a four input AND gate is the same as two two input AND gates in series, so all
							 * you have to do is store the results of one loop ( one AND gate ), grab the next loops fan in value, and use the previous
							 * loops result as an argument to the lookup table. Repeat!
							 */
						}
                                          
						else if(graph[ circuitLoopCount ].typ == NOT||graph[ circuitLoopCount ].typ == BUFF||graph[ circuitLoopCount ].typ == FROM)
							{a = shahrul( graph[ circuitLoopCount ].typ, a, graph[ 0 ].val);}
						tempNode = tempNode->nxt;
					}

				graph[ circuitLoopCount ].val = a;// set this value = to the lookup table's logic

					if ( graph[ circuitLoopCount ].po == 1 )
					{
						fprintf(outputFile, "%c", inttochar(graph[circuitLoopCount].val));// convert int to char and put the value in the outputFile
						// i.e. fprintf(outputFile, "%c", intToChar(graph[circuitLoopCount].val));
					}
				}
			}
		}

		// print a separator
		fprintf( outputFile, "\n\n");
	}
	return 1;
}



