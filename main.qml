import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Window{
    id: window1
    visible: true
    height: 500
    width: 400
    title: "Screeny"
    color: "white"

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        Rectangle {
            color: "red"
            Layout.fillWidth: true


            // content
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.bottomMargin: 5
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            Button {
                text: "Back"
            }
            Item {
                Layout.fillWidth: true
            }


            Rectangle {
                width: 20
                border.color: "#ffe664"
                border.width: 1
                height: width
                radius: width*0.2
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#fda61d"
                    }

                    GradientStop {
                        position: 1
                        color: "#43360a"
                    }






                }
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Qt.AlignCenter
                    verticalAlignment: Qt.AlignVCenter
                    color: "white"
                    text: "1"
                }
            }


            Item {
                Layout.fillWidth: true
            }
            Button {
                text: "Next"
                anchors.right: parent.right
            }
        }


    }



}

