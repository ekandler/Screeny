#ifndef SCREENMODE
#define SCREENMODE
#include <QString>

struct ScreenMode {
    unsigned int id;
    unsigned int height;
    unsigned int width;
    double refreshRate;
};

#endif // SCREENMODE

