#include "SuperGameModule.h"
#include <QDebug>
#include <QDateTime>

SuperGameModule::SuperGameModule(QObject *parent) : BaseModule(parent)
{
    superGameTimer = new QTimer(this);
    connect(superGameTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
}

SuperGameModule::~SuperGameModule()
{
    if(superGameTimer)
    {
        disconnect(superGameTimer, SIGNAL(timeout()), this, SLOT(onUpdate()));
        delete superGameTimer;
    }
}

void SuperGameModule::setQmlContext(QQmlContext* qmlContext)
{
    BaseModule::setQmlContext(qmlContext);
    qmlContext->setContextProperty("superGameModule", this);
}

void SuperGameModule::setUser(QSharedPointer<UserData> value)
{
    currentUser = value;
}

void SuperGameModule::setConfig(ConfigPtr config)
{
    BaseModule::setConfig(config);
}

void SuperGameModule::start()
{
    qDebug()<<"======================= SuperGameModule START =======================";
    superGameTime = currentUser->getSuperGameData().time;
    emit updateSuperGameTime(superGameTime);   
}

void SuperGameModule::stop()
{
    qDebug()<<"======================= SuperGameModule STOP =======================";
    superGameTimer->stop();
}

void SuperGameModule::startGame()
{
    startTime = QDateTime::currentMSecsSinceEpoch();
    superGameTimer->start(superGameTimerMills);
}

void SuperGameModule::onUpdate()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    int leftTime = superGameTime - time;
    if(leftTime >= 0.0)
    {
        emit updateSuperGameTime(leftTime);
    }
    else
    {
         superGameTimer->stop();
         emit updateSuperGameTime(0.0f);
         emit superGameFailed();
    }
}

void SuperGameModule::superGamePassedTest()
{
    int time = QDateTime::currentMSecsSinceEpoch() - startTime;
    currentUser->superGameCompleted(time);

    emit superGameSuccess(time);
}

QString SuperGameModule::getName() const
{
    return "Super Game location";
}

