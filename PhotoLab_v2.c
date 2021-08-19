
/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2021                 */
/* 								                                     */
/* This is an "A" level representation of PhotoLab v1.               */
/* There are improvements that can be made, but this is considered   */
/* very good.                                                        */
/*                                                                   */
/* This solution is for your reference for this course and           */
/* copyright belongs to the authors below. Reproduction or sharing   */
/* of this code outside of this class is prohibited except with the  */
/* express written consent of the authors.                           */
/*                                                                   */
/* modifications: 						                             */
/* 01/13/21     QV  Adjusted for W21                                 */
/* 01/11/20 	WL	adjusted for W20			                     */
/* 10/1/18  	MC  adjusted for F18			                     */
/* 09/27/17 	RD	adjusted for lecture usage		                 */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 *  * ***************************************************************** *
 *   * First Name:Eesha	
 *    * Last Name:Jain
 *     * UCInetID:	78529929
 *      */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "FileIO.h"
#include "Constants.h"
#include "DIPs.h"
#include "Advanced.h"
int n = 0;
unsigned int rbits = 7;
unsigned int gbits = 7;
unsigned int bbits = 7;
void PrintMenu(void);

void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
       

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    srand(time(NULL));
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
   
    /* Please replace the following code with proper menu  */
    /* with function calls for DIP operations	           */
    
    int option;         // user input option
    char fname[SLEN];   // input file name
    // print welcome message only once
    printf("Welcome to Photo Lab 2021 - v1!");
#ifdef DEBUG
	AutoTest(R,G,B);
	return 0;
#endif //DEBUG
    PrintMenu();
    scanf("%d", &option);
    int rc = -1;
    while (option != 99)
    { if (option == 1)
        {   printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        else if (option >= 2 && option <= 8)
        {   if (rc != 0)
            {   printf("No image was read.\n");
            }
            else
            {   switch(option)
                {   case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;
                    case 3:
                        Aging(R, G, B);
                        printf("\"Aging\" operation is done!\n");
                        break;
                    case 4:
                        EdgeDetection(R, G, B);
                        printf("\"Edge Detection\" operation is done!\n");
                        break;
                    case 5:
                        Sharpen(R, G, B);
                        printf("\"Sharpen\" operation is done!\n");
                        break;
		    case 6:
			Noise(n, R, G, B);
			printf("\"Noise\" operation is done!\n");
			break;
		    case 7:
                        Posterize(R, G, B, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;		
		    case 8:
                        Negative(R, G, B);
                        printf("\"Negative\" operation is done!\n");
                        break;	
                    default:
                        break;
                }   
            }
        }
        else if (option == 22)
        {   AutoTest(R, G, B);
        }
        else
        {   printf("Invalid selection!\n");
        }
	// Process finished, waiting for anothre input
	PrintMenu();
        
        scanf("%d", &option);   
    }


    printf("Exiting program.\n");
    /* End of replacing */
    return 0;
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

    LoadImage("lambo", R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
#ifdef DEBUG
    printf("Aging tested!\n\n");
#endif //DEBUG
    /* add more tests here ("edge" and "sharpen")*/
    LoadImage("lambo", R, G, B);
    EdgeDetection(R, G, B);
    SaveImage("edge", R, G, B);
#ifdef DEBUG
    printf("Edge Detection tested!\n\n");
#endif //DEBUG    
    LoadImage("lambo", R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
#ifdef DEBUG
    printf("Sharpen tested!\n\n");
#endif //DEBUG
    LoadImage("pigeon", R, G, B);
    Noise(30, R, G, B);
    SaveImage("noise", R, G, B);
#ifdef DEBUG
    printf("Noise tested!\n\n");
#endif
    LoadImage("pigeon", R, G, B);
    Negative(R, G, B);
    SaveImage("negative", R, G, B);
#ifdef DEBUG
    printf("Negative tested!\n\n");
#endif
    LoadImage("pigeon", R, G, B);
    Posterize(R, G, B, rbits, gbits, bbits);
    SaveImage("posterize", R, G, B);
#ifdef DEBUG
    printf("Posterize tested!\n\n");
#endif
    
}
void PrintMenu()
{   printf("\n-------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save the image in PPM and JPEG format\n");
    printf(" 3: Run aging filter\n");
    printf(" 4: Run edge detection filter\n");
    printf(" 5: Run sharpen filter\n");
    printf(" 6: Run noise filter\n");
    printf(" 7: Run posterize filter\n");
    printf(" 8: Run negative filter\n");
    printf("22: Test all functions\n");
    printf("99: Exit\n");
    printf("--------------------------\n");
    printf("Please make your choice: ");
}












