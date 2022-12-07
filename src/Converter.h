#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

std::vector<std::string> imageFormation;

class Converter
{
private:
    //string to save the file name to be converted -> .jpg, .png, .jpeg, / .vid, .mp4
    std::string filename;

    //full string of characters from the most dark to the brightest
    static const std::string standardGrayScaleASCII;
    
    //shorter string of characters from the most dark to the brightest
    static const std::string shorterGrayScaleASCII;

    //cv::Mat image format of OpenCV
    cv::Mat img;

    std::string textResult;

public:
    //Converter constructor
    Converter(){};
    
    //Converter destructor
    ~Converter(){};
    
    //setter filename
    void setFilename(std::string filename);
    
    //getter filename
    std::string getFilename();
    
    //getter filename's extention
    std::string getExtention(std::string filename);
    
    //naive converter image -> ASCII function
    //receiver cv::Mat to convert, and the ASCIIGrayScale -> "shorter" | "full"
    std::string naiveConvert(cv::Mat img, std::string grayScaleType);

    //setter image -> cv::Mat
    void setImage(cv::Mat img);

    //getter image -> cv::Mat
    cv::Mat getImage();
    
    //convert its own imgage to gray scale or a given image (cv::Mat)
    void convertGrayScale();
    void convertGrayScale(cv::Mat img);

    //convert its own imgage to (x,y) or a given image (cv::Mat) to (x,y)
    void resize(int x, int y);
    void resize(cv::Mat img, int x, int y);

    //function that converts a slice of the image = from -> to
    //used for parallelism 
    static void convertSlice(cv::Mat img, std::string grayScaleType, int from_x, int to_x, int threadNumber);

    //converter paralleized, image -> ASCII function
    //receive cv::Mat to convert, and the ASCIIGrayScale -> "shorter" | "full" and the number of threads to
    std::string parallelConvert(cv::Mat img, std::string grayScaleType, int numThreads);

};

void Converter::setImage(cv::Mat img){
    this->img = img;
}

cv::Mat Converter::getImage(){
    return this->img;
}

void Converter::setFilename(std::string filename){
    this->filename = filename;
}

std::string Converter::getFilename(){
    return this->filename;
}

std::string Converter::getExtention(std::string filename){
    int pos = filename.find_last_of('.');
    return filename.substr(pos + 1, filename.size() - pos);
}

std::string Converter::naiveConvert(cv::Mat img, std::string grayscaleType = "shorter" ){
    const std::string standardGrayScaleASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    const std::string shorterGrayScaleASCII =  " .:-=+*#%@";
                                                
    
    //getting the max and min pixel values of a image
    double maxValue, minValue;
    cv::minMaxLoc(img, &minValue, &maxValue);

    //converting each pixel of the image to a ASCII character based on its brightness
    std::string text = "";
    for(int i = 0 ; i < img.rows; i++){
        for(int j = 0 ; j < img.cols; j++){

            if(grayscaleType == "shorter"){
                int index  = shorterGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                text.push_back(shorterGrayScaleASCII[index]);
            }
            else{
                int index  = standardGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                text.push_back(standardGrayScaleASCII[index]);
            }
        }
        text.push_back('\n');
    }
    return text;
}

void Converter::convertGrayScale(){
    cv::cvtColor(this->img, this->img, cv::COLOR_BGR2GRAY);
}

void Converter::convertGrayScale(cv::Mat image){
    cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
}

void Converter::resize(int x, int y){
    cv::resize(this->img, this->img, cv::Size(x, y));
}

void Converter::resize(cv::Mat img, int x, int y){
    cv::resize(img, img, cv::Size(x, y));
}

void Converter::convertSlice(cv::Mat img, std::string grayScaleType, int from_x,  int to_x, int threadNumber){
    const std::string standardGrayScaleASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    const std::string shorterGrayScaleASCII =  " .:-=+*#%@";

    //getting the max and min pixel values of a image
    double maxValue, minValue;
    cv::minMaxLoc(img, &minValue, &maxValue);

    //converting each pixel of the image to a ASCII character based on its brightness
    std::string text = "";
    for(int i = from_x ; i < to_x; i++){
        for(int j = 0 ; j < img.cols; j++){
            if(grayScaleType == "shorter"){
                int index  = shorterGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                text.push_back(shorterGrayScaleASCII[index]);
            }
            else{
                int index  = standardGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                text.push_back(standardGrayScaleASCII[index]);
            }
            if(j == img.cols - 1)
                text.push_back('\n');
        }
    }
    imageFormation[threadNumber] = text;
}

std::string Converter::parallelConvert(cv::Mat img, std::string grayScaleType = "shorter", int numThreads = 1){
    
    for (int i = 0; i < numThreads; i++)
        imageFormation.push_back("");
    
    std::vector<std::thread> workers;

    for (int i = 0; i < numThreads; i++)
    {
        workers.push_back(std::thread(convertSlice, img, grayScaleType, i*(img.rows/numThreads), (i+1)*(img.rows /numThreads), i));    
    }

    for (int i = 0; i < numThreads; i++)
    {
        workers[i].join();
        textResult.append(imageFormation[i]);
    }
    
    return this-> textResult;
    
}