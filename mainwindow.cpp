#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,golemio("")
    ,qSettings(QCoreApplication::applicationDirPath()+"/settings.ini", QSettings::IniFormat)
{
    ui->setupUi(this);

    golemioAddress=qSettings.value("golemio/address").toString();
    golemio.setAdresa(golemioAddress);

    golemioKey=qSettings.value("golemio/key").toString().toUtf8();
    golemio.setKlic(golemioKey.toUtf8());

    golemioParametry=qSettings.value("golemio/parameters").toString();
    golemio.setParametry(golemioParametry);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_getData_clicked()
{
    golemio.startDataDownload(golemioParametry);
}


void MainWindow::slotGolemioReady()
{
    qDebug() <<  Q_FUNC_INFO;
    //qDebug()<<"povypisu "<<xmlMpvParser.stazenaData.length();

    golemio.naplnVstupDokument(golemio.stazenaData);
    prestupyGolemio=golemio.parseDomDocumentDepartures();
    zastavkyGolemio=golemio.parseDomDocumentStops();
    infotextsGolemio=golemio.parseDomDocumentInfotexts();

    qDebug()<<"bum10";


    qDebug()<<"bum11";
    /* if(filterConnections)
    {
        //   prestupy=xmlMpvParser.vyfiltrujPrestupy(prestupy,stavSystemu.aktlinka);
    }*/
    qDebug()<<"pocet Prestupu ve vektoru: "<<prestupyGolemio.count();


    //createScene(prestupyGolemio);


}

