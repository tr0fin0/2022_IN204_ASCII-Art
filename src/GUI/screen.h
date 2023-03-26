#include <iostream>
#include <gtkmm.h>
#include "dimensions.h"
#include "../utils/utils.h"
#include "../networkConnection/server.h"
#include "WebConference.h"

class mainWindow : public Gtk::Window 
{
public:
  // declarations with come after
  mainWindow();           // class constructor
  // Gtk::Window:set_resizable(mainWindow, false)

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
  set_default_size(windowW, windowH);
  set_border_width(windowB);
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
  fixedWindow.move(boxImg, boxImgX, boxImgY);
  fixedWindow.move(boxReturn, boxReturnX, boxReturnY);
  fixedWindow.move(boxButtons, boxButtonsX, boxButtonsY);


  // Image
  std::string mainImagePath = pathRel2Abs("images/waves.png");
  const char * mainImagePathConst = mainImagePath.c_str();
  image  = Glib::wrap(gtk_image_new_from_file(mainImagePathConst), false);

  boxImg.add(*image);

  // const GdkPixbuf *pb = gtk_image_get_pixbuf(GTK_IMAGE(image));
  // printf("image is %ux%u pixels\n", gdk_pixbuf_get_width(pb), gdk_pixbuf_get_height(pb));
  // printf(image->get_height());
  // std::cout << image->get_height();


  // Return
  alignReturn.add(boxReturn);
  boxReturn.pack_start(buttonReturn, false, false, 0);


  // Buttons
  alignButtons.add(boxButtons);
  boxButtons.pack_start(buttonConvert, false, false, 0);
  boxButtons.pack_start(buttonWebcam, false, false, 0);
  boxButtons.pack_start(buttonWebconference, false, false, 0);
}



void mainWindow::setStyle(){
  set_title("ASCII Art");
  set_default_size(windowW, windowH);
  set_border_width(windowB);
  set_position(Gtk::WindowPosition::WIN_POS_CENTER_ALWAYS);
  set_visible(true);
  set_can_focus(false);
  set_resizable(false);

  // Fixed
  fixedWindow.set_size_request(windowW, windowH);
  fixedWindow.set_visible(true);
  fixedWindow.set_can_focus(false);


  // Image
  boxImg.set_visible(true);
  boxImg.set_can_focus(false);


  // Return
  alignReturn.set_size_request(alignReturnW, alignReturnH);
  alignReturn.set_visible(true);
  alignReturn.set_can_focus(false);
  alignReturn.set_border_width(alignReturnB);

  boxReturn.set_visible(true);
  boxReturn.set_can_focus(false);

  buttonReturn.set_label("back");
  buttonReturn.set_visible(true);
  buttonReturn.set_can_focus(false);
  buttonReturn.set_focus_on_click(true);
  buttonReturn.set_size_request(buttonReturnW, buttonReturnH);
  buttonReturn.set_border_width(buttonReturnB);


  // Buttons
  alignButtons.set_size_request(alignButtonsW, alignButtonsH);
  alignButtons.set_visible(true);
  alignButtons.set_can_focus(false);
  alignButtons.set_border_width(alignButtonsB);

  boxButtons.set_visible(true);
  boxButtons.set_can_focus(false);

  buttonConvert.set_label("convert");
  buttonConvert.set_visible(true);
  buttonConvert.set_can_focus(false);
  buttonConvert.set_focus_on_click(true);
  buttonConvert.set_size_request(buttonsW, buttonsH);
  buttonConvert.set_border_width(buttonsB);

  buttonWebcam.set_label("webcam");
  buttonWebcam.set_visible(true);
  buttonWebcam.set_can_focus(false);
  buttonWebcam.set_focus_on_click(true);
  buttonWebcam.set_size_request(buttonsW, buttonsH);
  buttonWebcam.set_border_width(buttonsB);

  buttonWebconference.set_label("webconference");
  buttonWebconference.set_visible(true);
  buttonWebconference.set_can_focus(false);
  buttonWebconference.set_focus_on_click(true);
  buttonWebconference.set_size_request(buttonsW, buttonsH);
  buttonWebconference.set_border_width(buttonsB);
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

void mainWindow::buttonWebconference_clicked()
{
  // Close all open windows except this one
  auto windows = Gtk::Window::list_toplevels();
  for (auto window : windows)
  {
    if (window != this)
    {
      window->close();
    }
  }

  // Gtk::Window* m_new_window = Gtk::manage(new mainWindow());
  Gtk::Window *m_new_window = Gtk::manage(new WebConference());
  // WebConference m_new_window;

  // Show the new window
  m_new_window->show_all();
  // m_new_window.show_all();

  // std::thread loop_thread([&m_new_window]() {
  //     while (true) {
  //         // Faça algo para atualizar a lista de caracteres ASCII, por exemplo, ler de uma webcam
  //         std::string ascii_text = "ASCII Art";

  //         // Atualize o TextView na thread principal
  //         m_new_window.updateAsciiText(ascii_text);

  //         // Aguarde um tempo antes de atualizar novamente
  //         std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //     }
  // });

  std::cout << "conference" << std::endl;
}

  // show_all_children();