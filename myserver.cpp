#include "myserver.h"

MyServer::MyServer(QObject *parent) :
  QTcpServer(parent)
{
  ok = 1;
}

void MyServer::StartServer(){
  if(!this->listen(QHostAddress::Any, 1234)){
    qDebug() << "server not started";
  }
  else{
    qDebug() << "server started";
  }
}

void MyServer::incomingConnection(qintptr socketDescriptor){

  qDebug() << socketDescriptor << " connecting...";
  MyThread *thread = new MyThread(socketDescriptor,this, &storage);
  connect(thread,SIGNAL(finished()), thread, SLOT(deleteLater()));
  thread->run();
}
