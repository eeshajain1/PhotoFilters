
//Eesha Jain Advanced.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Constants.h"
#include "Advanced.h"
/*** global definitions ***/

void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) 
{
  int x, y;
  printf("Please input your noise percentage: ");
  scanf("%d", &n);
  for(int i = 0; i < ((n*WIDTH*HEIGHT)/100); i++ ){
    x = rand() % WIDTH;
    y = rand() % HEIGHT;
    R[x][y] = 255;
    G[x][y] = 255;
    B[x][y] = 255;

  }

}
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
    int x, y;
    unsigned int rexp, gexp, bexp;
    printf("Enter the number of posterization bits for R channel (1 to 8): ");
    scanf("%d", &rbits);
    rexp =(int)(pow(2,(rbits - 1))-1); /* this is the vaue we | our red bits by */
    printf("Enter the number of posterization bits for G channel (1 to 8): ");
    scanf("%d", &gbits); 
    gexp = (int)(pow(2,(gbits - 1))-1); /* this is the vaue we | our green bits by */
    printf("Enter the number of posterization bits for B channel (1 to 8): ");
    scanf("%d", &bbits); 
    bexp =(int)(pow(2,(bbits - 1))-1); /* this is the vaue we | our blue bits by */

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
            R[x][y] = (R[x][y] | rexp);//we make all the last bits 1
            if((R[x][y] >>(rbits-1))%2 == 1){//we shift to check the desired bit, then if it is 1, we subtract
            	R[x][y] = R[x][y] - (int)(pow(2,(rbits-1)));
            }
            B[x][y] = (B[x][y] | bexp);
            if((B[x][y] >>(bbits-1))%2 == 1){
                B[x][y] = B[x][y] - (int)(pow(2,(bbits-1)));
            }
            G[x][y] = (G[x][y] | gexp);
            if((G[x][y] >>(gbits-1))%2 == 1){
                G[x][y] = G[x][y] - (int)(pow(2,(gbits-1)));
            }
     /* first we | in order to make the last few bits 1, then we check if the desired bit is one by shifting, and if so, we subtract*/
        }
   }
}

void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for (y = 0; y < HEIGHT; y++)
    {   for(x = 0; x < WIDTH; x++)
        {   R[x][y] = 255 - R[x][y];
            G[x][y] = 255 - G[x][y];
            B[x][y] = 255 - B[x][y];            
        }
    }

}
