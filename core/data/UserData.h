#ifndef USERDATA_H
#define USERDATA_H

#include <QObject>
#include <qDebug>
#include <QQmlContext>
#include "core/data/OneStageData.h"
#include "core/data/SuperGameData.h"
#include "config/Config.h"

struct BaseUserData
{
private:
    Q_GADGET
    Q_PROPERTY(int id MEMBER id)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString surname MEMBER surname)
    Q_PROPERTY(QString email MEMBER email)
    Q_PROPERTY(QString phone MEMBER phone)
    Q_PROPERTY(QString gender MEMBER gender)
    Q_PROPERTY(int test MEMBER test)

public:
    int id = 0;
    QString name = "";
    QString surname = "";
    QString email = "";
    QString phone = "";
    QString gender = "M";
    int test = 0;
    int confirmed = 0;
    int remainSeconds = 0;

    Q_INVOKABLE bool isPinConfirmed() const;
    Q_INVOKABLE int getPinToConfirm() const;

    void print();
    void clear();
};
Q_DECLARE_METATYPE(BaseUserData)

struct PrizesUserData
{
private:
    Q_GADGET
    Q_PROPERTY(bool prize1 MEMBER prize1)
    Q_PROPERTY(bool prize2 MEMBER prize2)

public:
    bool prize1 = false;
    bool prize2 = false;
};
Q_DECLARE_METATYPE(PrizesUserData)

struct GameUserData
{
private:
    Q_GADGET
    Q_PROPERTY(QString description MEMBER description)
    Q_PROPERTY(QVariantList stageTimes MEMBER stageTimes)
    Q_PROPERTY(float superGameTime MEMBER superGameTime)

public:
    QVector<OneStageData> stages;
    OneStageData currentStage;
    int currentStageId;
    bool _hasGames = false;

    SuperGameData superGame;

    int cleanGameTime;

    QString description;
    QString descriptionWin;
    QString iconName;
    QString imageWinName;

    QVariantList stageTimes;

    QString startGame;
    QString stage1;
    QString stage2;
    QString stage3;
    QString finishGame;
    int status;

    float superGameTime = 0.0;

    QVariantList fullGamePath;
    QVariantList targetPoints;

    QVector<QPointF> startPath;
    QVector<QPointF> finalPath;

    GameUserData();

    void setupConfigGameData(const StandOneGameConfig& game);
    void setupConfigSuperGameData(const SuperGameConfig& superGame);

    void setCurrentStageId(int id);

    OneStageData getCurrentStage() const;
    int getCurrentStageId() const;

    bool isFinalStage() const;

    void currentStageCompleted(int time);

    void superGameCompleted(int time);

    bool hasStages() const;

    QVariantList getFullGamePath() const;
    QVariantList getTargetPoints() const;

};
Q_DECLARE_METATYPE(GameUserData)

struct UserObject
{
    BaseUserData baseUserData;
    PrizesUserData prizesUserData;
    GameUserData gameUserData;
};

class UserData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(BaseUserData baseUserData READ baseUserData WRITE setBaseUserData NOTIFY baseUserDataChanged)
    Q_PROPERTY(PrizesUserData prizesUserData READ prizesUserData WRITE setPrizesUserData NOTIFY prizesUserDataChanged)
    Q_PROPERTY(GameUserData gameUserData READ gameUserData WRITE setGameUserData NOTIFY gameUserDataChanged)

public:
    explicit UserData(QObject *parent = nullptr);
    virtual ~UserData();

    enum class CantPlayReason
    {
        None,
        WasRecently,
        YouArePlaying,
        FinishedPrizesGot,
        FinishedPrizesNotGot
    };
    Q_ENUM(CantPlayReason)

    Q_INVOKABLE CantPlayReason getReasonCantPlay() const;
    Q_INVOKABLE int getCurrentStageId() const;
    Q_INVOKABLE void clearBaseUserData();
    Q_INVOKABLE int getSecondsToStart() const;
    bool isFinalStage() const;

    QVariantList getFullGamePath() const;
    QVariantList getTargetPoints() const;


    void setBaseUserData(const BaseUserData& value);
    BaseUserData baseUserData() const;

    void setPrizesUserData(const PrizesUserData& value);
    PrizesUserData prizesUserData() const;

    void setGameUserData(const GameUserData& value);
    GameUserData gameUserData() const;

    OneStageData getCurrentStage() const;
    void currentStageCompleted(int time);

    void superGameCompleted(int time);

    bool hasStages() const;

    void setQmlContext(QQmlContext* value);
    void setConfig(ConfigPtr value);

    void setGameConfig(StandGamesConfig config);
    void clearData();

    void setNewUserData(const UserObject& userObject);
    void setUserDoesntExist();

    void setGameCategory(int id);

    bool canPlay() const;
    bool allPrizesGot() const;
    bool wasRecently() const;
    bool playingOnAnotherStand() const;
    bool finished() const;

    SuperGameData getSuperGameData() const;

    QVector<QPointF> getStartPath() const;
    QVector<QPointF> getFinalPath() const;


private:
    BaseUserData _baseUserData;
    PrizesUserData _prizesUserData;
    GameUserData _gameUserData;

    StandGamesConfig _gameConfig;
    QQmlContext* qmlContext;

    bool _canPlay = false;
    CantPlayReason cantPlayReason;

    void checkCanUserPlay();

signals:
    void baseUserDataChanged();
    void prizesUserDataChanged();
    void gameUserDataChanged();
};

typedef UserData::CantPlayReason CantPlayReason;

#endif // USERDATA_H
