#include <QApplication>
#include "GlWidget.h"

int main(int argc, char* argv[])
{
    // This just create a Window and hands the main loop
    // to Qt. All events and drawing are handled in GlWidget.
  QApplication a(argc, argv);
  GlWidget w;
  w.show();

  return a.exec();
}
