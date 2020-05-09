#include "helpers.h"
#include<math.h>
#include<stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbGray;
    // i = width and j = height because we need to access the rows first and then columns

    for(int i=0; i<height ; i++)
    {
        for(int j=0; j<width ; j++)
        {
            // averages the colour intensity and then applies the same value to get gray color
            rgbGray = round((image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed)/3.000);

            image[j][i].rgbtBlue = rgbGray ;
            image[j][i].rgbtGreen = rgbGray ;
            image[j][i].rgbtRed = rgbGray ;

        }

    }

} // restricting the valur of red blue and green to 255
int limit(int RGB)
{
    if (RGB> 255)
    {
        RGB = 255 ;
    }
    return RGB;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
    int sepiaBlue;
    int sepiaGreen;


    for(int i=0 ; i< width; i++)
    {
        for (int j=0; j<height ; j++)
        {
            // applying the formula for sepia , we also need to round the values for getting an integer as output.
            sepiaBlue = limit(round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue));
            sepiaGreen = limit(round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue));
            sepiaRed = limit(round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue));

            image[j][i].rgbtBlue = sepiaBlue;
            image[j][i].rgbtRed = sepiaRed;
            image[j][i].rgbtGreen = sepiaGreen ;

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //temporary array
    RGBTRIPLE temporary[((width - 1)/2)+ 1];
// swapping
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= round((width - 1)/ 2) ; j++)
        {
            temporary[j] = image[i][j];
        }
       for (int j = 0; j <= round((width - 1)/ 2) ; j++)
       {
           image[i][j] = image[i][width + (-j - 1)];
       }
       for (int j = 0; j <= round((width - 1)/ 2) ; j++)
       {
           image[i][width + (-j - 1)] = temporary[j];
       }
    }

    return;

}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
     int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    //create a temporary table of colors to not to change the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;

            //sums the value of the pixel and 8 neighbouring pixels and skips the iteration if it goes outside the picture
            for(int k =-1 ; k<2 ;k++)
            {
                if (j+k <0 || j + k> height - 1)
                {
                    continue ;
                }

                for (int h =-1; h<2 ; h++)
                {
                    if (h+i<0 || h+i> width - 1)
                    {
                        continue  ;
                    }
                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            //averages the sum to make picture look blur
             temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }
    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}
