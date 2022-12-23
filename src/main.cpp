#include "~Util/~util.h"
#include <gtkmm/application.h>
#include "GUI/screen.h"

int main(){
    run();

    auto app = Gtk::Application::create("org.gtkmm.example");

    HelloWorld helloworld;

    //Shows the window and returns when it is closed.
    return app->run(helloworld);

    return 0;
}
