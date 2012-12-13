#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include <opencv2/opencv.hpp>
#include "verifier.h"
#include "detector.h"
#include "webcamImagePaint.h"
#include "usermanager.h"
#include <QTime>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    bool setupServer();
    void addLog(const QString &text);
    QTcpServer *faceServer;
    bool isBusy;
    QTcpSocket *faceSocket;
    int _width;
    int _height;
    char *_buf2;
    IplImage opencv_image;
    vector<verifier *> vlist;
    vector<string> vname;
    detector newDetector;
    UserManager manager;
    bool AuthFace();
    QString errorString;
    webcamImagePaint newWebcamImagePaint;
    void sendGreeting();
    int USER;
    int logCount;
    void reload();
    bool reloadflag;
public slots:
    void handleConnection();
    void handleReload();
    void handleImage();
    void handleDisconnect();
};

#endif // MAINWINDOW_H
