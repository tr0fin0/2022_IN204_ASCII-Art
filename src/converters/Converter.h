#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>

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
    std::unique_ptr<char[]> naiveConvert(cv::Mat img, int grayScaleType);

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
    static void convertSlice(const cv::Mat img, char *textResult ,int grayScaleType, int from_x, int to_x);

    //converter paralleized, image -> ASCII function
    //receive cv::Mat to convert, and the ASCIIGrayScale -> 1 = "shorter" | 2 = "full" and the number of threads to use in the conversion
    std::unique_ptr<char[]> parallelConvert(const cv::Mat &img, int grayScaleType, int numThreads);

    //function to show in the terminal the ASCII image
    void print_ASCII();
    void print_ASCII(std::unique_ptr<char[]> textResult);
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

std::unique_ptr<char[]> Converter::naiveConvert(cv::Mat img, int grayscaleType = 1){
    const std::string standardGrayScaleASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    const std::string shorterGrayScaleASCII =  " .:-=+*#%@";
                                                
    auto textResult = std::make_unique<char[]>(img.rows * img.cols);

    //getting the max and min pixel values of a image
    double maxValue, minValue;
    cv::minMaxLoc(img, &minValue, &maxValue);

    //converting each pixel of the image to a ASCII character based on its brightness
    for(int i = 0 ; i < img.rows; i++){
        for(int j = 0 ; j < img.cols; j++){
            if(j == img.cols - 1){
                textResult[(img.cols*i) + j] = '\n';
            }
            else{
                if(grayscaleType){
                int index  = shorterGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                textResult[(img.cols*i) + j] = shorterGrayScaleASCII[index];
                }
                else{
                    int index  = standardGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                    textResult[(img.cols*i) + j] = standardGrayScaleASCII[index];
                }
            }
        }
    }

    return textResult;
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

void Converter::convertSlice(cv::Mat img, char *textResult, int grayScaleType, int from_x,  int to_x){
    const std::string standardGrayScaleASCII = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    const std::string shorterGrayScaleASCII =  " .:-=+*#%@";

    //getting the max and min pixel values of a image
    double maxValue, minValue;
    cv::minMaxLoc(img, &minValue, &maxValue);

    //converting each pixel of the image to a ASCII character based on its brightness
    for(int i = from_x ; i < to_x; i++){
        for(int j = 0 ; j < img.cols; j++){
            if(j == img.cols - 1){
                textResult[(img.cols*i) + j] = '\n';
            }
            else{
                if(grayScaleType){
                int index  = shorterGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                textResult[(img.cols*i) + j] = shorterGrayScaleASCII[index];
                }
                else{
                    int index  = standardGrayScaleASCII.size()*((int)img.at<uchar>(i,j) - minValue)/maxValue;
                    textResult[(img.cols*i) + j] = standardGrayScaleASCII[index];
                }
            }
        }
    }
    
}

std::unique_ptr<char[]> Converter::parallelConvert(const cv::Mat& img, int grayScaleType, int numThreads = 1){
    
    auto textResult = std::make_unique<char[]>(img.rows * img.cols);

    std::vector<std::thread> workers;

    for (int i = 0; i < numThreads; i++)
    {
        workers.push_back(std::thread(convertSlice, img, textResult.get(), grayScaleType, i*(img.rows/numThreads), (i+1)*(img.rows/numThreads)));    
    }

    for (int i = 0; i < numThreads; i++)
    {
        workers[i].join();
    }
    
    return textResult;
}

void Converter:: print_ASCII(std::unique_ptr<char[]> textResult){
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            std::cout << textResult[(img.cols*i) + j];
        }
    }
}

void Converter:: print_ASCII(){
    std::unique_ptr<char[]> textResult = parallelConvert(img, 1, 2);
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            std::cout << textResult[(img.cols*i) + j];
        }
    }
}