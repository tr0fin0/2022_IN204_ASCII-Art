#include <gtkmm.h>
#include <glibmm/dispatcher.h>
#include <thread>
#include <chrono>

class WebConference : public Gtk::Window
{
public:
    WebConference()
    {
        int windowW = 500;
        int windowH = 500;

        m_textview = Gtk::manage(new Gtk::TextView());
        m_textview->set_size_request(windowW, windowH);

        Gtk::Box *box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
        box->pack_start(*m_textview, false, false, 0);
        box->set_size_request(windowW, windowH);

        add(*box);

        set_title("ASCII Conference");
        set_default_size(windowW, windowH);
        set_border_width(10);
        set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
        set_visible(true);
        set_can_focus(false);
        set_resizable(false);

        m_dispatcher.connect([this]()
                             {
            Glib::RefPtr<Gtk::TextBuffer> buffer = m_textview->get_buffer();
            buffer->set_text(m_ascii_text); });
    }

    void updateAsciiText(const std::string &ascii_text)
    {
        m_ascii_text = ascii_text;
        m_dispatcher.emit();
    }

private:
    void on_button_quit();

    Gtk::TextView *m_textview;
    std::string m_ascii_text;
    Glib::Dispatcher m_dispatcher;
};

void WebConference::on_button_quit()
{
    // hide();
    close();
}