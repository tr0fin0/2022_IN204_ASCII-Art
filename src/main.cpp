#include "VideoConverter.h"

int main(){
    
    ImageConverter c("../images/flower.jpeg");

    c.convertGrayScale();

    std::cout << c.getImage().size() << std::endl;

    //c.resize(100, 50);

    std::cout << c.getImage().size() << std::endl;

    int tests = 1000;
    double meanN = 0;

    //testing time for converting 1000 images with the naive approach
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < tests; i++)
    {
        c.naiveConvert(c.getImage(), 1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);    
    meanN = meanN + duration.count();
    std::cout << "Naive approach ( no threads ) - [converting " << tests <<" images]: " << meanN/1000000 << "s" << std::endl;

    
    //testing time for converting 1000 images with the parallel approach
    //testing from 1 -> 14 threads
    for (int t = 1; t < 15; t++)
    {
        meanN = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < tests; i++)
        {
            
            c.parallelConvert(c.getImage(), 2, t);

        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);    
        meanN = meanN + duration.count();
        
        std::cout<< "Parallel approach " << t <<" thread(s) - [converting " << tests <<" images]: " <<meanN/1000000 << std::endl;
    }
    
    //camera capture
    /*
    cv::VideoCapture cap(0);
    cv::Mat img;

    while(true){
        Converter c;
        cap.read(img);
        system("cls || clear");

        c.setImage(img);
        c.convertGrayScale();
        
        c.resize(170, 50);

        c.print_ASCII(c.parallelConvert(c.getImage(), 1, 3));
        //std::cout << c.parallelConvert(c.getImage(), "shorter", 1);
        //std::cout << c.naiveConvert(c.getImage(), "shorter");
    }
    */
    
    

    return 0;
}
