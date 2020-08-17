#ifndef MAINSERVERWINDOW_H
#define MAINSERVERWINDOW_H

#include <QWidget>
#include <QDebug>
#include "serverside.h" /* <-- Import our ServerSide Class */


QT_BEGIN_NAMESPACE
namespace Ui { class MainServerWindow; }
QT_END_NAMESPACE

class MainServerWindow : public QWidget
{
    Q_OBJECT

public:
    MainServerWindow(QWidget *parent = nullptr);
    ~MainServerWindow();

private slots:
    void on_pushButton_stopServer_clicked();   /* <-- SLOT for when StopServer button is clicked*/
    void on_pushButton_startServer_clicked();   /* <-- SLOT for when StartServer button is clicked*/
    void on_pushButton_testConnection_clicked();    /* <-- SLOT for when TestConnection button is clicked*/
    void smbConnectedToServer();    /* <-- SLOT for when somebody connects to the server*/
    void smbDisconnectedFromServer();   /* <-- SLOT for when somebody discconects from the server*/
    void gotNewMessage(QString msg);    /* <-- SLOT for when we get a new message*/


private:
    Ui::MainServerWindow *ui;
    ServerSide *server; /* <-- Create a object of ServerSide type */
};
#endif // MAINSERVERWINDOW_H
