#include <QApplication>
#include <mymainwindow.h>

int main (int argc, char *argv[])
{
   QApplication app (argc,argv);

   /* Creating the main window:  */
   MyMainWindow *Main_Window = new MyMainWindow();
   Main_Window->setStyleSheet("background-color: white");
   Main_Window->setWindowTitle("Compiler Parser Project");
   Main_Window->show();

   /* display Main Window Icon "in the top left": */
   Main_Window->Execute_MainWindow_Icon();

   /* display Home page intro image: */
   Main_Window->Execute_MainWindow_Image();

   //Main_Window->Execute_Main_Label();

   /* Create a start Push Button: */
   Main_Window->Execute_MainWindow_StartPushButton();

   return app.exec();
}

