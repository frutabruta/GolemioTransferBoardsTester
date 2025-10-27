#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

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

    ui->lineEdit_parameters->setText(golemioParametry);

    updateSeconds=qSettings.value("app/timeout").toInt();

    ui->spinBox_timeout->setValue(updateSeconds);

    timerUpdate.setInterval(updateSeconds*1000);
    timerSeconds.setInterval(1000);
    timerSeconds.start();


    connect(&golemio,&Golemio::stazeniHotovo,this,&MainWindow::slotGolemioReady);
    connect(&golemio,&Golemio::signalError,this,&MainWindow::slotRequestError);


    connect(&timerUpdate,&QTimer::timeout,this,&MainWindow::slotRefreshTimout);
    connect(&timerSeconds,&QTimer::timeout,this,&MainWindow::slotSeconds);
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

    connectionListToTable(prestupyGolemio,ui->tableWidget_departures);

}


void MainWindow::eraseTable(QTableWidget *tableWidget)
{
    //used to erase tablewidgets without program crash due to signals
    //  https://stackoverflow.com/a/31564541
    qDebug() <<  Q_FUNC_INFO;

    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);

}


void MainWindow::connectionListToTable(QVector<ConnectionGolemioV4> connectionList,QTableWidget* tableWidget)
{

    eraseTable(tableWidget);


    foreach(ConnectionGolemioV4 connection, connectionList)
    {
        connectionToTable(connection,tableWidget);
    }
}



void MainWindow::connectionToTable(ConnectionGolemioV4 connection, QTableWidget* tableWidget)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;



    row = tableWidget->rowCount();
    tableWidget->insertRow(row);

    QString lineName=connection.routeShortName;
    cell = new QTableWidgetItem(lineName);

    tableWidget->setItem(row, 0, cell);

    QString destinationName=connection.tripHeadsign;
    cell = new QTableWidgetItem(destinationName);
    tableWidget->setItem(row, 1, cell);

    cell = new QTableWidgetItem(connection.departureTimestampMinutes.join(",") );
    tableWidget->setItem(row, 2, cell);

    cell = new QTableWidgetItem(connection.stopPlatformCode );
    tableWidget->setItem(row, 3, cell);

    cell = new QTableWidgetItem(connection.substitutionTextCs );
    tableWidget->setItem(row, 4, cell);

    cell = new QTableWidgetItem(connection.substitutionTextEn );
    tableWidget->setItem(row, 5, cell);

    cell = new QTableWidgetItem(connection.icons.join(" ") );
    tableWidget->setItem(row, 6, cell);

    tableWidget->resizeColumnsToContents();
}



void MainWindow::on_pushButton_setParameters_clicked()
{
    golemioParametry=ui->lineEdit_parameters->text();
    golemio.setParametry(golemioParametry);
}


void MainWindow::on_spinBox_timeout_valueChanged(int arg1)
{
    updateSeconds=arg1;
    timerUpdate.setInterval(updateSeconds*1000);
}


void MainWindow::on_pushButton_saveConfig_clicked()
{
    qSettings.setValue("golemio/parameters",golemioParametry);
    qSettings.setValue("app/timeout",updateSeconds);
}


void MainWindow::on_checkBox_autoUpdate_stateChanged(int arg1)
{
    if(arg1)
    {
        if(updateSeconds>0)
        {
            golemio.startDataDownload(golemioParametry);
            timerUpdate.start();
        }
        else
        {
            messageBox("neplatná hodnota intervalu");
            timerUpdate.stop();
        }

    }
    else
    {
        timerUpdate.stop();
    }
}

void MainWindow::messageBox(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

void MainWindow::slotRefreshTimout()
{
    golemio.startDataDownload(golemioParametry);
}

void MainWindow::slotSeconds()
{
    ui->label_CountDown->setText(QString::number(timerUpdate.remainingTime()/1000));
}

void MainWindow::slotRequestError(QString errorMessage)
{
    messageBox(errorMessage);
}
