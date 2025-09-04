#ifndef CONNECTIONGOLEMIO_H
#define CONNECTIONGOLEMIO_H
#include <QDateTime>
#include <QDebug>

//#include "connection.h"

//this class stores connections obtained from public Golemio API: https://api.golemio.cz/v2/pid/docs/openapi/


class ConnectionGolemio
{
public:
    ConnectionGolemio();

    QDateTime arrivalTimestampPredicted;
    QDateTime arrivalTimestampScheduled;
    QString arrivalTimestampMinutes="";

    bool delayIsAvailable=false;
    int delayMinutes=0;
    int delaySeconds=0;

    QDateTime departureTimestampPredicted;
    QDateTime departureTimestampScheduled;
    QString departureTimestampMinutes="";

    QString lastStopName="";
    QString lastStopId="";


    QString routeShortName="";
    int routeType=0;
    bool routeIsNight=false;
    bool routeIsRegional=false;
    bool routeIsSubstituteTransport=false;

    QString stopId="";
    QString stopPlatformCode="";


    QString tripDirection="";
    QString tripHeadsign="";
    QString tripId="";
    QString tripShortName="";
    bool tripIsCanceled=false;
    bool tripIsAirConditioned=false;
    bool tripIsWheelchairAccessible=false;
    
    bool tripIsAtStop=false;


    QString minutesToArrival();
    //  Connection toConnection();
    static QDateTime qStringDoQDateTime(QString vstup);
    static QString qDateTimeToString(QDateTime vstup);

};

#endif // CONNECTIONGOLEMIO_H
