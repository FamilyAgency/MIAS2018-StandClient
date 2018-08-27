import QtQuick.Layouts 1.3
import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.8

import "../../tools"
import "../elements"

Item
{
    id: advatage;
    anchors.fill: parent;

    property string mainTitleDefault: "НАЗВАНИЕ<br/>ПРЕИМУЩЕСТВА";
    property int circleSize: 150;
    property real nameMarginTop: 60;
    property string buttonText: "ПОЕХАЛИ<br/>ДАЛЬШЕ";
    property real btnMarginBottom: 100;

    signal advantageReaded;

    FontManager
    {
        id: font;
    }

    Video
    {
        id: video;
        width : 1080;
        height : 1150;
        loops: MediaPlayer.Infinite;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        focus: true;
    }

    Text
    {
        id: promtText;
        anchors.left: parent.left;
        anchors.leftMargin: 60;
        anchors.topMargin: nameMarginTop;
        anchors.top: parent.top;
        text: mainTitleDefault;
        font.family: font.hyundaiSansHeadMedium;
        font.pixelSize:  70;
        color: "#ffffff";
        textFormat: Text.StyledText;
        horizontalAlignment: Text.AlignLeft;
        verticalAlignment: Text.AlignVCenter;

        Text
        {
            id: promtText2;
            anchors.left: parent.left;
            anchors.topMargin: nameMarginTop;
            anchors.top: promtText.bottom;
            text: mainTitleDefault;
            font.family: font.hyundaiSansHeadRegular;
            font.pixelSize:  40;
            color: "#ffffff";
            textFormat: Text.StyledText;
            horizontalAlignment: Text.AlignLeft;
            verticalAlignment: Text.AlignVCenter;

            lineHeight: 1.1;
        }

        OpacityAnimator on opacity
        {
            id: promtTextAnim;
            from: 0;
            to: 1;
            duration: 700
            running:false;
        }
    }

    BigRedButton
    {
        id: brb;

        anchors.bottomMargin: btnMarginBottom;
        visible:false;
        anchors.fill: parent;
        btnWidth: 410;
        btnHeight: 410;
        btnRadius: 205;

        onClicked:
        {
            advatage.advantageReaded();
        }
    }

    Timer
    {
        id: brbdelay;
        running: false;
        interval: 8000;
        onTriggered:
        {
            brbdelay.stop();
            brb.visible = true;
            brb.show();
        }
    }

    Component.onCompleted:
    {
        brb.setTitle(buttonText);
    }

    function setTexts(title, description)
    {
        advatage.mainTitleDefault = title;
        promtText2.text = description;
        //fullAdvantageDescr.setTexts(title, description);
    }

    function setVideo(videoPath)
    {
        video.source = configController.getVideoFileInAppDir(videoPath);
        console.log(videoPath, configController.getVideoFileInAppDir(videoPath));
        // console.log("video path ", configController.getVideoFileInAppDir(videoPath));
        video.play();
    }

    function show()
    {
        visible = true;
        brb.visible = false;
        brbdelay.start();
        promtText.opacity = 0;
        promtTextAnim.from = 0;
        promtTextAnim.to = 1;
        promtTextAnim.start();
    }

    function hide()
    {
        brbdelay.stop();
        brb.hide();
        video.stop();

        promtTextAnim.from = 1;
        promtTextAnim.to = 0;
        promtTextAnim.start();
    }
}
