#include "application.h"

#include <iostream>

int main()
try {
    Application app;

    if (!app.initialize()) {
        std::cerr << "Failed to initialize the application." << "\n";
        return -1;
    }

    app.run();

    return 0;
}
catch (const std::exception& e) {
    std::cerr << "An error occurred: " << e.what() << "\n";
    return -1;
}