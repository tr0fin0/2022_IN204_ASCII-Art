#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <iostream>
#include <gtkmm.h>
#include "../networkConnection/server.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

private:
  // Signal handlers:
  void on_button_quit();
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Style *style;
  Gtk::Widget *image;
  Gtk::Grid m_grid;
  Gtk::Button m_button_1, m_button_2, m_button_quit;
};


ExampleWindow::ExampleWindow()
: m_button_1("Image Convertion"),
  m_button_2("Video Convertion"),
  m_button_quit("Quit")
{


  set_title("Gtk::Grid");
  set_border_width(12);
  set_default_size(500, 400);

  image  = Glib::wrap(gtk_image_new_from_file("/home/gustavo/Documentos/facul/ENSTA/GLObjOri/ASCII-Art/images/waves.png"), false);
  
  add(m_grid);
  m_grid.add(m_button_1);
  m_grid.add(m_button_2);
  m_grid.attach_next_to(*image, m_button_1, Gtk::POS_TOP, 2, 1);
  m_grid.attach_next_to(m_button_quit, m_button_1, Gtk::POS_BOTTOM, 2, 1);

  m_button_1.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &ExampleWindow::on_button_numbered), "button 1") );
  m_button_2.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &ExampleWindow::on_button_numbered), "button 2") );

  m_button_quit.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_quit) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}

void
ExampleWindow::on_button_numbered(const Glib::ustring& data)
{
  std::cout << data << " was pressed" << std::endl;
}

#endif