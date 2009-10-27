#include <QApplication>
#include "ventetickets.h"
//
QString AppVersion("0.1");
int main(int argc, char ** argv)
{
  QApplication app( argc, argv );
  VenteTickets win;
  win.show();
  app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
  return app.exec();
}
