#include <iostream>
#include <gtkmm.h>
#include "../utils/utils.h"
#include "../networkConnection/server.h"

class mainWindow : public Gtk::Window
{
public:
  mainWindow();
  virtual ~mainWindow();

private:
  // Signal handlers:
  void on_button_quit();
  void on_button_numbered(const Glib::ustring& data);

  // Child widgets:
  Gtk::Style *style;
  Gtk::Widget *image;
  Gtk::Grid m_grid;
  Gtk::Button buttonConvert, buttonWebcam, buttonWebconference, buttonQuit;
  Gtk::Box box1;
};



mainWindow::mainWindow():
  buttonConvert("Convert from File"),
  buttonWebcam("Webcam"),
  buttonWebconference("Webconference"),
  buttonQuit("Quit")
{


  set_title("ASCII Art");
  set_border_width(15);
  set_default_size(1080, 720);



  std::string mainImagePath = pathRel2Abs("images/waves.png");
  const char * mainImagePathConst = mainImagePath.c_str();

  image  = Glib::wrap(gtk_image_new_from_file(mainImagePathConst), false);
  // image  = Glib::wrap(gtk_image_new_from_file("/home/gustavo/Documentos/facul/ENSTA/GLObjOri/ASCII-Art/images/waves.png"), false);
  // image  = Glib::wrap(gtk_image_new_from_file("/home/tr0fin0/Documents/git_repositories/ASCII-Art/images/waves.png"), false);


  add(m_grid);
  m_grid.add(buttonConvert);
  m_grid.add(buttonWebcam);
  m_grid.add(buttonWebconference);
  m_grid.attach(*image, 0, 0, 1, 1);
  m_grid.attach(buttonConvert, 1, 0, 1, 1);
  m_grid.attach(buttonWebcam, 2, 0, 1, 1);
  m_grid.attach(buttonWebconference, 3, 0, 1, 1);
  // m_grid.attach_next_to(*image, buttonConvert, Gtk::POS_TOP, 2, 1);
  // m_grid.attach_next_to(buttonQuit, buttonConvert, Gtk::POS_BOTTOM, 2, 1);

  buttonConvert.signal_clicked().connect(
    sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
      &mainWindow::on_button_numbered), "button 1") );


  buttonWebcam.signal_clicked().connect(
    sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
      &mainWindow::on_button_numbered), "button 2") );


  buttonQuit.signal_clicked().connect(sigc::mem_fun(*this,
    &mainWindow::on_button_quit) );

  show_all_children();
}

mainWindow::~mainWindow()
{
}

void mainWindow::on_button_quit()
{
  hide();
}

void
mainWindow::on_button_numbered(const Glib::ustring& data)
{
  std::cout << data << " was pressed" << std::endl;
}