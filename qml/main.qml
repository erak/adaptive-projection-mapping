import QtQuick 2.3
import QtQuick.Controls 1.3
import QtMultimedia 5.4
import freemapper.Projection 1.0
import freemapper.CaptureImage 1.0
import freemapper.CameraCapture 1.0



ApplicationWindow {
    visible: true
    width: 660
    height: 580
    title: qsTr("freemapper")

    CameraCapture {
        id: camera
    }

//    CaptureImage {
//        id: captureImage
//        width: 640
//        height: 480
//    }

    Projection {
        id: projection
        enabled: false
        // scene: capture.scene
    }

    Connections {
        target: captureImage
        onImageChanged: image.setImage(image)
    }

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
                id: image
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
            right: projectionBtn.left
            margins: 10
        }
        onClicked: {
            // capture.capture()

            loader.sourceComponent = null
            loader.sourceComponent = captureComponent
        }
        text: "Calibrate"
    }


    Button {
        id: projectionBtn
        objectName: "projectionOnOff"
        width: 100

        anchors {
            top: captureArea.bottom
            right: parent.right
            margins: 10
        }

        text: projection.enabled ? "Projection: On" : "Projection: Off"
        onClicked: !projection.enabled ? projection.on() : projection.off()
    }


}
