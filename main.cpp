#include"bitmap.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;


vector <vector <Pixel> > averageMatrix(vector<string>);

/**
todo: get a vector of strings to save all the filenames in
then make a function that goes thro the vector of strings and opens each file 
and then make each file topixelmatrix then make a vector of vector of pixels to go throgh 
the image then make it get the rgb values and save it in a vector of int, so that the red value
will be saved in vector<int>red for example and green will be saved in vector<int>green, and blue vector<int>blue
when we went throgh all the files which are inside the vector of strings and got all the rgb values in out red, blue and green vectors
then we add all the red to gether and dived by the number of files and do the same thing for green and blue as well, after we get the 
average of each rgb then we return save it in side the vector and return it.
**/
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
    
    if(vectorOfFiles.size()<2)
    {
        cout<<"A composite image cannot be created!\n";
        return 1;
    }

    bmp = averageMatrix(vectorOfFiles);
    image.fromPixelMatrix(bmp);
    image.save("Composite-Malnassafi.bmp");


    return 0;
}
/**
need a vector of vector of pixels to add all the red in each image then divide by the number of images
there are to get the average then make the vector go throgh each pixel and change the redness after
that to it for green and blue as well
**/
vector <vector <Pixel> >averageMatrix(vector<string>nameOfFiles) //trying to make a for loop to go throgh all the files saved in the string vector then opening them then going throgh each one and adding the rgb values
{                                                                //to the main Matrix then dividing by the amount of files we had in the string vector
    Bitmap image;
    vector <vector <Pixel> > mainMatrix;
    string test;
    Pixel rgb, RGB;
    for(int index=0; index < nameOfFiles.size();index++)
    {
        image.open(nameOfFiles[index]);
        test = nameOfFiles[index];
        test = image.toPixelMatrix();
        for(int r = 0; r<test.size();r++)
        {
            for(int c=0; c<test[r].size();c++)
            {
                rgb =  test[r][c];
                RGB = mainMatrix[r][c];


            }
        }
    
    }


}
