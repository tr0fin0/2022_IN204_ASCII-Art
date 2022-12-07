#include "ImageConverter.h"

class VideoConverter : public Converter
{
private:
    /* data */
public:
    VideoConverter(std::string filename);
    ~VideoConverter();
};

VideoConverter::~VideoConverter()
{
}

/*
    
    VideoCapture cap(0);
    Mat img, aux, img_gray;

    while(true){
        cap.read(img);

        system("cls || clear");

        cvtColor(img, aux, COLOR_BGR2GRAY);
        resize(aux, img_gray, Size(140, 75));
        string ASCII_gray_scale = "   ..:-=+*#%@";

        //creating the string
        string text = "";
        for(int i = 0 ; i < img_gray.rows; i++){
            for(int j = 0 ; j < img_gray.cols; j++){
                //for the future -> 0 -> min(pixel_image) and 256 -> max(pixel_image)
                int index  = ASCII_gray_scale.size()*((int)img_gray.at<uchar>(i,j) - 0)/256;
                text.push_back(ASCII_gray_scale[index]);
            }
            text.push_back('\n');
        }
        cout << text;
    
    }
    
    */