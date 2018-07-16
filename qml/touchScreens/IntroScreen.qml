import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
//import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import com.app 1.0

Item
{
    id:login;

    anchors.fill: parent;
    anchors.centerIn: parent;

    ColumnLayout
    {
        spacing: 10;
        anchors.centerIn: parent;

        Text
        {
            id:mainText;
            Layout.alignment : Qt.AlignHCenter;
            text: "Привет. Приложи браслет, чтобы начать";
            font.family: "Helvetica";
            font.pixelSize: 25;
            color: "#999999";
        }

        ProgressBar
        {
            indeterminate: true;
            anchors.horizontalCenter: parent.horizontalCenter;
            visible:false;
        }

        Text
        {
            id:erroText;
            Layout.alignment : Qt.AlignHCenter;
            visible : false;
            text: "Не знаю кто ты человек";
            font.family: "Helvetica";
            font.pixelSize: 20;
            color: "#990000";
        }

        Button
        {
            id: startBtn;
            implicitHeight: 80;
            implicitWidth: 80;
            Layout.alignment : Qt.AlignHCenter;
            text:"Start";
            visible:false;
            onClicked:
            {
                appController.startInstruction();
            }
        }
    }

    Connections
    {
        target:userData;

        onUserStateChanged:
        {
            switch(userState)
            {
            case UserState.None:
                break;

            case UserState.DoesntExists:
                mainText.text = "Похоже, что тебя не существует!";
                startBtn.visible = false;
                break;

            case UserState.Finished:
                mainText.text = "Забирай свои призы и не приходи сюда!";
                startBtn.visible = false;
                break;

            case UserState.WasRecently:
                mainText.text = "Недавно же играл!";
                startBtn.visible = false;
                break;

            case UserState.YouArePlaying:
                mainText.text = "Играешь на другом стенде хитрец!";
                startBtn.visible = false;
                break;
            }
        }

        onLoginStateChanged:
        {
            switch(loginState)
            {
            case LoginState.Login:
                mainText.text = "О привет, " + userData.name + "! Начнем!";
                startBtn.visible = true;
                break;

            case LoginState.Error:
                mainText.text = "Ошибка сервера";
                startBtn.visible = false;
                break;
            }
        }
    }

    function stop()
    {
        mainText.text =  "Привет. Приложи браслет, чтобы начать";
        erroText.visible = false;
        startBtn.visible = false;
    }

    function setTestState(state)
    {
        reset();
    }
}
