#include "ventetickets.h"
#include <QPrinterInfo>
#include <QPrinter>
#include <QMessageBox>
#include <QPainter>
#include <QPoint>
#include <QInputDialog>
#include <QFileDialog>
#include <locale>
#include <sstream>

/**
 * Constructor
 * set some defaults setings
 */
VenteTickets::VenteTickets( QWidget * parent, Qt::WFlags f)
	: QMainWindow(parent, f)
{
  setWindowTitle("Vente de tickets");
  setupUi(this);
  EventName="";
  string logFileName;

  /* printer */
  //if we can't find the default printer, we choose one
  if(!SetPrinterInfo("TSP100"))
    SelectPrinter(true);

  //default background image
  ticketImg=QImage("ticketAE.png");

  // if we can't load the default ticket background, we choose one
  if (ticketImg.isNull())
    Load_image(true);
  else
    ticketImg=ticketImg.scaledToWidth(Printer.pageRect().width()/2,
                                      Qt::SmoothTransformation);

  logFileName = getenv("HOME");
  logFileName += "/aeticketptr_log.txt";
  this->logFile.loadLogFile(logFileName);
  lcd1tik->display(this->logFile.getCount1());
  lcd2tik->display(this->logFile.getCount2());

  // set default number of tickets
  this->setUniteCarnet(10);

  /* Connect signals */
  SigConnect();
}

/**
 * Signal connections
 */
void VenteTickets::SigConnect()
{
  connect(actionTickets,SIGNAL(activated()),this,SLOT(Load_image()));
  connect(actionEventName,SIGNAL(activated()),this,SLOT(SetEventName()));
  connect(actionA_propos,SIGNAL(activated()),this,SLOT(About()));
  connect(actionImprimante,SIGNAL(activated()),this,SLOT(SelectPrinter()));
  connect(actionReset,SIGNAL(activated()),this,SLOT(ResetCompteurs()));
  connect(actionNbTickets,SIGNAL(activated()),this,SLOT(SelectNbTickets()));
  connect(vente1, SIGNAL( released() ), this, SLOT(Print1()));
  connect(vente2, SIGNAL( released() ), this, SLOT(Print2()));
}

/**
 * Load event name
 */
void VenteTickets::SetEventName()
{
  EventName = QInputDialog::getText(this,
                                    QString::fromUtf8("Nom de l'évennement"),
                                    QString::fromUtf8("Nom :"),
                                    QLineEdit::Normal,
                                    EventName);
}

/**
 * Load ticket's image
 * @param force force image selection
 */
void VenteTickets::Load_image(bool force)
{
  QString fileName;
  while(fileName.isEmpty() && force)
  {
    fileName = QFileDialog::getOpenFileName(0,
                                            "Open File",
                                            QDir::currentPath(),
                                            "All images (*.png *.jpg)");
    if (!fileName.isEmpty())
    {
      QImage image(fileName);
      if (image.isNull())
      {
        QMessageBox::information(0,
                                 "Erreur",
                                 "Impossible de charger le fichier");
      }
      else
      {
        ticketImg=image.scaledToWidth(Printer.pageRect().width()/2,
                                      Qt::SmoothTransformation);
      }
    }
  }
  return;
}

void VenteTickets::Load_image()
{
  Load_image(true);
}

/**
 * SelectPrinter
 * @param force force printer selection
 */
void VenteTickets::SelectPrinter(bool force)
{
  QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
  QStringList sprinters;
  for (int c = 0; c < printers.size(); ++c)
    sprinters << printers[c].printerName();
  printers.clear();
  bool set = SetPrinterInfo(QInputDialog::getItem(this,
                            QString::fromUtf8("Imprimante"),
                            QString::fromUtf8("Imprimante :"),
                            sprinters,
                            0,
                            false));
  while(!set && force)
  {
    set = SetPrinterInfo(QInputDialog::getItem(this,
                         QString::fromUtf8("Imprimante"),
                         QString::fromUtf8("Imprimante :"),
                         sprinters,
                         0,
                         false));
  }
}
void VenteTickets::SelectPrinter()
{
  SelectPrinter(false);
}

/**
 * About box
 */
void VenteTickets::About()
{
  QString about = "<h3>Vente de tickets :<h3>";
  about += QString::fromUtf8("<h4>Développeur(s) :</h4>");
  about += "<ul>";
  about += "<li> Simon Lopez";
  about += "<li> Mathieu Briand";
  about += "</ul>";
  about += QString::fromUtf8("<h4>Basé sur </h4>");
  about += "Qt ";
  about += QT_VERSION_STR;
  static QMessageBox* mbox = new QMessageBox (QMessageBox::Information,
                                              QString::fromUtf8("À propos"),
                                              about);
  mbox->setButtonText ( 1, "OK" );
  mbox->show();
}

/**
 * Set printer name
 * @param name name of the printer
 */
bool VenteTickets::SetPrinterInfo(QString name)
{
  QList<QPrinterInfo> printers = QPrinterInfo::availablePrinters();
  for (int c = 0; c < printers.size(); ++c)
  {
    if (printers[c].printerName()==name
        || printers[c].printerName().indexOf(name,1)!=-1)
    {
      Printer.setPrinterName(printers[c].printerName());
      Printer.setColorMode(QPrinter::GrayScale);
      Printer.setPageMargins(0,0,0,0,QPrinter::Millimeter);
#ifdef Q_WS_WIN
      Printer.setPaperSize(QSizeF(70,2000),QPrinter::Millimeter);
#else
      Printer.setPaperSize(QPrinter::A4);
      Printer.setPaperSize(QSize(Printer.paperSize(QPrinter::Millimeter).width()
                                 ,2000)
                           ,QPrinter::Millimeter);
#endif
      printers.clear();
      return true;
    }
  }
  printers.clear();
  return false;
}

/**
 * Print 10 tickets
 */
void VenteTickets::Print1()
{
  lcd1tik->display(lcd1tik->intValue()+1);
  logFile.log(lcd1tik->intValue(), lcd2tik->intValue());
  Print(uniteCarnet);
}

/**
 * Print 20 tickets
 */
void VenteTickets::Print2()
{
  lcd2tik->display(lcd2tik->intValue()+1);
  logFile.log(lcd1tik->intValue(), lcd2tik->intValue());
  Print(2*uniteCarnet);
}

/**
 * Print tickets
 * @param nb number of tickets to print
 */
void VenteTickets::Print(int nb)
{
  QPainter Painter(&Printer);
  int header=0;
  Painter.setPen(Qt::blue);
#ifdef Q_WS_WIN
  Painter.setFont(QFont("Arial", 15, 1));
#else
  Painter.setFont(QFont("Arial", 50, 1));
#endif
  Painter.setViewport(Printer.pageRect ());
  if(EventName!="")
  {
#ifdef Q_WS_WIN
    header=30;
    Painter.drawText(QRect(0,
                           0,
                           Printer.pageRect().width(),
                           20),
                     Qt::AlignCenter,
                     EventName);
#else
    header=100;
    Painter.drawText(QRect(0,
                           0,
                           Printer.pageRect().width(),
                           50),
                     Qt::AlignCenter,
                     EventName);
#endif
  }
  for(int i=0;i<(nb/2);i++)
  {
    Painter.drawImage(QPoint(0,i*ticketImg.height()+header),
                      ticketImg);
    Painter.drawRect(0,
                     i*ticketImg.height()+header,
                     ticketImg.width(),
                     ticketImg.height());
    Painter.drawImage(QPoint(ticketImg.width(),i*ticketImg.height()+header),
                      ticketImg);
    Painter.drawRect(ticketImg.width(),
                     i*ticketImg.height()+header,
                     ticketImg.width(),
                     ticketImg.height());
  }

  if (nb%2 == 1)
  {
    Painter.drawImage(QPoint(0,(nb/2)*ticketImg.height()+header),
                      ticketImg);
    Painter.drawRect(0,
                     (nb/2)*ticketImg.height()+header,
                     ticketImg.width(),
                     ticketImg.height());
  }

  Painter.end();
}

/**
 * Set number of tickets per group
 * @param nb number of tickets per group
 */
void VenteTickets::setUniteCarnet(int unite)
{
  QString str;

  uniteCarnet = unite;

  str = QString("Carnet de ").append(QString::number(uniteCarnet)).append(" tickets :");
  tik1label->setText(str);
  str = QString("Carnet de ").append(QString::number(2 * uniteCarnet)).append(" tickets :");
  tik2label->setText(str);

  str = QString::number(uniteCarnet).append(" tickets");
  vente1->setText(str);
  str = QString::number(2 * uniteCarnet).append(" tickets");
  vente2->setText(str);
}

/**
  * Prompt user for number of tickets per group
  */
void VenteTickets::SelectNbTickets()
{
  int nb = QInputDialog::getInt(this,
                                QString::fromUtf8("Nombre de tickets par carnet"),
                                QString::fromUtf8("Nombre de tickets (carnet simple) :"),
                                uniteCarnet, 1, 100);
  setUniteCarnet(nb);
}

/**
 * Reset all counters
 */
void VenteTickets::ResetCompteurs()
{
  lcd1tik->display(0);
  lcd2tik->display(0);
  logFile.log(lcd1tik->intValue(), lcd2tik->intValue());
}


/**
 * Open log file
 * @param fileName lof file name
 */
void LogFile::loadLogFile(string fileName)
{
  char buf[50];
  tm timeinfo;
  time_t ttime;
  int t1, t2;

  ticket1Count = 0;
  ticket2Count = 0;

  logFile.open(fileName.c_str(), fstream::in | fstream::out | fstream::ate);

  if (logFile.fail())
  {
    ofstream f(fileName.c_str());
    f.close();
    logFile.open(fileName.c_str(), fstream::in | fstream::out | fstream::ate);
  }

  // On va au début de la dernière ligne du fichier
  logFile.seekg(-2, ios_base::cur);
  while ((logFile.peek() != '\n') && (logFile.tellg() > 0))
    logFile.seekg(-1, ios_base::cur);

  if (logFile.tellg() > 0)
    logFile.seekg(1, ios_base::cur);

  // Si la ligne n'est pas vide, on récupère les infos
  if (! logFile.fail())
  {
    logPos = logFile.tellg();

    logFile.getline(buf, 50);

    sscanf(buf, "%d-%d-%d %d:%d:%d %d %d",
        &(timeinfo.tm_year), &(timeinfo.tm_mon), &(timeinfo.tm_mday),
        &(timeinfo.tm_hour), &(timeinfo.tm_min), &(timeinfo.tm_sec),
        &t1, &t2);

    timeinfo.tm_year -= 1900;
    timeinfo.tm_mon--;
    timeinfo.tm_isdst = 0;

    ttime = mktime(&timeinfo);

    // Si le log date d'il y a moins de deux heures, on charge les nombres de ventes
    if ((time(NULL) - ttime)  < 7200)
    {
      ticket1Count = t1;
      ticket2Count = t2;
    }
    else
    {
      logFile.seekg(0, ios_base::end);
      logPos = logFile.tellg();
    }
  }
  else
  {
    logPos = 0;
    logFile.clear();
  }
}

/**
 * Get how many time 1st type tickets group has been printed
 */
int LogFile::getCount1()
{
  return ticket1Count;
}

/**
 * Get how many time 2nd type tickets group has been printed
 */
int LogFile::getCount2()
{
  return ticket2Count;
}


/**
 * Save how many time each types of tickets group has been printed
 */
void LogFile::log(int t1, int t2)
{
    char buf[50];
    time_t t;

    ticket1Count = t1;
    ticket2Count = t2;

    logFile.seekg(logPos, ios_base::beg);

    t = time(NULL);
    strftime(buf, 50, "%Y-%m-%d %H:%M:%S", localtime(&t));
    logFile << buf;

    snprintf(buf, 50, " %d %d", ticket1Count, ticket2Count);
    logFile << buf << endl;

    logFile.flush();
}

