#include"bitmap.h"
#include<vector>
#include<iostream>
#include<string>

using namespace std;


//vector <vector <Pixel> > avergaeMatrix(vector<vector <Pixel> >);
//Pixel averageColorPixel(Pixel, Pixel, Pixel);
int main()
{
    Bitmap image;
    vector <vector <Pixel> > bmp;
    string fileName[10];
    int c = 0;
    char addFile;
    bool validImage = image.isImage();
    do{
            cout<<"What is the file name that you want to add? [it must be at least two and no more than 10]\n";
            cin>>fileName[c];
            image.open(fileName[c]);
            if(validImage == true)
            {
                cout<<"Image "<<c+1<<" has been loaded\n";
                c++;
            }
            else
            {
                cout<<"The file couldnt be loaded, the file doesn't exist or isn't a valid bitmap or it isn't the same dimensions (width and height) as the first image loaded\n";
                cout<<"please put another file name in";
            }
            cout<<"Do you want to add another file Y/N\n";
            cin>>addFile;
      }while(fileName[c].size()<10 && addFile == 'Y' || addFile == 'y');

    return 0;
}
