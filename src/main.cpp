#include "~Util/~util.h"
#include <gtkmm/application.h>
#include "GUI/MainWindow.h"
// #include "GUI/screen_1.h"
// #include "networkConnection/tcp_s.cpp"
// #include "networkConnection/server.h"

int main(){
    // run();
    
    auto app = Gtk::Application::create("org.gtkmm.example");
    MainWindow Window;

    return app->run(Window);

    // Shows the window and returns when it is closed.
    // return app->run(Window);
    
    int choice = 0;
    while(choice != 1 && choice != 2 && choice != 3){    
        std::cout << "(1)Server | (2) Client: ";
        std::cin >> choice;
    }
    if(choice == 2){
        be_client("147.250.227.185");
    }
    if(choice == 3){
        VideoConverter v;
        v.CaptureWebcam();
    }
    else{
        system("hostname -I");
        be_server();
}
    return 0;
}
