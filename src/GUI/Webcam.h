#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>
#include <uchardet/uchardet.h>

#include <glib.h>
#include <iconv.h>
#include <iostream>
#include <string>
#include <cstring>
// #include "../converters/VideoConverter.h"
// #include "../converters/ImageConverter.h"
// #include "../converters/Converter.h"

class Webcam : public Gtk::Window
{
public:
    Webcam()
    {
        int windowW = 1000;
        int windowH = 1000;

        m_textview = Gtk::manage(new Gtk::TextView());
        m_textview->set_editable(true);
        m_textview->set_cursor_visible(false);
        m_buffer = m_textview->get_buffer();

        m_buffer->set_property("monospace", true);

        m_textview->override_font(Pango::FontDescription("Monospace 12"));
        m_textview->set_justification(Gtk::JUSTIFY_CENTER);

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
                                   cv::VideoCapture cap(0);
                                   cv::Mat img;
                                   while (true)
                                   {
                                       std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                       // std::string new_text = get_new_text();
                                       Converter c;
                                       cap.read(img);

                                       // system("cls || clear");

                                       c.setImage(img);
                                       c.convertGrayScale();

                                       c.resize(50, 50);
                                       // c.print_ASCII(c.parallelConvert(c.getImage(), 1, 3));

                                       // #include <glib.h>

                                       // bool is_valid_utf8(const std::string& str) {
                                       //     return g_utf8_validate(str.c_str(), str.length(), NULL);
                                       // }

                                       // return "constant\nconstant\n\nconstant";
                                       std::string str = c.getStringASCII();

                                       // std::cout << g_utf8_validate(str.c_str(), str.length(), NULL) << std::endl;

                                       // // const char* invalidString = "This is an invalid string\x80";
                                       // std::string validString;
                                       // validString.assign(str, strlen(str.c_str()));
                                       // std::cout << "Invalid string:\n"
                                       //           << str << std::endl;
                                       // std::cout << "Valid string:\n"
                                       //           << validString << std::endl;

                                       uchardet_t ud = uchardet_new();
                                       uchardet_handle_data(ud, str.c_str(), str.size());
                                       uchardet_data_end(ud);
                                       const char *encoding = uchardet_get_charset(ud);
                                       std::string result(encoding);
                                       // std::cout << "encoding: " << encoding << std::endl;
                                       uchardet_delete(ud);

                                       // Create an iconv descriptor for the conversion
                                       iconv_t cd = iconv_open("UTF-8", "ASCII");

                                       std::string ascii_str = str;

                                       // Get the length of the input and output strings
                                       size_t in_len = ascii_str.length();
                                       size_t out_len = in_len * 4; // Maximum possible size for UTF-8

                                       // Allocate memory for the output string
                                       char *out_buf = new char[out_len + 1];

                                       // Convert the string
                                       char *in_ptr = const_cast<char *>(ascii_str.c_str());
                                       char *out_ptr = out_buf;
                                       if (iconv(cd, &in_ptr, &in_len, &out_ptr, &out_len) == (size_t)-1)
                                       {
                                           perror("iconv");
                                           exit(EXIT_FAILURE);
                                       }

                                       // Null-terminate the output string
                                       *out_ptr = '\0';

                                       // Clean up
                                       iconv_close(cd);
                                       std::string utf8_str(out_buf);
                                       delete[] out_buf;
                                       // std::cout << "utf8_str:\n" << utf8_str << std::endl;
                                       // return str;
                                       // return utf8_str;

                                       // m_ascii_text = new_text;
                                       m_ascii_text = utf8_str;
                                       m_dispatcher.emit();
                                   }
                                   // cap.release(); // TODO kill camera input after closing window
                               });
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

    // std::string get_new_text();
    void on_button_quit();
};

void Webcam::on_button_quit()
{
    close();
}

// std::string Webcam::get_new_text()
// {
//     // Get new text from somewhere, e.g. a file, a network connection, etc.
//     // For this example, just return a static string.
//     return "true";
// }
