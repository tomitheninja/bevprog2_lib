#include "application.h"

int main()
{
    Application app;

    while (app.tick())
        ;

    return 0;
}
