#include "ImageConverter.h"

class VideoConverter : public Converter
{
private:
    /* data */
public:
    VideoConverter();
    VideoConverter(std::string filename);
    ~VideoConverter(){};
    void CaptureWebcam();

};

VideoConverter::VideoConverter(){}

VideoConverter::VideoConverter(std::string filenameGiven){
        setFilename(filenameGiven);

        std::string extention = getExtention(getFilename());

        try{
            if(extention == "mp4" || extention == "mov"){
                setImage(cv::imread(getFilename()));       
            }
            else if (extention == "jpeg" || extention == "png" || extention == "jpg" )
                throw (1);
            
            else
                throw (2);    
            
        }catch(int e){
            if(e == 1){
                std::cout << "Not the correct object type, try use ImageConverter" << std::endl;
            }
            if(e == 2){
                std::cout << "Wrong extention try to use = mov, mp4" << std::endl;
            }
            std::exit(1);
        }

    };

//camera capture
void VideoConverter::CaptureWebcam(){

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
    }
}