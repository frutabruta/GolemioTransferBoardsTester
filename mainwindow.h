#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "golemio/golemio.h"
#include <QSettings>

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
private:
    Ui::MainWindow *ui;

    Golemio golemio;

    QSettings qSettings;

    QVector<ConnectionGolemio> prestupyGolemio;
    QVector<StopGolemio> zastavkyGolemio;
    QVector<GolemioInfotext> infotextsGolemio;
    QString golemioParametry="";
    QString golemioAddress="";
    QString golemioKey="";


};
#endif // MAINWINDOW_H
