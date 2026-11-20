#ifndef VENTETICKETS_H
#define VENTETICKETS_H

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
  void loadLogFile(const string& fileName);
  int getCount1() const;
  int getCount2() const;
  void log(int t1, int t2);
private:
  fstream logFile;
  streamsize logPos = 0;
  int ticket1Count = 0;
  int ticket2Count = 0;
};

class VenteTickets : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
  VenteTickets(QWidget * parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  void setUniteCarnet(int unite);
private:
  QString EventName;
  QPrinter Printer;
  QImage ticketImg;
  int uniteCarnet{};
  LogFile logFile;
  void SigConnect() const;
  bool SetPrinterInfo(const QString& name);
  void Print(int nb);
  void Load_image();
  void SelectPrinter(bool force);
private slots:
  void SetEventName();

  static void About();
  void SelectPrinter();
  void Print1();
  void Print2();
  void SelectNbTickets();
  void ResetCompteurs();
};

#endif

