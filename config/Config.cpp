#include "Config.h"

Config::Config()
{
    mainConfig.reset(new MainConfig);
    mindwaveConfig.reset(new MindwaveConfig);
    rfidConfig.reset(new RFIDConfig);
    serverConfig.reset(new ServerConfig);
    slackConfig.reset(new SlackConfig);
    loggerConfig.reset(new LoggerConfig);
    monitoringConfig.reset(new MonitoringConfig);
    standGamesConfig.reset(new StandGamesConfig);
}

Config::~Config()
{

}

QString Config::getRawData() const
{
    return rawData;
}

void Config::setRawData(const QString& value)
{
    rawData = value;
}
