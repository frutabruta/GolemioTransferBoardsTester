#ifndef GOLEMIO_H
#define GOLEMIO_H
//#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>


//#include <QCoreApplication>


//#include <VDV301publisher/VDV301DataStructures/connectionmpv.h>
//#include <VDV301publisher/VDV301DataStructures/line.h>
#include "stopgolemio.h"
#include "connectiongolemio.h"
class GolemioInfotext
{


public:
    enum DisplayType
    {
        DisplayTypeInline,
        DisplayTypeGeneral,
        DisplayTypeGeneralAlternate
    };

    DisplayType display_type=DisplayTypeGeneral;
    QString text="";
    QString text_en="";
    QVector<QString> related_stops;
    QDateTime valid_from;
    QDateTime valid_to;

    static QString displayTypeToQString(GolemioInfotext::DisplayType input);
    static GolemioInfotext::DisplayType displayTypeFromQString(QString input);

};


class Golemio: public QObject
{
    Q_OBJECT
public:
    //konstruktor a destruktor
    Golemio(QByteArray klic);
    ~Golemio();


    QByteArray stazenaData="";
    //  QByteArray vystupData="";
    // QVector<PrestupMPV> seznamPrestupuMpv;
    QVector<ConnectionGolemio> seznamPrestupuGolemio;
    QVector<StopGolemio> stopGolemioList;
    QVector<GolemioInfotext> golemioInfotextList;


    void naplnVstupDokument(QByteArray vstup);
    ;
    void startDataDownload(int cisloCis);
    //QVector<ConnectionMPV> vyfiltrujPrestupy(QVector<ConnectionMPV> vstupniPrestupy, Line linka); //unused
    //  bool jePrestupNaSeznamu(ConnectionMPV prestup, QVector<ConnectionMPV> seznamPrestupu);

    QVector<GolemioInfotext> parseDomDocumentInfotexts();
    QVector<ConnectionGolemio> parseDomDocumentDepartures();
    QVector<StopGolemio> parseDomDocumentStops();

    // QVector<ConnectionGolemio> parsujDomDokument();
    void setKlic(const QByteArray &newKlic);

    void setParametry(const QString &newParametry);

    void setAdresa(const QString &newAdresa);

    void startDataDownload(QString golemioAttributes);


private:
    //instance
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    //promenne
    QByteArray mKlic="";
    QString mAdresa="http://api.golemio.cz/v2/pid/departureboards/";
    QString mParametry="";
    QJsonDocument mVstupniJson;


private slots:
    QByteArray requestReceived(QNetworkReply *replyoo);
signals:
    void stazeniHotovo ();
};

#endif // GOLEMIO_H
