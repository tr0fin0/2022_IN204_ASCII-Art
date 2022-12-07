#include "VideoConverter.h"

int main(){
    
    ImageConverter c("../images/agnt.jpeg");

    c.convertGrayScale();

    std::cout << c.getImage().size() << std::endl;

    //c.resize(100, 100);

    std::cout << c.getImage().size() << std::endl;

    int tests = 20;
    int meanN = 0;
    for (int i = 0; i < tests; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        c.naiveConvert(c.getImage(), "shorter");
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);    
        meanN = meanN + duration.count();
    }
    meanN = meanN/tests;
    std::cout << meanN << std::endl;

    for (int t = 1; t < 9; t++)
    {
        meanN = 0;
        for (int i = 0; i < tests; i++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            c.parallelConvert(c.getImage(), "shorter", t);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);    
            meanN = meanN + duration.count();
        }
        meanN = meanN/tests;
        std::cout << meanN << std::endl;
    }
    
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

        //std::cout << c.parallelConvert(c.getImage(), "shorter", 1);
        std::cout << c.naiveConvert(c.getImage(), "shorter");
        
    
    }
    */
    
    

    return 0;
}
