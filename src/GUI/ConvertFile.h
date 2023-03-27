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

        const char *pathConst = pathFile.c_str();
        Gtk::Widget *image = Glib::wrap(gtk_image_new_from_file(pathConst), false);

        set_title("ASCII Convert");
        set_default_size(windowW, windowH);
        set_border_width(10);
        set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
        set_visible(true);
        set_can_focus(false);
        set_resizable(false);
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