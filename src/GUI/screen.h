#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <iostream>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include "../converters/VideoConverter.h"


class HelloWorld : public Gtk::Window
{

public:
  HelloWorld();
  virtual ~HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
};

HelloWorld::HelloWorld(): m_button("Make a flower!")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window.
  set_border_width(20);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &HelloWorld::on_button_clicked));
              
  // This packs the button into the Window (a container).
  add(m_button);

  // The final step is to display this newly created widget...
  m_button.show();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  ImageConverter c("../images/flower.jpeg");
  c.convertGrayScale();
  c.resize(50,25);
  c.print_ASCII();
}


#endif