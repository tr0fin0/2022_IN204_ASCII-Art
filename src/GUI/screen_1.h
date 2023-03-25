#include <iostream>
#include <gtkmm.h>
#include "../utils/utils.h"
#include "../networkConnection/server.h"

class mainWindow : public Gtk::Window
{
public:
  mainWindow();
  void set_hierarchy();
  void draw_widgets();
  virtual ~mainWindow();

private:
  // Signal handlers:
  void on_button_quit();
  void on_button_importer();
  void on_button_exporter();

  // Child widgets:
  // example code
  Gtk::Fixed m_fixed;
  Gtk::Box m_box1, m_box2, m_box3, m_box4;
  Gtk::Alignment m_align1, m_align2;
  Gtk::Entry m_entry1, m_entry2, m_entry3;
  Gtk::Label m_label1, m_label2, m_label3, m_label4, m_label5, m_label6;
  Gtk::Button m_button1, m_button2;
  Gtk::Frame m_frame1, m_frame2;
  Gtk::LinkButton m_linkbutton;
};



mainWindow::mainWindow():
  m_box1{Gtk::Orientation::ORIENTATION_VERTICAL},
  m_box2{Gtk::Orientation::ORIENTATION_VERTICAL},
  m_box3{Gtk::Orientation::ORIENTATION_VERTICAL},
  m_box4{Gtk::Orientation::ORIENTATION_VERTICAL}
{
  set_title("ASCII Art");
  set_default_size(300, 400);
  // set_border_width(15);
  set_visible(true);

  set_hierarchy();
  draw_widgets();
  show_all_children();
}


void mainWindow::set_hierarchy()
{
  // Window
  add(m_fixed);

  // Fixed
  m_fixed.add(m_frame1);  // exportar senhas
  m_fixed.add(m_frame2);  // importar senhas
  m_fixed.add(m_box4);    // texto embaixo
  m_fixed.move(m_frame1, 6, 000); // posição absoluta de frame
  m_fixed.move(m_frame2, 6, 200); // posição absoluta de frame
  m_fixed.move(m_box4, 6, 320);

  //  Fixed
  //    Frame
  //      Box
  //        Alignment
  //          Box
  //            Entry
  //            Entry
  //        Label
  //        Button

  // Frame 1
  m_frame1.add(m_box1);
  m_frame1.set_label("exportar senhas");

  // Box 1
  // ordem de add influencia como as variaveis sao affichados
  m_box1.add(m_align1);
  m_box1.add(m_label1);
  m_box1.add(m_button1);

  // Alignment 1
  m_align1.add(m_box2);

  // Box 2
  m_box2.pack_start(m_entry1, true, true, 0);
  m_box2.pack_start(m_entry2, true, true, 0);

  // Frame 2
  m_frame2.add(m_align2);
  m_frame2.set_label("importar senhas");

  // Alignment 2
  m_align2.add(m_box3);

  // Box 3
  m_box3.pack_start(m_entry3, true, true, 0);
  m_box3.pack_start(m_label3, true, true, 0);
  m_box3.pack_start(m_button2 , true, true, 0);

  // Box 4
  m_box4.pack_start(m_label5, true, true, 0);
  m_box4.pack_start(m_label6, true, true, 0);
  m_box4.pack_start(m_linkbutton, true, true, 0);

  // show_all_children();
}

void mainWindow::draw_widgets(){
  // Window
  set_title("ASCII Art");
  set_default_size(300, 400);
  set_border_width(10);
  set_visible(true);
  set_can_focus(false);

  // Fixed
  m_fixed.set_size_request(300, 400);
  m_fixed.set_visible(true);
  m_fixed.set_can_focus(false);


  // Frame 1
  m_frame1.set_size_request(100, 80);
  m_frame1.set_visible(true);
  m_frame1.set_can_focus(false);
  m_frame1.set_margin_end(8);
  m_frame1.set_shadow_type(Gtk::ShadowType::SHADOW_IN);
  m_frame1.set_label_align(0.02);

  // Box 1
  m_box1.set_visible(true);
  m_box1.set_can_focus(false);

  // Alignment 1
  m_align1.set_size_request(396, 100);
  m_align1.set_visible(true);
  m_align1.set_can_focus(false);
  m_align1.set_border_width(10);

  // Box 2
  m_box2.set_visible(true);
  m_box2.set_can_focus(false);

  // Entry 1
  m_entry1.set_visible(true);
  m_entry1.set_visibility(false);
  m_entry1.set_can_focus(true);
  m_entry1.set_placeholder_text("insira sua senha");
  m_entry1.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
  m_entry1.set_max_length(32);

  // Entry 2
  m_entry2.set_visible(true);
  m_entry2.set_visibility(false);
  m_entry2.set_can_focus(true);
  m_entry2.set_placeholder_text("repita sua senha");
  m_entry2.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
  m_entry2.set_max_length(32);

  // Label 1
  m_label1.set_text("exportar senhas do formator GPG com criptografia");
  m_label1.set_visible(true);
  m_label1.set_can_focus(false);

  // Button 1
  m_button1.set_label("exportar");
  m_button1.set_visible(true);
  m_button1.set_can_focus(true);
  m_button1.set_focus_on_click(true);
  m_button1.set_border_width(10);

  // Frame 2
  m_frame2.set_size_request(100, 80);
  m_frame2.set_visible(true);
  m_frame2.set_can_focus(false);
  m_frame2.set_margin_end(8);
  m_frame2.set_shadow_type(Gtk::ShadowType::SHADOW_IN);
  m_frame2.set_label_align(0.02);

  // Alignment 2
  m_align2.set_size_request(396, 100);
  m_align2.set_visible(true);
  m_align2.set_can_focus(false);
  m_align2.set_border_width(10);

  // Box 3
  m_box3.set_visible(true);
  m_box3.set_can_focus(false);

  // Label 3
  m_label3.set_visible(true);
  m_label3.set_can_focus(false);
  m_label3.set_text("importar arquivo GPG, insira sua senha importar");

  // Entry 3
  m_entry3.set_visible(true);
  m_entry1.set_visibility(false);
  m_entry3.set_can_focus(true);
  m_entry3.set_placeholder_text("informe a senha do arquivo");
  m_entry3.set_input_purpose(Gtk::INPUT_PURPOSE_PASSWORD);
  m_entry3.set_max_length(32);

  // Button 2
  m_button2.set_label("importar");
  m_button2.set_visible(true);
  m_button2.set_can_focus(true);
  m_button2.set_focus_on_click(true);
  // m_button2.set_border_width(10);

  // Box 4
  m_box4.set_size_request(396, 80);
  m_box4.set_visible(true);
  m_box4.set_can_focus(false);

  // Label 5
  m_label5.set_visible(true);
  m_label5.set_can_focus(false);
  m_label5.set_text("arquivo salvo na raiz do diretório");

  // Label 6
  m_label6.set_visible(true);
  m_label6.set_can_focus(false);
  m_label6.set_text("GNU GPL v3");

  // LinkButton
  m_linkbutton.set_visible(true);
  m_linkbutton.set_can_focus(false);
  m_linkbutton.set_label("terminalroot.com.br");
  m_linkbutton.set_uri("https://github.com/tr0fin0");
}

mainWindow::~mainWindow()
{
}

void mainWindow::on_button_quit()
{
  hide();
}