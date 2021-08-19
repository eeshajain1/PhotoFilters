//Eesha Jain
//DIPs.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Constants.h"
#include "DIPs.h"
#include "FileIO.h"

/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
	    B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
            R[x][y] = (unsigned char) (B[x][y]*1.6);
            G[x][y] = (unsigned char) (B[x][y]*1.6);
	}
    }
}

void EdgeDetection(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{   
    int             x, y, m, n, a, b;
    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];
    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            tmpR[x][y] = R[x][y];
            tmpG[x][y] = G[x][y];
            tmpB[x][y] = B[x][y];
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < HEIGHT - 1; y++){
        for (x = 1; x < WIDTH - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (tmpR[x][y] - tmpR[a][b]);
                    sumG += (tmpG[x][y] - tmpG[a][b]);
                    sumB += (tmpB[x][y] - tmpB[a][b]);
                }
            }
            R[x][y] = (sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < MIN_PIXEL) ? MIN_PIXEL: sumR;
            G[x][y] = (sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < MIN_PIXEL) ? MIN_PIXEL: sumG;
            B[x][y] = (sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < MIN_PIXEL) ? MIN_PIXEL: sumB;
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < HEIGHT; y++) {
        R[0][y] = 0;
        G[0][y] = 0;
        B[0][y] = 0;
        R[WIDTH - 1][y] = 0;
        G[WIDTH - 1][y] = 0;
        B[WIDTH - 1][y] = 0;
    }
    for (x = 0; x < WIDTH; x++) {
        R[x][0] = 0;
        G[x][0] = 0;
        B[x][0] = 0;
        R[x][HEIGHT - 1] = 0;
        G[x][HEIGHT - 1] = 0;
        B[x][HEIGHT - 1] = 0;
    }
} 

void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{   int x, y;
    int tmpr = 0, tmpg = 0, tmpb = 0;
    unsigned char R_temp[WIDTH][HEIGHT];
    unsigned char G_temp[WIDTH][HEIGHT];
    unsigned char B_temp[WIDTH][HEIGHT];
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R_temp[x][y] = R[x][y];
            G_temp[x][y] = G[x][y];
            B_temp[x][y] = B[x][y];            
        }
    }
    for (x = 1; x < WIDTH - 1; x++)
    {   for (y = 1; y < HEIGHT - 1; y++)
        {   tmpr = 9 * R[x][y] - R[x-1][y-1] - R[x-1][y] - R[x-1][y+1] - R[x][y-1] - R[x][y+1] - R[x+1][y-1] - R[x+1][y] - R[x+1][y+1];
            tmpg = 9 * G[x][y] - G[x-1][y-1] - G[x-1][y] - G[x-1][y+1] - G[x][y-1] - G[x][y+1] - G[x+1][y-1] - G[x+1][y] - G[x+1][y+1];
            tmpb = 9 * B[x][y] - B[x-1][y-1] - B[x-1][y] - B[x-1][y+1] - B[x][y-1] - B[x][y+1] - B[x+1][y-1] - B[x+1][y] - B[x+1][y+1];
        R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
        G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
        B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb; 
        tmpr = tmpg = tmpb = 0;
        }
    }
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R[x][y] = R_temp[x][y];
            G[x][y] = G_temp[x][y];
            B[x][y] = B_temp[x][y];            
        }
    }
}
