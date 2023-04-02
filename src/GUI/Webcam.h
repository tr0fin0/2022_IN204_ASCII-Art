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


class Webcam : public Gtk::Window
{
public:
    Webcam()
    {
        setHierarchy();
        setStyle();
        setBehaviour();

        m_thread = std::thread([this]()
        {
            cv::Mat img;
            Converter c;
            cv::VideoCapture cap(0);

            while (this->isRunning)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(41));
                
                cap.read(img);
                c.setImage(img);
                c.convertGrayScale();

                c.resize(250, 100);

                std::string str = c.getStringASCII();

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

                if(this->isRunning){
                    m_ascii_text = utf8_str;
                    m_dispatcher.emit();
                }
            }
            
            cap.release(); // kill camera input after closing window
        });

        show_all_children();
    }
    ~Webcam(){}
private:
    void setHierarchy();
    void setStyle();
    void setBehaviour();
    
    Gtk::Fixed fixedWindow;
    Gtk::Button buttonQuit;
    Gtk::Alignment alignButtonText;
    Gtk::Box boxButtonText;

    Gtk::TextView *m_textview;
    Glib::RefPtr<Gtk::TextBuffer> m_buffer;
    std::string m_ascii_text;
    Glib::Dispatcher m_dispatcher;
    std::thread m_thread;
    bool isRunning;

    void on_button_quit();
};

void Webcam::setHierarchy(){
    // Window
    add(fixedWindow);

    // Fixed
    fixedWindow.add(alignButtonText);
        
    //align
    alignButtonText.add(boxButtonText);


    m_textview = Gtk::manage(new Gtk::TextView());
    m_textview->set_editable(true);
    m_textview->set_size_request(1000, 800);
    m_textview->set_cursor_visible(false);
    m_buffer = m_textview->get_buffer();
    m_textview->override_font(Pango::FontDescription("Monospace 5"));

    //box
    boxButtonText.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
    boxButtonText.pack_start(*m_textview,  false, false, 0);
    boxButtonText.pack_start(buttonQuit,  false, false, 0);
}

void Webcam::setStyle(){
    int windowW = 1000;
    int windowH = 900;

    // Fixed
    fixedWindow.set_size_request(windowW, windowH);
    fixedWindow.set_visible(true);
    fixedWindow.set_can_focus(false);

    // boxButtonText
    boxButtonText.set_visible(true);
    boxButtonText.set_can_focus(false);

    // buttonQuit
    buttonQuit.set_label("Close WebCam");
    buttonQuit.set_visible(true);
    buttonQuit.set_can_focus(false);
    buttonQuit.set_focus_on_click(true);
    buttonQuit.set_size_request(10, 10);
    buttonQuit.set_border_width(10);
    buttonQuit.set_sensitive(true);

    // AlignButtonText
    //alignButtonText.set_size_request(-1, -1);
    alignButtonText.set_visible(true);
    alignButtonText.set_can_focus(false);
    alignButtonText.set_border_width(0);

    boxButtonText.set_visible(true);
    boxButtonText.set_can_focus(false);
    m_textview->set_justification(Gtk::JUSTIFY_CENTER);

    set_title("ASCII Webcam");
    set_border_width(10);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
    set_visible(true);
    set_can_focus(false);
    set_resizable(false);
    set_deletable(false);

    m_dispatcher.connect([this](){ 
        m_buffer->set_text(m_ascii_text); 
    });

    isRunning = true;
}

void Webcam::setBehaviour(){
    buttonQuit.signal_clicked().connect(sigc::mem_fun(*this, &Webcam::on_button_quit));
}

void Webcam::on_button_quit()
{   
    this->isRunning = false;
    m_thread.join();
    close();
}

