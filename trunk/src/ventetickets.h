#ifndef VENTETICKETS_H
#define VENTETICKETS_H

#include <QMainWindow>
#include <QString>
#include <QPrinter>

#include "ui_mainwindow.h"

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
};
#endif




