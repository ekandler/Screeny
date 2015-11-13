#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "screenmodemanipulatorfactory.h"
#include "screenmode.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);


    ScreenModeManipulatorFactory modeFactory;
    IScreenModeManipulator * modeManip = modeFactory.CreateModeManipulator();
    ScreenMode desiredMode{1920,1080,25};
    modeManip->SetScreenMode(1, desiredMode);


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

