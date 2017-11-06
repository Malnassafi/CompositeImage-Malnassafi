#include"bitmap.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;

// Function Prototypes
vector <vector <Pixel> > averageMatrix(vector<string>);
int cheakComposite(vector<string>);
void divideMatrix(vector <vector <Pixel> > & , vector <string>);
void addingMatrix(vector <vector <Pixel> > & , vector <vector <Pixel> >);
void resizeMatrix(vector <vector <Pixel> > & , vector <vector <Pixel> >);
// main Function begins
int main()
{
        Bitmap image;
        vector <vector <Pixel> > bmp;
        vector <string> vectorOfFiles;
        string fileName;
        char addFile;
        bool validImage;
        int c = 0;
        do
        {
                cout<<"What is the file name that you want to add? [it must be at least two and no more than 10]\n";
                cin>>fileName;
                image.open(fileName);
                validImage = image.isImage();
                if(validImage == true)
                {
                        cout<<"Image "<<c+1<<" has been loaded\n";
                        vectorOfFiles.push_back(fileName);
                        c++;
                        cout<<vectorOfFiles.size()<<" \n";
                }
                else
                {
                        cout<<"The file couldnt be loaded, the file doesn't exist or isn't a valid bitmap or it isn't the same dimensions (width and height) as the first image loaded\n";
                        cout<<"please put another file name in\n";
                }
                cout<<"Do you want to add another file Y/N\n";
                cin>>addFile;
        }while(vectorOfFiles.size()<10 && (addFile == 'Y' || addFile == 'y'));

        /*if(vectorOfFiles.size()<2)
          {
          cout<<"A composite image cannot be created!\n";
          return 1;
          }*/
        cheakComposite(vectorOfFiles);
        bmp = averageMatrix(vectorOfFiles);
        image.fromPixelMatrix(bmp);
        image.save("Composite-Malnassafi.bmp");


        return 0;
}
// Function Def
vector <vector <Pixel> >averageMatrix(vector<string>nameOfFiles)
{                                                           
        Bitmap image;
        vector <vector <Pixel> > mainMatrix;
        vector <vector <Pixel> >test;
        //Pixel rgb, RGB;

        for(int index=0; index < nameOfFiles.size();index++)
        {
                image.open(nameOfFiles[index]);
                test = image.toPixelMatrix();
                /*if(mainMatrix.size() != test.size())
                {
                        mainMatrix.resize(test.size());
                }
                for(int r = 0; r<test.size();r++)
                {
                        if(mainMatrix[r].size() != test[r].size())
                        {       
                                mainMatrix[r].resize(test[r].size());
                        }    
                }*/
                resizeMatrix(mainMatrix, test);
                addingMatrix(mainMatrix, test);

                /* for(int r = 0; r<test.size();r++)
                   {
                   if(mainMatrix[r].size() != test[r].size())
                   {
                   mainMatrix[r].resize(test[r].size());
                   }    
                   for(int c=0; c<test[r].size();c++)
                   {
                   rgb =  test[r][c];
                   RGB = mainMatrix[r][c];
                   RGB.red= RGB.red + rgb.red;
                   RGB.green = RGB.green + rgb.green;
                   RGB.blue = RGB.blue + rgb.blue;
                   mainMatrix[r][c] = RGB;


                   }
                   }*/

        }
        divideMatrix(mainMatrix,nameOfFiles);
        /** for(int r=0; r<test.size(); r++)
          {
          for(int c=0; c<test[r].size();c++)
          {
          RGB = mainMatrix[r][c];
          RGB.red = RGB.red / nameOfFiles.size();
          RGB.green = RGB.green / nameOfFiles.size();
          RGB.blue= RGB.blue / nameOfFiles.size();
          mainMatrix[r][c] = RGB;
          }
          }**/
        return mainMatrix;

}   

int cheakComposite(vector<string>cheakFileCount)
{
        if(cheakFileCount.size()<2)
        {
                cout<<"A composite image cannot be created!\n";
                return 1;
        }



}

void divideMatrix(vector <vector <Pixel> > & miniMatrix, vector <string>fileSize)
{
        Pixel RGB;
        for(int r=0; r<miniMatrix.size(); r++)
        {
                for(int c=0; c<miniMatrix[r].size();c++)
                {
                        RGB = miniMatrix[r][c];
                        RGB.red = RGB.red / fileSize.size();
                        RGB.green = RGB.green / fileSize.size();
                        RGB.blue= RGB.blue / fileSize.size();
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

void resizeMatrix(vector <vector <Pixel> > & reSize , vector <vector <Pixel> > maxSize)
{
        if(reSize.size() != maxSize.size())
        {
                reSize.resize(maxSize.size());
        }
        for(int r = 0; r<maxSize.size();r++)
        {
                if(reSize[r].size() != maxSize[r].size())
                {
                        reSize[r].resize(maxSize[r].size());
                }
        }

}
