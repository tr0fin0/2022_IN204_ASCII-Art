#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>
// #include "../converters/VideoConverter.h"
// #include "../converters/ImageConverter.h"
// #include "../converters/Converter.h"

class Webcam : public Gtk::Window
{
public:
    Webcam()
    {
        int windowW = 500;
        int windowH = 500;

        m_textview = Gtk::manage(new Gtk::TextView());
        m_textview->set_editable(true);
        m_textview->set_cursor_visible(false);
        m_buffer = m_textview->get_buffer();

        add(*m_textview);

        set_title("ASCII Webcam");
        set_default_size(windowW, windowH);
        set_border_width(10);
        set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
        set_visible(true);
        set_can_focus(false);
        set_resizable(false);

        m_dispatcher.connect([this]()
                             { m_buffer->set_text(m_ascii_text); });

        m_thread = std::thread([this]()
                               {
            while (true)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                std::string new_text = get_new_text();

                m_ascii_text = new_text;
                m_dispatcher.emit();
            } });
        show_all_children();
    }

    ~Webcam()
    {
        if (m_thread.joinable())
        {
            m_thread.join();
        }
    }

private:
    Gtk::TextView *m_textview;
    Glib::RefPtr<Gtk::TextBuffer> m_buffer;
    std::string m_ascii_text;
    Glib::Dispatcher m_dispatcher;
    std::thread m_thread;

    std::string get_new_text();
    void on_button_quit();
};

void Webcam::on_button_quit()
{
    close();
}

std::string Webcam::get_new_text()
{
    // Get new text from somewhere, e.g. a file, a network connection, etc.
    // For this example, just return a static string.
    // cv::VideoCapture cap(0);
    // cv::Mat img;
    // Converter c;
    // cap.read(img);

    // system("cls || clear");

    // c.setImage(img);
    // c.convertGrayScale();

    // c.resize(65, 50);

    // c.print_ASCII(c.parallelConvert(c.getImage(), 1, 3));


    // return c.getStringASCII();
    return "constant";
}

// class Webcam : public Gtk::Window
// {
// public:
//     Webcam()
//     {
//         int windowW = 500;
//         int windowH = 500;

//         m_textview = Gtk::manage(new Gtk::TextView());
//         m_textview->set_editable(false);
//         m_textview->set_cursor_visible(false);
//         m_textview->set_size_request(windowW, windowH);

//         Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
//         box->pack_start(*m_textview, false, false, 0);
//         box->set_size_request(windowW, windowH);

//         add(*box);

//         set_title("ASCII Webcam");
//         set_default_size(windowW, windowH);
//         set_border_width(10);
//         set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
//         set_visible(true);
//         set_can_focus(false);
//         set_resizable(false);

//         m_dispatcher.connect([this]()
//                              {
//             Glib::RefPtr<Gtk::TextBuffer> buffer = m_textview->get_buffer();
//             buffer->set_text(m_ascii_text); });
//     }

//     void updateAsciiText(const std::string &ascii_text)
//     {
//         m_ascii_text = ascii_text;
//         m_dispatcher.emit();
//     }

// private:
//     void on_button_quit();

//     Gtk::TextView *m_textview;
//     std::string m_ascii_text;
//     Glib::Dispatcher m_dispatcher;
// };
