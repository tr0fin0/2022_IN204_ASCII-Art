#include "~Util/~util.h"
#include <gtkmm/application.h>
#include "GUI/screen.h"
// #include "GUI/screen_1.h"
// #include "networkConnection/tcp_s.cpp"

int main(){
    // run();
    
    auto app = Gtk::Application::create("org.gtkmm.example");

    mainWindow Window;

    // Shows the window and returns when it is closed.
    return app->run(Window);
    
    // int choice = 0;
    // while(choice != 1 && choice != 2){    
    //     std::cout << "(1)Server | (2) Client: ";
    //     std::cin >> choice;
    // }
    // if(choice == 2){
    //     be_client("147.250.224.185");
    // }
    // else{
    //     system("hostname -I");
    //     be_tcp_server();
    // }
    // return 0;
}
