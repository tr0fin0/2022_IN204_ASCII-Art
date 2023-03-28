#include <iostream>
#include <fstream>
#include <gtkmm.h>
#include "dimensions.h"
#include "../utils/utils.h"
#include "../networkConnection/server.h"
#include "WebConference.h"
#include "ConvertFile.h"
#include "Webcam.h"

class MainWindow : public Gtk::Window
{
public:
  // declarations with come after
  MainWindow(); // class constructor

  virtual ~MainWindow(); // class destructor

private:
  void setHierarchy();
  void setStyle();
  void setBehaviour();
  void on_button_quit();
  void buttonIP_clicked();
  void buttonConvert_clicked();
  void buttonWebcam_clicked();
  void buttonWebconference_clicked();

  // widgets declaration
  Gtk::Fixed fixedWindow;
  Gtk::Box boxImg, boxReturn, boxButtons;
  Gtk::Alignment alignReturn, alignButtons;
  Gtk::Style *style;
  Gtk::Widget *image;
  Gtk::Button buttonConvert, buttonWebcam, buttonWebconference, buttonIP;
};

MainWindow::MainWindow() : boxImg{Gtk::Orientation::ORIENTATION_VERTICAL},
                           boxReturn{Gtk::Orientation::ORIENTATION_VERTICAL},
                           boxButtons{Gtk::Orientation::ORIENTATION_VERTICAL}
{
  setHierarchy();
  setStyle();
  setBehaviour();

  show_all_children();
}

void MainWindow::setHierarchy()
{
  // Window
  add(fixedWindow);

  // Fixed
  fixedWindow.add(boxImg);
  fixedWindow.add(alignReturn);
  fixedWindow.add(alignButtons);
  fixedWindow.move(boxImg, boxImgX, boxImgY);
  fixedWindow.move(alignReturn, boxReturnX, boxReturnY);
  fixedWindow.move(alignButtons, boxButtonsX, boxButtonsY);

  // Image
  std::string mainImagePath = pathRel2Abs("images/waves.png");
  const char *mainImagePathConst = mainImagePath.c_str();
  image = Glib::wrap(gtk_image_new_from_file(mainImagePathConst), false);
  boxImg.add(*image);

  // Return
  alignReturn.add(boxReturn);
  boxReturn.pack_start(buttonIP, false, false, 0);

  // Buttons
  alignButtons.add(boxButtons);
  boxButtons.pack_start(buttonConvert, false, false, 0);
  boxButtons.pack_start(buttonWebcam, false, false, 0);
  boxButtons.pack_start(buttonWebconference, false, false, 0);
}

void MainWindow::setStyle()
{
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

  // buttonIP.set_label(getHostname());
  buttonIP.set_label("get IP");
  buttonIP.set_visible(true);
  buttonIP.set_can_focus(false);
  buttonIP.set_focus_on_click(true);
  buttonIP.set_size_request(buttonIPW, buttonIPH);
  buttonIP.set_border_width(buttonIPB);
  buttonIP.set_sensitive(true);

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

void MainWindow::setBehaviour()
{
  buttonIP.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::buttonIP_clicked));
  buttonConvert.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::buttonConvert_clicked));
  buttonWebcam.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::buttonWebcam_clicked));
  buttonWebconference.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::buttonWebconference_clicked));
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_quit()
{
  close();
}

void MainWindow::buttonIP_clicked()
{
  buttonIP.set_label(getHostname());
}


void MainWindow::buttonConvert_clicked()
{
  // Get the number of open windows
  Gtk::FileChooserDialog dialog("Please choose a file", Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_current_folder(pathRel2Abs("images"));

  // Add response buttons to the dialog
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("Open", Gtk::RESPONSE_OK);

  // Show the dialog and wait for a response
  int result = dialog.run();

  // Check if the user clicked the "Open" button
  if (result == Gtk::RESPONSE_OK)
  {
    // Get the selected file path from the dialog
    std::string file_path = dialog.get_filename();

    // Read the contents of the file
    std::ifstream file(file_path);
    if (file.is_open())
    {
      // close all open windows except this one
      auto windows = Gtk::Window::list_toplevels();
      for (auto window : windows)
      {
        if (window != this)
        {
          window->close();
        }
      }

      Gtk::Window *m_new_window = new ConvertFile(file_path);

      m_new_window->show_all();

      file.close();
    }
    else
    {
      std::cerr << "Failed to open file: " << file_path << std::endl;
    }
  }
}

void MainWindow::buttonWebcam_clicked()
{
  // close all open windows except this one
  auto windows = Gtk::Window::list_toplevels();
  for (auto window : windows)
  {
    if (window != this)
    {
      window->close();
    }
  }

  Webcam *m_new_window = new Webcam();

  // Show the new window
  m_new_window->show_all();
}

void MainWindow::buttonWebconference_clicked()
{
  // close all open windows except this one
  auto windows = Gtk::Window::list_toplevels();
  for (auto window : windows)
  {
    if (window != this)
    {
      window->close();
    }
  }

  WebConference *m_new_window = new WebConference();

  // Show the new window
  m_new_window->show_all();

  // std::thread loop_thread([&m_new_window]()
  //                         {
  //   while (true) {
  //     // Faça algo para atualizar a lista de caracteres ASCII, por exemplo, ler de uma webcam
  //     std::string ascii_text = "ASCII Art";

  //     // Atualize o TextView na thread principal
  //     m_new_window->updateAsciiText(ascii_text);

  //     // Aguarde um tempo antes de atualizar novamente
  //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //   } });
}
