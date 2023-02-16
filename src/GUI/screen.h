#include <iostream>
#include <gtkmm.h>
#include "../utils/utils.h"
#include "../networkConnection/server.h"

class mainWindow : public Gtk::Window 
{
public:
  // declarations with come after
  mainWindow();           // class constructor

  void setHierarchy();    // class widgets hierarchy
  void setWidgets();      // class widgets setup

  virtual ~mainWindow();  // class destructor


private:
  // action handlers
  void on_button_quit();
  void on_button_numbered(const Glib::ustring& data);

  // widgets declaration
  Gtk::Fixed fixedWindow;                   // window main fixed
  Gtk::Box boxImg, boxReturn, boxButtons;
  Gtk::Alignment alignReturn, alignButtons;
  Gtk::Entry entryIP;                       // input from user
  Gtk::Label labelIP, labelLinks;
  Gtk::Style  *style;                       // images
  Gtk::Widget *image;
  Gtk::Button buttonConvert, buttonWebcam, buttonWebconference, buttonQuit;
};



mainWindow::mainWindow():
  boxImg{Gtk::Orientation::ORIENTATION_VERTICAL},
  boxReturn{Gtk::Orientation::ORIENTATION_VERTICAL},
  boxButtons{Gtk::Orientation::ORIENTATION_VERTICAL} 
{
  set_title("ASCII Art");
  set_default_size(1080, 720);
  set_border_width(15);
  set_visible(true);

  setHierarchy();
  setWidgets();
  show_all_children();
}



void mainWindow::setHierarchy()
{

  std::string mainImagePath = pathRel2Abs("images/waves.png");
  const char * mainImagePathConst = mainImagePath.c_str();

  image  = Glib::wrap(gtk_image_new_from_file(mainImagePathConst), false);
  // image  = Glib::wrap(gtk_image_new_from_file("/home/gustavo/Documentos/facul/ENSTA/GLObjOri/ASCII-Art/images/waves.png"), false);
  // image  = Glib::wrap(gtk_image_new_from_file("/home/tr0fin0/Documents/git_repositories/ASCII-Art/images/waves.png"), false);

  // Window
  add(fixedWindow);
  // add(fixed);

  // Fixed
  fixedWindow.add(boxImg)
  fixedWindow.add(boxReturn)
  fixedWindow.add(boxButtons)
  fixedWindow.move(boxImg,      10, 10)
  fixedWindow.move(boxReturn,   10, 10)
  fixedWindow.move(boxButtons,  200, 200)
  // m_grid.add(buttonConvert);
  // m_grid.add(buttonWebcam);
  // m_grid.add(buttonWebconference);
  // m_grid.attach(*image, 0, 0, 1, 1);
  // m_grid.attach(buttonConvert, 1, 0, 1, 1);
  // m_grid.attach(buttonWebcam, 2, 0, 1, 1);
  // m_grid.attach(buttonWebconference, 3, 0, 1, 1);
  // m_grid.attach_next_to(*image, buttonConvert, Gtk::POS_TOP, 2, 1);
  // m_grid.attach_next_to(buttonQuit, buttonConvert, Gtk::POS_BOTTOM, 2, 1);


  // Frame 1




  // buttonConvert.signal_clicked().connect(
  //   sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
  //     &mainWindow::on_button_numbered), "button 1") );


  // buttonWebcam.signal_clicked().connect(
  //   sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
  //     &mainWindow::on_button_numbered), "button 2") );


  // buttonQuit.signal_clicked().connect(sigc::mem_fun(*this,
  //   &mainWindow::on_button_quit) );

  // show_all_children();
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