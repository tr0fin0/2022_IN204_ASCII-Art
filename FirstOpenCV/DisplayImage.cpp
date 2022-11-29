#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;



int main(){
    //lendo a imagem
    string path = "../images/lenna.png";
    Mat image = imread(path);
    Mat aux, img_gray;
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    //convertendo a imagem para preto e branco
    cvtColor(image, aux, COLOR_BGR2GRAY);
    resize(aux, img_gray, Size(75, 75));

    /*
     "Standard" character ramp for grey scale pictures, black -> white.
        "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^`'. "
    A more convincing but shorter sequence for representing 10 levels of grey is
        " .:-=+*#%@"
    */
    //using the shorter:
    string ASCII_gray_scale = " .:-=+*#%@";

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

    //imshow("Teste", img_gray);
    //waitKey(0);
    
    
    return 0;
}



