#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QPalette>
#include <QIcon>
#include <QSize>
#include <QFont>
#include <QObject>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include <QTreeView>
#include <second_window.h>

class MyMainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MyMainWindow() {}  //Constructor

    void Execute_MainWindow_Icon (void)
    {
      QIcon icon ("E:/Racing.Team/Weekly Documentation/logo gded.png");
      this->setWindowIcon(icon);
      QSize qsize;
      qsize.scale(30,30,Qt::KeepAspectRatio);
      this->setIconSize(qsize);
      this->setFixedSize(800,500);
    }

    void Execute_MainWindow_StartPushButton(void)
    {
      QPushButton *start_button = new QPushButton(this);
      start_button->setText("Parser Project");
      start_button->setGeometry(240,220,330,80);
      start_button->setStyleSheet("background-color: rgba(255,204,204)");
      QFont start_text;
      start_text.setBold(true);
      start_text.setPixelSize(50);
      start_text.setWeight(20);
      start_button->setFont(start_text);
      QPalette button_text_color;
      button_text_color.setColor(start_button->foregroundRole(), Qt::blue);
      start_button->setPalette(button_text_color);
      start_button->show();
      QObject:: connect(start_button,SIGNAL(clicked()),this, SLOT(On_start_button_Clicked()));
    }

    void Execute_Main_Label(void)
    {
        QLabel *label_pic = new QLabel(this);
        label_pic->setText("Parser Project");
        label_pic->setGeometry(200,240,350,60);
        QFont label_font;
        label_font.setPixelSize(40);
        label_font.setBold(true);
        label_pic->setFont(label_font);
        label_pic->setAlignment(Qt::AlignCenter);
        label_pic->setStyleSheet("background-color: rgba(102,230,255)");
        //label_pic->setAttribute(Qt::transparent);

        QPalette text_color;
        QColor color;
        color.setRgb(255,247,230);
        text_color.setColor(label_pic->foregroundRole(),color);
        label_pic->setPalette(text_color);
        label_pic->show();
    }

    void Execute_MainWindow_Image (void)
    {
      QLabel *label_pic = new QLabel(this);
      label_pic->setGeometry(0,0,800,500);
      label_pic->setAutoFillBackground(true);
      label_pic->setAlignment(Qt::AlignRight);
      QPixmap pix("E:/Electrical Departement/4th CSE/1st term/Compilers/new_mazbota.jpg");
      label_pic->setPixmap(pix.scaled(800,500,Qt::KeepAspectRatio));
      label_pic->setAlignment(Qt::AlignCenter);
      label_pic->show();

    }

    //E:/Racing.Team/Weekly Documentation/logo large.jpg
    void Exit_MainWindow(void){
        this->hide();
    }

    void Show_MainWindow(void){
        this->show();
    }

public slots:

    void On_start_button_Clicked (void){
       this->Exit_MainWindow();
       Second_Window *Window_2 = new Second_Window ();
       Window_2->setWindowTitle("Parser Project");
       Window_2->setStyleSheet("background-color: seal brown");
       Window_2->setFixedSize(700,500);
       Window_2->show();
       Window_2->Execute_Enter_Button(260,410,200,50);
       Window_2->Add_Label("Scanner TINY Language Code : ",130,80,320,50);
       Window_2->Execute_Horizontal_Top_Layout();
       Window_2->Execute_Vertical_Left_Layout();
       Window_2->Add_TextBox(130,135,500,250);
    }

};

#endif // MYMAINWINDOW_H
