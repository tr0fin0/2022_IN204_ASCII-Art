#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>
#include <gdkmm/pixbuf.h>
//#include "../converters/ImageConverter.h"

class ConvertFile : public Gtk::Window
{
public:
    ConvertFile(std::string filePath);

private:
    void setHierarchy(std::string filePath);
    void setStyle();
    void setBehaviour();
    void on_button_quit();
    void buttonConvert_clicked();
    void buttonSave_clicked();


    std::string filePath;
    Gtk::Fixed fixedWindow;
    Gtk::Box boxImg, boxButtons;
    Gtk::Alignment alignButtons;
    Gtk::Widget *image;
    Gtk::Button buttonConvert, buttonSave;
};

ConvertFile::ConvertFile(std::string filePath) : boxImg{Gtk::Orientation::ORIENTATION_VERTICAL},
                                                 boxButtons{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    this->filePath = filePath;
    setHierarchy(filePath);
    setStyle();
    setBehaviour();

    show_all_children();
}

void ConvertFile::setHierarchy(std::string filePath)
{
    int windowW = 1000;
    int windowH = 500;

    add(fixedWindow);
    fixedWindow.add(boxImg);
    fixedWindow.add(alignButtons);
    fixedWindow.move(boxImg, 0, 0);
    fixedWindow.move(alignButtons, 448, 224);

    const char *pathConst = filePath.c_str();
    image = Glib::wrap(gtk_image_new_from_file(pathConst), false);

    // Load the image
    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(pathConst);

    // Get the original width and height of the image
    int originalWidth = pixbuf->get_width();
    int originalHeight = pixbuf->get_height();

    // Calculate the new width and height of the image while maintaining the aspect ratio
    int maxWidth = 400;  // Set the maximum width of the image
    int maxHeight = 400; // Set the maximum height of the image
    double widthRatio = static_cast<double>(maxWidth) / static_cast<double>(originalWidth);
    double heightRatio = static_cast<double>(maxHeight) / static_cast<double>(originalHeight);
    double ratio = std::min(widthRatio, heightRatio);
    int newWidth = static_cast<int>(originalWidth * ratio);
    int newHeight = static_cast<int>(originalHeight * ratio);

    // Scale the image to the new width and height
    pixbuf = pixbuf->scale_simple(newWidth, newHeight, Gdk::INTERP_BILINEAR);

    // Create a new Gtk::Image from the scaled image
    Gtk::Image *image = Gtk::manage(new Gtk::Image(pixbuf));
    boxImg.add(*image);

    int imageW = image->get_allocated_width();
    int imageH = image->get_allocated_height();

    alignButtons.add(boxButtons);
    boxButtons.pack_start(buttonConvert, false, false, 0);
    boxButtons.pack_start(buttonSave, false, false, 0);
}

void ConvertFile::setStyle()
{
    set_title("ASCII Convert");
    set_default_size(windowW, windowH);
    set_border_width(10);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
    set_visible(true);
    set_can_focus(false);
    set_resizable(false);

    fixedWindow.set_size_request(windowW, windowH);
    fixedWindow.set_visible(true);
    fixedWindow.set_can_focus(false);

    boxImg.set_visible(true);
    boxImg.set_can_focus(false);

    alignButtons.set_size_request(0, 0);
    alignButtons.set_visible(true);
    alignButtons.set_can_focus(false);
    alignButtons.set_border_width(10);

    boxButtons.set_visible(true);
    boxButtons.set_can_focus(false);

    buttonConvert.set_label("convert");
    buttonConvert.set_visible(true);
    buttonConvert.set_can_focus(false);
    buttonConvert.set_focus_on_click(true);
    buttonConvert.set_size_request(100, 10);
    buttonConvert.set_border_width(2);

    buttonSave.set_label("save");
    buttonSave.set_visible(true);
    buttonSave.set_can_focus(false);
    buttonSave.set_focus_on_click(true);
    buttonSave.set_size_request(100, 10);
    buttonSave.set_border_width(2);
    buttonSave.set_sensitive(false);
}

void ConvertFile::setBehaviour()
{
    buttonConvert.signal_clicked().connect(sigc::mem_fun(*this, &ConvertFile::buttonConvert_clicked));
    buttonSave.signal_clicked().connect(sigc::mem_fun(*this, &ConvertFile::buttonSave_clicked));
}

void ConvertFile::on_button_quit()
{
    close();
}

void ConvertFile::buttonConvert_clicked()
{
    buttonSave.set_sensitive(true);
    buttonConvert.set_sensitive(false);

    ImageConverter imageConverter(this->filePath);
    
    std::string newFileLocation = generateNewFileLocation(this->filePath);
    
    imageConverter.convertGrayScale();
    imageConverter.resize(100, 100);

    std::string ASCII_ART = imageConverter.getStringASCII();

    saveASCIIArtAsImage(ASCII_ART, 100, 100, 500, 500, newFileLocation);

}

void ConvertFile::buttonSave_clicked()
{
    buttonConvert.set_sensitive(false);
    buttonSave.set_sensitive(false);
}