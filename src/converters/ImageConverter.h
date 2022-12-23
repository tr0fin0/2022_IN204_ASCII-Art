#include "Converter.h"

class ImageConverter : public Converter
{
private:

public:
    //Image Converter constructor
    ImageConverter(std::string filename);
    
    //Image Converter destructor
    ~ImageConverter();

};

ImageConverter::ImageConverter(std::string filenameGiven){
        setFilename(filenameGiven);

        std::string extention = getExtention(getFilename());

        try{
            if(extention == "jpeg" || extention == "png" || extention == "jpg"){
                setImage(cv::imread(getFilename()));       
            }
            else if (extention == "mp4" || extention == "mov")   
                throw (1);
            
            else
                throw (2);    
            
        }catch(int e){
            if(e == 1){
                std::cout << "Not the correct object type, try use VideoConverter" << std::endl;
            }
            if(e == 2){
                std::cout << "Wrong extention try to use = jpeg , png , jpg" << std::endl;
            }
            std::exit(1);
        }

    };

ImageConverter::~ImageConverter()
{
}

