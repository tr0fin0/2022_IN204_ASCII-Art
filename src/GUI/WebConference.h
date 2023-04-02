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


class WebConference : public Gtk::Window
{
public:
    //WebConference constructor
    //server -> isServer == 1 | otherwise -> client
    //if client, 
    WebConference(int isServer, char* server_IP_address = NULL)
    {
        this->isServer = isServer;
        this->server_IP_address = server_IP_address;

        setHierarchy();
        setStyle();
        setBehaviour();
        
        std::string asciiWaiting;
        if(isServer == 1)
            asciiWaiting = getWaiting();
        else
            asciiWaiting = getEntering();

        m_buffer->set_text(asciiWaiting);

        if(isServer == 1){
            receiving = true;
            t2 = std::thread(receiveFromClient, &m_ascii_text, &m_dispatcher, &receiving);
            sending = true;
            t1 = std::thread(sendToClient, &sending);

        }else{
            sending = true;
            t1 = std::thread(sendToServer, server_IP_address, &sending);
            receiving = true;
            t2 = std::thread(receiveFromServer, server_IP_address, &m_ascii_text, &m_dispatcher, &receiving);
        }

        show_all_children();
    }

    ~WebConference()
    {
        t1.join();
        t2.join();
    }

private:
    void setHierarchy();
    void setStyle();
    void setBehaviour();
    void on_button_quit();

    Gtk::Fixed fixedWindow;
    Gtk::Button buttonQuit;
    Gtk::Alignment alignButtonText;
    Gtk::Box boxButtonText;

    std::thread t1, t2;
    Gtk::TextView *m_textview;
    std::string m_ascii_text;
    Glib::Dispatcher m_dispatcher;
    Glib::RefPtr<Gtk::TextBuffer> m_buffer;
    
    bool receiving = false, sending = false;
    int isServer;
    const char* server_IP_address;

};

void WebConference::setBehaviour(){
    buttonQuit.signal_clicked().connect(sigc::mem_fun(*this, &WebConference::on_button_quit));
}

void WebConference::on_button_quit()
{   
    if(sending){
        sending = false;
        t1.join();
    }
    if(receiving){
        receiving = false;
        t2.join();
    }
    close();
}

void WebConference::setHierarchy(){
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


void WebConference::setStyle(){
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
    buttonQuit.set_label("End Meeting");
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

    set_title("ASCII Web Conference");
    set_border_width(10);
    set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
    set_visible(true);
    set_can_focus(false);
    set_resizable(false);
    set_deletable(false);

    m_dispatcher.connect([this](){ 
        m_buffer->set_text(m_ascii_text); 
    });
}

