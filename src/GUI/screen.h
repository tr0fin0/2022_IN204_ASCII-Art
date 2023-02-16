#include <iostream>
#include <gtkmm.h>
#include "../utils/utils.h"
#include "../networkConnection/server.h"
// #include "../networkConnection/tcp_s.cpp"

class mainWindow : public Gtk::Window 
{
public:
  // declarations with come after
  mainWindow();           // class constructor

  void setHierarchy();    // setup widgets hierarchy
  void setStyle();        // setup widgets style
  void setBehaviour();    // setup widgets behaviour

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
  Gtk::Button buttonConvert, buttonWebcam, buttonWebconference, buttonReturn;
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
  setStyle();
  setBehaviour();

  show_all_children();
}



void mainWindow::setHierarchy()
{
  // Window
  add(fixedWindow);


  // Fixed
  fixedWindow.add(boxImg);
  fixedWindow.add(boxReturn);
  fixedWindow.add(boxButtons);
  fixedWindow.move(boxImg,      10, 10);
  fixedWindow.move(boxReturn,   10, 10);
  fixedWindow.move(boxButtons,  200, 200);


  // Image
  std::string mainImagePath = pathRel2Abs("images/waves.png");
  const char * mainImagePathConst = mainImagePath.c_str();
  image  = Glib::wrap(gtk_image_new_from_file(mainImagePathConst), false);

  boxImg.add(*image);


  // Return
  alignReturn.add(boxReturn);
  boxReturn.pack_start(buttonReturn, true, true, 0);


  // Buttons
  alignButtons.add(boxButtons);
  boxButtons.pack_start(buttonConvert, true, true, 0);
  boxButtons.pack_start(buttonWebcam, true, true, 0);
  boxButtons.pack_start(buttonWebconference, true, true, 0);
}



void mainWindow::setStyle(){
  set_title("ASCII Art");
  set_default_size(1080, 720);
  set_border_width(10);
  set_visible(true);
  set_can_focus(false);

  // Fixed
  fixedWindow.set_size_request(1080, 720);
  fixedWindow.set_visible(true);
  fixedWindow.set_can_focus(false);


  // Image
  boxImg.set_visible(true);
  boxImg.set_can_focus(false);


  // Return
  alignReturn.set_size_request(200, 100);
  alignReturn.set_visible(true);
  alignReturn.set_can_focus(false);
  alignReturn.set_border_width(10);

  boxReturn.set_visible(true);
  boxReturn.set_can_focus(false);

  buttonReturn.set_label("back");
  buttonReturn.set_visible(true);
  buttonReturn.set_can_focus(false);
  buttonReturn.set_focus_on_click(true);
  buttonReturn.set_border_width(10);


  // Buttons
  alignButtons.set_size_request(400, 400);
  alignButtons.set_visible(true);
  alignButtons.set_can_focus(false);
  alignButtons.set_border_width(10);

  boxButtons.set_visible(true);
  boxButtons.set_can_focus(false);

  buttonConvert.set_label("convert");
  buttonConvert.set_visible(true);
  buttonConvert.set_can_focus(false);
  buttonConvert.set_focus_on_click(true);
  buttonConvert.set_border_width(2);

  buttonWebcam.set_label("webcam");
  buttonWebcam.set_visible(true);
  buttonWebcam.set_can_focus(false);
  buttonWebcam.set_focus_on_click(true);
  buttonWebcam.set_border_width(2);

  buttonWebconference.set_label("webconference");
  buttonWebconference.set_visible(true);
  buttonWebconference.set_can_focus(false);
  buttonWebconference.set_focus_on_click(true);
  buttonWebconference.set_border_width(2);
}


void mainWindow::setBehaviour(){

}



mainWindow::~mainWindow()
{
}


void mainWindow::on_button_quit()
{
  hide();
}

void mainWindow::on_button_numbered(const Glib::ustring& data)
{
  std::cout << data << " was pressed" << std::endl;
}


  // buttonConvert.signal_clicked().connect(
  //   sigc::bind<Glib::ustring>(sigc::mem_fun(*this,
  //     &mainWindow::on_button_numbered), "button 1") );


  // buttonWebcam.signal_clicked().connect(
  //   sigc::bind<Glib::ustring>( sigc::mem_fun(*this,
  //     &mainWindow::on_button_numbered), "button 2") );


  // buttonQuit.signal_clicked().connect(sigc::mem_fun(*this,
  //   &mainWindow::on_button_quit) );

  // show_all_children();