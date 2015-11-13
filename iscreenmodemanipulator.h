#ifndef ISCREENMODEMANIPULATOR_H
#define ISCREENMODEMANIPULATOR_H
#include "screenmode.h"
#include <QVector>

class IScreenModeManipulator
{
public:
    virtual ~IScreenModeManipulator() {}
    virtual bool SetScreenMode(unsigned int screen, ScreenMode mode) = 0;

};

#endif // ISCREENMODEMANIPULATOR_H
