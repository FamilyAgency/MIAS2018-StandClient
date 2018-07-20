#ifndef LOGINMODULE_H
#define LOGINMODULE_H

#include <QObject>
#include "BaseModule.h"
#include "core/data/UserData.h"
#include "components/RFIDComponent.h"
#include "components/ServerComponent.h"
#include "core/data/StandData.h"

class IntroModule : public BaseModule
{
    Q_OBJECT
public:
    explicit IntroModule(QObject *parent = nullptr);
    virtual ~IntroModule();

    virtual void setQmlContext(QQmlContext* qmlContext) override;
    virtual void setConfig(ConfigPtr config) override;
    virtual void start() override;
    virtual void stop() override;
    virtual QString getName() const override;

    virtual void setRFIDComponent(QSharedPointer<RFIDComponent> rfidComponent);
    virtual void setServerComponent(QSharedPointer<ServerComponent> value);
    virtual void setUserData(QSharedPointer<UserData> userData);
    virtual void setStandData(QSharedPointer<StandData> value);

private:
    QSharedPointer<RFIDComponent> rfidComponent = nullptr;
    QSharedPointer<ServerComponent> serverComponent = nullptr;
    QSharedPointer<UserData> userData = nullptr;
    QSharedPointer<StandData> standData = nullptr;

    void connectComponents();
    void disconnectComponents();

signals:
    void userCantStartReason(UserData::CantPlayReason reason);
    void userStartPlay();
    void userNotFound();


private slots:
    void onRFIDRecieve(int id);
    void onRFIDConnectedChanged();
    void onNewUserEntered(const UserObject& userObject);
    void onUserNotFound();
    void onServerError();
};

#endif // LOGINMODULE_H
