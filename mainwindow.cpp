#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    faceServer=new QTcpServer;
    faceSocket=0;
    this->_height=240;
    this->_width=320;
    this->_buf2=0;
    this->logCount=0;
    this->reloadflag=false;
    this->USER=-1;
    if(!manager.loadSetting())
    {
        this->addLog("UserManager Database is miss!\n");
    }
    else
    {
        this->addLog("UserManager Database Init!\n");
    }
    vname=manager.getUserList();
    int j=0;
    for(j=0;j<vname.size();j++)
    {

         vlist.push_back(new verifier(vname.at(j).c_str()));
    }
    cvInitImageHeader( &opencv_image,cvSize( _width,_height ),IPL_DEPTH_8U, 3, IPL_ORIGIN_TL, 4 );
    isBusy=false;
    if(this->setupServer())
    {
        this->addLog("Server Startup\n");
    }
    else
    {
        this->addLog("Server Failed\n");
    }
    connect(ui->reloadButton,SIGNAL(clicked()),this,SLOT(handleReload()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::addLog(const QString &text)
{
    QString polish(text);
    polish.prepend(QTime::currentTime().toString("h:m:s  "));
    this->ui->statusText->insertPlainText(polish);
    QTextCursor cursor = ui->statusText->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->statusText->setTextCursor(cursor);
    logCount++;
    if(logCount>200)
    {
        ui->statusText->clear();
        logCount=0;
    }
}
bool MainWindow::setupServer()
{
    if(faceServer->listen(QHostAddress::Any,19999))
    {
        connect(this->faceServer,SIGNAL(newConnection()),this,SLOT(handleConnection()));
        return true;
    }
    else
    {
        return false;
    }
}
void MainWindow::handleConnection()
{
    this->addLog("Handle new connection!\n");
    if(!this->isBusy)
    {
        this->isBusy=true;
        faceSocket=this->faceServer->nextPendingConnection();
        this->sendGreeting();
        connect(faceSocket,SIGNAL(readyRead()),this,SLOT(handleImage()));
        //connect(faceSocket,SIGNAL(disconnected()),this,SLOT(handleDisconnect()));
        connect(faceSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(handleDisconnect()));
    }
    else
    {
        this->addLog("Server busy!Unable to handle new coming\n");
    }
}
void MainWindow::sendGreeting()
{
    this->faceSocket->write("face server v1.0",64);

    this->faceSocket->flush();
    this->addLog("Client Connected!\n");
}
void MainWindow::handleDisconnect()
{
    if(faceSocket!=0)
    {
    this->faceSocket->disconnectFromHost();
    this->faceSocket->close();

    faceSocket->deleteLater();
    faceSocket=0;
    this->isBusy=false;
    this->addLog("Client Disconnected!\n");

    }
}
void MainWindow::handleImage()
{
    if(this->faceSocket->bytesAvailable()>=_width*_height*3)
    {
        _buf2 = new char[_width*_height*3];
        this->faceSocket->read((char *)_buf2,_width*_height*3);
        opencv_image.imageData=(char *)_buf2;
        bool authresult=false;
        try
        {
            authresult=this->AuthFace();

            newWebcamImagePaint.paintCyclops(&opencv_image, newDetector.eyesInformation.LE, newDetector.eyesInformation.RE);
            newWebcamImagePaint.paintEllipse(&opencv_image, newDetector.eyesInformation.LE, newDetector.eyesInformation.RE);
        }
        catch(...)
        {
            qDebug()<<"Some Error Happened";
        }
        this->faceSocket->write(opencv_image.imageData,_width*_height*3);
        if(authresult)
        {
            QString result="Success:";
            result.append(vname.at(USER).c_str());
            result+="\n";
            this->faceSocket->write(result.toAscii(),256);

        }
        else
        {
            this->faceSocket->write(this->errorString.toAscii(),256);
        }
        delete _buf2;
        _buf2=0;
        this->faceSocket->flush();
    }
    else
    {
        /*char statusText[200];
        sprintf(statusText,"Waiting for enough data:%d avail\n",this->faceSocket->bytesAvailable());
        this->addLog(statusText);*/
    }
}
bool MainWindow::AuthFace()
{

    newDetector.runDetector(&opencv_image);
    if (sqrt(pow(newDetector.eyesInformation.LE.x-newDetector.eyesInformation.RE.x,2) + (pow(newDetector.eyesInformation.LE.y-newDetector.eyesInformation.RE.y,2)))>28  && sqrt(pow(newDetector.eyesInformation.LE.x-newDetector.eyesInformation.RE.x,2) + (pow(newDetector.eyesInformation.LE.y-newDetector.eyesInformation.RE.y,2)))<120)
    {
        double yvalue=newDetector.eyesInformation.RE.y-newDetector.eyesInformation.LE.y;
        double xvalue=newDetector.eyesInformation.RE.x-newDetector.eyesInformation.LE.x;
        double ang= atan(yvalue/xvalue)*(180/CV_PI);
        if (pow(ang,2)<200)
        {
             IplImage * im = newDetector.clipFace(&opencv_image);
             int j=0;
             this->addLog("Checking Face!\n");
             for(j=0;j<vlist.size();j++)
             {
                  int val=vlist.at(j)->verifyFace(im);
                  if (val==1)
                  {
                       cvReleaseImage(&im);
                       USER=j;
                       this->addLog("Authenciation Successful\n");
                       return true;
                  }
             }
             cvReleaseImage(&im);
             this->addLog("Access Denied\n");
             this->errorString="Access Denied\n";
             return false;
         }
         else
         {
                     this->addLog("Please keep align face!\n");
                     this->errorString="Please keep align face!\n";
                     return false;
         }
  }
   else
   {
        this->addLog("Adjusting distance\n");
        this->errorString="";
        if(this->newDetector.messageIndex==0)
            this->errorString+="Please come closer to the camera";
        else if (this->newDetector.messageIndex==1)
            this->errorString+="Please go a little far";
        else
            this->errorString+="Trying to detect your face";
        this->errorString+="\n";
        return false;
   }
}
void MainWindow::handleReload()
{
    this->ui->reloadButton->setEnabled(false);
    if(!manager.loadSetting())
    {
        this->addLog("UserManager Database is miss!\n");
    }
    else
    {
        this->addLog("UserManager Database Init!\n");
    }
    vname=manager.getUserList();
    for (int i=0;i<vlist.size();i++)
    {
        verifier *temp=vlist.at(i);
        delete temp;
    }
    vlist.clear();
    int j=0;
    for(j=0;j<vname.size();j++)
    {

         vlist.push_back(new verifier(vname.at(j).c_str()));
    }

    this->addLog("Server Reload!\n");
    this->ui->reloadButton->setEnabled(true);
}

