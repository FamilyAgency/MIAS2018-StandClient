#include "UHFCardHandler.h"

UHFCardHandler::UHFCardHandler(QObject *parent) : RFIDComponent(parent)
{
    beepOnCommand.append(char(0xA0));
    beepOnCommand.append(char(0x04));
    beepOnCommand.append(char(0x01));
    beepOnCommand.append(char(0x7A));
    beepOnCommand.append(char(0x01));
    beepOnCommand.append(char(0xE0));

    //////////////////////////////////////

    beepOffCommand.append(char(0xA0));
    beepOffCommand.append(char(0x04));
    beepOffCommand.append(char(0x01));
    beepOffCommand.append(char(0x7A));
    beepOffCommand.append(char(0x00));
    beepOffCommand.append(char(0xE1));

    //////////////////////////////////////

    readCommand.append(char(0xA0));//head
    readCommand.append(char(0x04));//len
    readCommand.append(char(0xFF));//adress
    readCommand.append(char(0x89));
    readCommand.append(char(0x01));
    readCommand.append(char(0xD3));

    //////////////////////////////////////

    inventoryCommand.push_back(char(0xA0));//head
    inventoryCommand.push_back(char(0x03));//len
    inventoryCommand.push_back(char(0x01));//adress

    inventoryCommand.push_back(char(0x90));//command
    inventoryCommand.push_back(char(0xCC));//checksum

    //////////////////////////////////////

    clearCommand.push_back(char(0xA0));
    clearCommand.push_back(char(0x03));
    clearCommand.push_back(char(0x01));

    clearCommand.push_back(char(0x93));
    clearCommand.push_back(char(0xC9));

    //////////////////////////////////////

    resetCommand.push_back(char(0xA0));
    resetCommand.push_back(char(0x03));
    resetCommand.push_back(char(0x01));

    resetCommand.push_back(char(0x70));
    resetCommand.push_back(char(0xEC));

    //////////////////////////////////////

    //    unsigned char cmd[4] = { 0xA0, 0x03, 0x01, 0x70 };
    //    auto  newLis = cmd;
    //    unsigned char check = ' ';
    //    check = CheckSum(newLis, 4);
}

void UHFCardHandler::startReading()
{
//    auto portName = getPortNameByModelIndex(modelIndex);
//    serialPort->setPortName(portName);

//    qDebug()<<"startReading "<<modelIndex<<portName;

//    auto serialPortBaudRate = QSerialPort::BaudRate(rfidConfig.baudRate);
//    serialPort->setBaudRate(serialPortBaudRate);

//    if (!serialPort->open(QIODevice::ReadWrite))
//    {
//        qDebug()<<"serialPort opening error";
//    }
//    else
//    {
//        qDebug()<<"serialPort opened";
//        connect(serialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
//        connect(serialPort, SIGNAL(errorOccurred(QSerialPort::SerialPortError)), this, SLOT(onReadError(QSerialPort::SerialPortError)));

//        serialPort->write(beepOffCommand);

//        timer = new QTimer(this);
//        connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
//        timer->start(taskTimerMills);
//    }
}

void UHFCardHandler::onReadyRead()
{
//    if(!serialPort->isOpen())
//    {
//        return;
//    }

//    QByteArray bytesReaded = serialPort->readAll();

//    if(bytesReaded.isEmpty())
//    {
//        return;
//    }
}

void UHFCardHandler::onUpdate()
{
   // serialPort->write(readCommand);
}

//QVariantList BaseRFIDDataReader::getPortsAvailable() const
//{
//    QVariantList info;
//    QSerialPortInfo serialPortInfo;

//    qDebug()<<"port names ======================";
//    auto ports = serialPortInfo.availablePorts();
//    for(auto port: ports)
//    {
//        info.append(port.portName() + " " /*+ port.description() + " "*/ +  port.manufacturer());
//         qDebug()<<"port name: " +  port.portName();
//         qDebug()<<"port description: " +  port.description();
//         qDebug()<<"port manufacturer: " +  port.manufacturer();
//         qDebug()<<"port systemLocation: " +  port.systemLocation();
//         qDebug()<<"port serialNumber: " +  port.serialNumber();
//         qDebug()<<"port vendorIdentifier: " +  port.vendorIdentifier();
//         qDebug()<<"port productIdentifier: " +  port.productIdentifier();
//    }
//    qDebug()<<"======================";

//    USBTools tools;
//    tools.printAvailableDevices();

//    return info;
//}

//QString BaseRFIDDataReader::getPortNameByModelIndex(int modelIndex) const
//{
//    QSerialPortInfo serialPortInfo;
//    auto ports = serialPortInfo.availablePorts();

//    if(ports.length() > modelIndex)
//    {
//        return ports[modelIndex].portName();
//    }

//    return "";
//}

