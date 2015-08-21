import QtQuick 2.3
import QtQuick.Controls 1.3
import QtMultimedia 5.4

ApplicationWindow {
    visible: true
    width: 660
    height: 580
    title: qsTr("freemapper")

    Rectangle {
        id: captureArea
        width: parent.width
        height: 500
        color: "transparent"

        Component {
            id: defaultComponent

            Rectangle {
                width: 640
                height: 480
                color: "black"
                anchors {
                    top: parent.top
                    left: parent.left
                    margins: 10
                }
            }
        }

        Component {
            id: captureComponent

            Image {
                source: "image://capture"
                cache: false
                height: 480
                width: 640
                anchors {
                    top: parent.top
                    left: parent.left
                    margins: 10
                }
            }
        }

        Loader {
            id: loader
            sourceComponent: defaultComponent
        }
    }

    Button {
        id: calibrate
        anchors {
            top: captureArea.bottom
            right: projectionOnOff.left
            margins: 10
        }
        onClicked: {
            loader.sourceComponent = null
            loader.sourceComponent = captureComponent
        }
        text: "Calibrate"
    }


    Button {
        id: projectionOnOff
        objectName: "projectionOnOff"
        width: 100

        anchors {
            top: captureArea.bottom
            right: parent.right
            margins: 10
        }

        text: "Projection: On"
        onClicked: {
            if ( text == "Projection: On" ) {
                text = "Projection: Off";
            } else {
                text = "Projection: On";
            }
        }
    }


}
