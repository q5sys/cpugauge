/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

/*class BLAH : public QObject{
	Q_OBJECT
private:
  QTimer *timer;
  QObject *root;

private slots:
  void changeValue(){
    root->findChild<QObject*>("CPUGauge")->setProperty("cpuInt", qrand()%101);
  }

public:
  BLAH(QObject *B) : QObject(0){
    root = B;
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeValue()) );
    timer->start();
  }
  ~BLAH(){}  
};*/

int main(int argc, char *argv[])
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    QGuiApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/DejaVuSans.ttf");
    app.setFont(QFont("DejaVu Sans"));

    QQmlApplicationEngine engine(QUrl("qrc:/qml/window.qml"));
    if (engine.rootObjects().isEmpty()){   return -1; }
    //qDebug() << "Number of Objects:" << engine.rootObjects().count();
    //BLAH tmp(engine.rootObjects().first());
    engine.rootObjects().first()->findChild<QObject*>("CPUGauge")->setProperty("cpuInt",90);

    return app.exec();
}

/*   stuff from sysadm to get cpu percentage to make this work in realtime - obviously not done yet
 *
QString result(){
  QProcess proc;
  QString command = "sysctl -n kern.cp_times"
  proc.setProcessChannelMode(QProcess::MergedChannels); //need output
  proc.start(command);
  return QString(proc.readAllStandardOutput());
}

static QStringList last = QStringList();
if(last.isEmpty()){
  //need two ticks before it works properly
  sleep(1);
  last = result;
  result = result();
}

double tot = 0;
double roundtot;
int cpnum = 0;
for(int i=4; i<result.length(); i+=5){
   //The values come in blocks of 5 per CPU: [user,nice,system,interrupt,idle]
   cpnum++; //the number of CPU's accounted for (to average out at the end)
   //qDebug() <<"CPU:" << cpnum;
   long sum = 0;
   //Adjust/all the data to correspond to diffs from the previous check
   for(int j=0; j<5; j++){
     QString tmp = result[i-j];
     result[i-j] = QString::number(result[i-j].toLong()-last[i-j].toLong());
     //need the difference between last run and this one
     sum += result[i-j].toLong();
     last[i-j] = tmp; //make sure to keep the original value around for the next run
   }
   QJsonObject vals;
   roundtot = 100.0L - ( (100.0L*result[i].toLong())/sum );
   tmp.setNum(qRound(roundtot));
   vals.insert("busy", tmp );
   tmp.setNum(cpnum);
   retObject.insert("cpu" + tmp, vals);
   //Calculate the percentage used for this CPU (100% - IDLE%)
   tot += 100.0L - ( (100.0L*result[i].toLong())/sum ); //remember IDLE is the last of the five values per CPU
 }

*/
