#ifndef SCREEN_H
#define SCREEN_H
#include <QVector>
#include <QString>
#include "screenmode.h"

class MonitorScreen
{
private:
    QVector<ScreenMode> mAvailModes;
    QString mName;
    unsigned int mID;
    QVector<ScreenMode>::iterator mCurrentlyUsedMode;
    bool mConnected;
public:
    MonitorScreen(unsigned int ID, QString name, QVector<ScreenMode> AvailModes);
    SetCurrentlyUsedMode(QVector<ScreenMode>::iterator &&mode) {mCurrentlyUsedMode = mode;}
    SetConnected(bool connected) {mConnected = connected;}
    QVector<ScreenMode> GetScreenModes() {return mAvailModes;}

};

#endif // SCREEN_H
