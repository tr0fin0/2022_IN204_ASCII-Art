#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>

class ConvertFile : public Gtk::Window
{
public:
    ConvertFile(std::string pathFile);

private:
    void setHierarchy(std::string pathFile);
    void setStyle();
    void setBehaviour();
    void on_button_quit();
    void buttonConvert_clicked();
    void buttonSave_clicked();

    Gtk::Fixed fixedWindow;
    Gtk::Box boxImg, boxButtons;
    Gtk::Alignment alignButtons;
    Gtk::Widget *image;
    Gtk::Button buttonConvert, buttonSave;
};

ConvertFile::ConvertFile(std::string pathFile) : boxImg{Gtk::Orientation::ORIENTATION_VERTICAL},
                                                 boxButtons{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    setHierarchy(pathFile);
    setStyle();
    setBehaviour();

    show_all_children();
}

void ConvertFile::setHierarchy(std::string pathFile)
{
    int windowW = 1000;
    int windowH = 500;

    add(fixedWindow);
    fixedWindow.add(boxImg);
    fixedWindow.add(boxButtons);
    fixedWindow.move(boxImg, 0, 0);
    fixedWindow.move(boxButtons, 448, 224);

    const char *pathConst = pathFile.c_str();
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

private:
    void on_button_quit();

    Gtk::TextView *m_textview;
    std::string m_ascii_text;
    Glib::Dispatcher m_dispatcher;
};


void ConvertFile::on_button_quit()
{
    close();
}