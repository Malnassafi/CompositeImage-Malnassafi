#include"bitmap.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;

// NO MAGIC NUMBERS!
const int MIN_NUM_OF_PICS = 2;
const int MAX_NUM_OF_PICS = 10;
const int NO_PICS = 0;
// Function Prototypes
vector <vector <Pixel> > compositeImage(vector<string>);
void divideMatrix(vector <vector <Pixel> > & , int); 
void addingMatrix(vector <vector <Pixel> > & , vector <vector <Pixel> >); 
void resizeMatrix(vector <vector <Pixel> > & , int , int);
void askAndSaveImage(vector <string> &);
void cheakImageSize(vector <string> &);

// main Function begins
int main()
{
        Bitmap image;
        vector <vector <Pixel> > bmp;
        vector <string> vectorOfFiles;
        
        askAndSaveImage(vectorOfFiles);

        if(vectorOfFiles.size() < MIN_NUM_OF_PICS)
        {
                cerr<<"A composite image cannot be created!\n";
        }
        else
        {
                bmp = compositeImage(vectorOfFiles);
                image.fromPixelMatrix(bmp);
                image.save("Composite-Malnassafi.bmp");
                cout<<"Image has been Composite succesfully!\n\n";
        }
        return 0;
} //End of main Fucntion

// Function Def's 
void askAndSaveImage(vector <string> & vectorOfImages) //askes for the images that the user wants to add saves them if thier in a valid BMP format
{
        Bitmap image;
        string fileName;
        bool validImage;
        do
        {
                cout<<"What is the file name that you want to add? if you dont want to add a file write done!\n";
                cin>>fileName;
                if( fileName != "done" && fileName != "DONE")
                {
                        image.open(fileName);
                        validImage = image.isImage();
                        if(validImage == true)
                        {
                                if(vectorOfImages.size() > NO_PICS)
                                {
                                        vectorOfImages.push_back(fileName);
                                        cheakImageSize(vectorOfImages);
                                }
                                else
                                {
                                        cout<<"Image "<<vectorOfImages.size() + 1<<" has been loaded\n";
                                        vectorOfImages.push_back(fileName);
                                }

                                if(vectorOfImages.size() == MAX_NUM_OF_PICS)
                                {
                                        cout<<" You entered the max num of images allowed in this project which is "<<MAX_NUM_OF_PICS<<"!\n\n";
                                }
                        }
                        else
                        {
                                cerr<<"The file couldnt be loaded the file doesn't exist or isn't a valid bitmap \n ";
                        }
                }
        }while(vectorOfImages.size() < MAX_NUM_OF_PICS && (fileName != "DONE" && fileName != "done"));
}

vector <vector <Pixel> > compositeImage(vector<string>nameOfFiles) // Compsites all the images together
{                                                                 
        Bitmap image;                                          
        vector <vector <Pixel> > mainMatrix;                       
        vector <vector <Pixel> >subMatrix;
        for(int index=0; index < nameOfFiles.size();index++)
        {
                image.open(nameOfFiles[index]);
                subMatrix = image.toPixelMatrix();
                resizeMatrix(mainMatrix, subMatrix.size() , subMatrix[0].size());
                addingMatrix(mainMatrix, subMatrix);
                cout<<"\nImage "<<index + 1<<" out of "<<nameOfFiles.size()<<" is done\n\n";
        }
        divideMatrix(mainMatrix,nameOfFiles.size());
        return mainMatrix;
}   

void divideMatrix(vector <vector <Pixel> > & miniMatrix, int size) // divids the main matrix by the number of images saved in the vector of strings
{
        Pixel RGB;
        for(int r=0; r<miniMatrix.size(); r++)
        {
                for(int c=0; c<miniMatrix[r].size();c++)
                {
                        RGB = miniMatrix[r][c];
                        RGB.red = RGB.red / size;
                        RGB.green = RGB.green / size;
                        RGB.blue= RGB.blue / size;
                        miniMatrix[r][c] = RGB;
                }
        }

}

void addingMatrix(vector <vector <Pixel> > & mainSum, vector <vector <Pixel> > addTo) // addes all the RGB Pixels to the main matrix
{
        Pixel rgb, RGB;
        for(int r = 0; r<addTo.size();r++)
        {    
                for(int c=0; c<addTo[r].size();c++)
                {
                        rgb =  addTo[r][c];
                        RGB = mainSum[r][c];
                        RGB.red= RGB.red + rgb.red;
                        RGB.green = RGB.green + rgb.green;
                        RGB.blue = RGB.blue + rgb.blue;
                        mainSum[r][c] = RGB;
                }
        }
}

void resizeMatrix(vector <vector <Pixel> > & reSize , int rows, int cols) // resizes the main matrix to the size of all the images
{
        if(reSize.size() != rows)
        {
                reSize.resize(rows);
        }
        for(int r = 0; r<reSize.size();r++)
        {
                if(reSize[r].size() != cols)
                {
                        reSize[r].resize(cols);
                }
        }

}

void cheakImageSize(vector <string> & sizeOfImage) // cheaks if the size of the image is the same as the first image 
{
        Bitmap image, image1;
        vector <vector <Pixel> >mainImage;
        vector <vector <Pixel> >cheakSize;
        
        image.open(sizeOfImage[0]);
        mainImage = image.toPixelMatrix();
        image1.open(sizeOfImage[sizeOfImage.size() - 1]);
        cheakSize = image1.toPixelMatrix();
        if(mainImage.size() != cheakSize.size() || mainImage[0].size() != cheakSize[0].size())
        {
                sizeOfImage.pop_back();
                image.fromPixelMatrix(mainImage);
                cerr<<"This imgae isn't the same dimensions (width and height) as the first image loaded\n";
        }
        else
        {
                image.fromPixelMatrix(mainImage);
                image1.fromPixelMatrix(cheakSize);
                cout<<"Image "<<sizeOfImage.size()<<" has been loaded\n";
        }
}
