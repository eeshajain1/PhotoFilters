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
 * ***************************************************************** *
 * First Name:Eesha	
 * Last Name:Jain
 * UCInetID:	78529929
 */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*** global definitions ***/

#define WIDTH  600		/* image width */
#define HEIGHT 400		/* image height */
#define SLEN    64		/* maximum length of file names */

// added new defines for edge detection filter
#define MAX_PIXEL 255	/* max pixel value */
#define MIN_PIXEL 0		/* min pixel value */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
/* written for you; should not been modified */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
/* written for you; should not been modified */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* aging the photo */
/* sample function to get you started */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* detect edges in a picture (black background with white edges) */
void EdgeDetection(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
       
void Noise(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

//void Negative(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);
int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    /* Please replace the following code with proper menu  */
    /* with function calls for DIP operations	           */
    
    int option;         // user input option
    char fname[SLEN];   // input file name

    // print welcome message only once
    printf("Welcome to Photo Lab 2021 - v1!");
    PrintMenu();
    scanf("%d", &option);
    
    int rc = -1;        // return code of LoadImage()

    while (option != 99)
    {   
        // menu item 2-4 requires image is loaded first
        if (option == 1)
        {   printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        else if (option >= 2 && option <= 5)
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
			Noise(R, G, B);
			printf("\"Noise\" operation is done!\n");
			break;
		    case 7:
                        Posterize(R, G, B);
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

/* takes in a file name without extension */
/* writes file into R, G, B arrays */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

/* takes R, G, B arrays and writes it in a file */
/* filename (fname) has no extension */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}

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

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

    LoadImage("lambo", R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
    printf("Aging tested!\n\n");
    
    /* add more tests here ("edge" and "sharpen")*/
    LoadImage("lambo", R, G, B);
    EdgeDetection(R, G, B);
    SaveImage("edge", R, G, B);
    printf("Edge Detection tested!\n\n");
    
    LoadImage("lambo", R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    printf("Sharpen tested!\n\n");
    
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/

// print menu only
void PrintMenu()
{   printf("\n-------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save the image in PPM and JPEG format\n");
    printf(" 3: Run aging filter\n");
    printf(" 4: Run edge detection filter\n");
    printf(" 5: Run sharpen filter\n");
    printf("22: Test all functions\n");
    printf("99: Exit\n");
    printf("--------------------------\n");
    printf("Please make your choice: ");
}


// edge detection function
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

// Sharpen function
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
void Noise(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]) 
{


}
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

}

/* MORE COMING SOON */

/* EOF */
