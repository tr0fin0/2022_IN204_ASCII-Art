#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>

class ConvertFile : public Gtk::Window
{
public:
    ConvertFile(std::string pathFile)
    {
        int windowW = 500;
        int windowH = 500;

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