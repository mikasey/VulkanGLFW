#include "Application.hpp"

int main(){
    Application app;

    try{
        app.run();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
        app.cleanup();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}