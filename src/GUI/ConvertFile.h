#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>
#include <gdkmm/pixbuf.h>
// #include "../converters/ImageConverter.h"

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
    Gtk::Box boxImg, boxConvert, boxButtons;
    Gtk::Alignment alignButtons;
    Gtk::Widget *image, *imageConvert;
    Gtk::Button buttonConvert, buttonSave;
};

ConvertFile::ConvertFile(std::string filePath) : boxImg{Gtk::Orientation::ORIENTATION_VERTICAL},
                                                 boxConvert{Gtk::Orientation::ORIENTATION_VERTICAL},
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
    fixedWindow.add(boxConvert);
    fixedWindow.add(alignButtons);
    fixedWindow.move(boxImg, 0, 0);
    fixedWindow.move(boxConvert, 600, 0);
    fixedWindow.move(alignButtons, 440, 160);

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

    int imageW = pixbuf->get_width();
    int imageH = pixbuf->get_height();
    // fixedWindow.move(boxImg, 0,10);
    fixedWindow.move(boxImg, (400 - imageW) / 2, (400 - imageH) / 2);

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

    boxConvert.set_visible(false);
    boxConvert.set_can_focus(false);

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

    // Load the image
    // const char *pathConst = this->filePath.c_str();
    Glib::RefPtr<Gdk::Pixbuf> pixbufOriginal = Gdk::Pixbuf::create_from_file(this->filePath.c_str());

    // Get the original width and height of the image
    int originalW = pixbufOriginal->get_width();
    int originalH = pixbufOriginal->get_height();

    ImageConverter imageConverter(this->filePath);

    std::string newFileLocation = generateNewFileLocation(this->filePath);

    imageConverter.convertGrayScale();
    imageConverter.resize(originalW / 4, originalH / 4);

    std::string ASCII_ART = imageConverter.getStringASCII();

    saveASCIIArtAsImage(ASCII_ART, originalW / 4, originalH / 4, originalW, originalH, newFileLocation);

    const char *pathConst = newFileLocation.c_str();
    imageConvert = Glib::wrap(gtk_image_new_from_file(pathConst), false);

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
    Gtk::Image *imageConvert = Gtk::manage(new Gtk::Image(pixbuf));
    int imageW = pixbuf->get_width();
    int imageH = pixbuf->get_height();

    boxConvert.add(*imageConvert);
    fixedWindow.move(boxConvert, 600 + (400 - imageW) / 2, (400 - imageH) / 2);
    boxConvert.set_visible(true);

    fixedWindow.show_all();
}

void ConvertFile::buttonSave_clicked()
{
    buttonConvert.set_sensitive(false);
    buttonSave.set_sensitive(false);

        Gtk::FileChooserDialog dialog("Save Image", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Save", Gtk::RESPONSE_OK);

    // Set the default file name and filter
    dialog.set_current_name("image.png");
    dialog.set_filter(Gtk::FileFilter::create());
    dialog.get_filter()->set_name("PNG Images");
    dialog.get_filter()->add_mime_type("image/png");

    // Show the dialog and wait for a response
    int result = dialog.run();

    // If the user selects a file and clicks the "Save" button
    if (result == Gtk::RESPONSE_OK) {
      // Get the selected file path
      std::string filename = dialog.get_filename();

      // Load the image from a file
      std::string imagePath = "image.jpg";
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(imagePath);

      // Scale the image to a desired size while preserving aspect ratio
      int desiredWidth = 800;
      int desiredHeight = 600;
      double aspectRatio = (double)pixbuf->get_width() / (double)pixbuf->get_height();
      if (aspectRatio > 1.0) {
        // Landscape image
        desiredHeight = (int)((double)desiredWidth / aspectRatio);
      } else {
        // Portrait image
        desiredWidth = (int)((double)desiredHeight * aspectRatio);
      }
      pixbuf = pixbuf->scale_simple(desiredWidth, desiredHeight, Gdk::INTERP_BILINEAR);

      // Save the scaled image to the selected file
      pixbuf->save(filename, "png");
    }
}