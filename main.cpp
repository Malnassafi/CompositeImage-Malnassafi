#include"bitmap.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;
// NO MAGIC NUMBERS!
const int LEST_NUM_OF_PICS = 2;
const int MAX_NUM_OF_PICS = 10;
// Function Prototypes
vector <vector <Pixel> > averageMatrix(vector<string>);
void divideMatrix(vector <vector <Pixel> > & , int);
void addingMatrix(vector <vector <Pixel> > & , vector <vector <Pixel> >);
void resizeMatrix(vector <vector <Pixel> > & , int , int);
// main Function begins
int main()
{
        Bitmap image;
        vector <vector <Pixel> > bmp;
        vector <string> vectorOfFiles;
        string fileName;
        char addFile;
        bool validImage;
        do
        {
                cout<<"What is the file name that you want to add? [it must be at least two and no more than 10]\n";
                cin>>fileName;
                image.open(fileName);
                validImage = image.isImage();

                if(validImage == true)
                {
                        cout<<"Image "<<vectorOfFiles.size() + 1<<" has been loaded\n";
                        vectorOfFiles.push_back(fileName);


                        if(vectorOfFiles.size() < MAX_NUM_OF_PICS)
                        {
                                cout<<"Do you want to add another file Y/N\n";
                                cin>>addFile;
                        }
                        else
                        {
                                cout<<" You entered the max num of images allowed in this project which is "<<MAX_NUM_OF_PICS<<"!\n\n";
                        }
                }
                else
                {
                        cerr<<"The file couldnt be loaded the file doesn't exist or isn't a valid bitmap or\n "
                                "it isn't the same dimensions (width and height) as the first image loaded\n";
                }

        }while(vectorOfFiles.size() < MAX_NUM_OF_PICS && (addFile == 'Y' || addFile == 'y'));

        if(vectorOfFiles.size() < LEST_NUM_OF_PICS)
        {
                cerr<<"A composite image cannot be created!\n";
        }
        else
        {
                bmp = averageMatrix(vectorOfFiles);
                image.fromPixelMatrix(bmp);
                image.save("Composite-Malnassafi.bmp");
                cout<<"Image has been Compsite succesfully!\n\n";
        }
        return 0;
}
// Function Def
vector <vector <Pixel> >averageMatrix(vector<string>nameOfFiles)
{                                                           
        Bitmap image;
        vector <vector <Pixel> > mainMatrix;
        vector <vector <Pixel> >test;

        for(int index=0; index < nameOfFiles.size();index++)
        {
                image.open(nameOfFiles[index]);
                test = image.toPixelMatrix();
                resizeMatrix(mainMatrix, test.size() , test[0].size());
                addingMatrix(mainMatrix, test);
                cout<<"\nImage "<<index + 1<<" out of "<<nameOfFiles.size()<<" is done\n\n";
        }
        divideMatrix(mainMatrix,nameOfFiles.size());
        return mainMatrix;
}   

void divideMatrix(vector <vector <Pixel> > & miniMatrix, int size)
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

void addingMatrix(vector <vector <Pixel> > & moreMatrix, vector <vector <Pixel> > test1)
{
        Pixel rgb, RGB;
        for(int r = 0; r<test1.size();r++)
        {    
                for(int c=0; c<test1[r].size();c++)
                {
                        rgb =  test1[r][c];
                        RGB = moreMatrix[r][c];
                        RGB.red= RGB.red + rgb.red;
                        RGB.green = RGB.green + rgb.green;
                        RGB.blue = RGB.blue + rgb.blue;
                        moreMatrix[r][c] = RGB;
                }
        }
}

void resizeMatrix(vector <vector <Pixel> > & reSize , int rows, int cols)
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
