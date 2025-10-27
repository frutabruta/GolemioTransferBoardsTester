#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GolemioClient/golemiov4.h"
#include <QSettings>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_getData_clicked();

    void slotGolemioReady();
    void on_pushButton_setParameters_clicked();

    void on_spinBox_timeout_valueChanged(int arg1);

    void on_pushButton_saveConfig_clicked();

    void on_checkBox_autoUpdate_stateChanged(int arg1);

    void slotRefreshTimout();
    void slotSeconds();
    void slotRequestError(QString errorMessage);
private:
    Ui::MainWindow *ui;

    QTimer timerUpdate;
    QTimer timerSeconds;

    GolemioV4 golemio;

    QSettings qSettings;

    QVector<ConnectionGolemioV4> prestupyGolemio;
    QVector<StopGolemio> zastavkyGolemio;
    QVector<GolemioInfotext> infotextsGolemio;
    QString golemioParametry="";
    QString golemioAddress="";
    QString golemioKey="";

    int updateSeconds=10;


    void connectionToTable(ConnectionGolemioV4 connection, QTableWidget *tableWidget);
    void connectionListToTable(QVector<ConnectionGolemioV4> connectionList, QTableWidget *tableWidget);
    void eraseTable(QTableWidget *tableWidget);
    void messageBox(QString message);
};
#endif // MAINWINDOW_H
