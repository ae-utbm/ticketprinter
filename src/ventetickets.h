#ifndef VENTETICKETS_H
#define VENTETICKETS_H

#include <QMainWindow>
#include <QString>
#include <QPrinter>
#include <iostream>
#include <fstream>
#include <string>

#include "ui_mainwindow.h"

using namespace std;


class LogFile
{
public:
  void loadLogFile(string fileName);
  int getCount1();
  int getCount2();
  void log(int t1, int t2);
private:
  fstream logFile;
  streamsize logPos;
  int ticket1Count;
  int ticket2Count;
};

class VenteTickets : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
  VenteTickets( QWidget * parent = 0, Qt::WFlags f = 0);
  void setUniteCarnet(int unite);
private:
  QString EventName;
  QPrinter Printer;
  QImage ticketImg;
  int uniteCarnet;
  LogFile logFile;
  void SigConnect();
  bool SetPrinterInfo(QString name);
  void Print(int nb);
  void Load_image(bool force);
  void SelectPrinter(bool force);
private slots:
  void SetEventName();
  void About();
  void Load_image();
  void SelectPrinter();
  void Print1();
  void Print2();
  void SelectNbTickets();
  void ResetCompteurs();
};

#endif

