#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QObject>
#include <QMessageBox>
#include <QComboBox>
#include <QStringList>
#include <QString>
#include <QTextEdit>
#include <QTextStream>
#include <QSize>
#include <QTextBrowser>
#include <third_window.h>
#include <parser_tree.h>

class Second_Window: public QMainWindow
{
  Q_OBJECT

public:
    Second_Window(){}
    QTextEdit *text = new QTextEdit (this);
    QLabel *label_1 = new QLabel(this);
    QPushButton *next_button = new QPushButton(this);
    QString result = "Non_Token";

    void Add_Label (QString text,int x, int y, int w, int h)
    {
        label_1->setGeometry(x,y,w,h);
        label_1->setText(text);
        QFont label_1_Font;
        label_1_Font.setFamily("Segoe UI Emoji");
        label_1_Font.setWeight(7);
        label_1_Font.setPixelSize(23);
        label_1->setFont(label_1_Font);
        label_1->show();
    }
 
    void Execute_Enter_Button (int x, int y, int w, int h)
    {
        //Create "next Button"  
       next_button->setGeometry(x,y,w,h);

       //design the font of the "next Button" text:
       next_button->setText("Parse");
       QFont next_button_text;
       next_button_text.setBold(true);
       next_button_text.setPixelSize(30);
       next_button_text.setWeight(10);
       next_button->setFont(next_button_text);

       //design the color of the button text and BG:
       QPalette button_text_color;
       QColor color_text;
       color_text.setRgb(0,0,0);  //black color
       button_text_color.setColor(next_button->foregroundRole(), color_text);       
       next_button->setPalette(button_text_color);
       next_button->setStyleSheet("background-color: lightblue");

       //display the button
       next_button->show();

       //action of the button click event:
       QObject:: connect(next_button,SIGNAL(clicked()),this, SLOT(On_Enter_button_Clicked()));
    }

    void Add_TextBox (int x, int y, int w, int h)
    { 
      text->setGeometry(x,y,w,h);
      text->setFontFamily("Segoe UI Emoji");
      text->setFontWeight(20);
      QFont label_1_Font;
      label_1_Font.setPixelSize(15);
      text->setFont(label_1_Font);
      text->setStyleSheet("background-color: white");
      text->scroll(50,50);
      text->show();
    }

    void Add_txt_of_TextEdit (QString s)
    {
        text->setText(s);
    }

    QString txt_of_TextEdit(void)
    {
        return text->toPlainText();
    }

    void Execute_Horizontal_Top_Layout(void)
    {
      QLabel *Top_Panel = new QLabel (this);
      Top_Panel->setGeometry(0,0,700,80);
      Top_Panel->setText("Compiler Parser Project");

      QFont text_font;
      text_font.setFamily("Segoe UI Emoji");
      text_font.setPixelSize(30);
      text_font.setBold(true);
      Top_Panel->setFont(text_font);

      QPalette text_color_1;
      QColor color_1;
      color_1.setRgb(179,255,229); //pale blue
      text_color_1.setColor(Top_Panel->foregroundRole(),color_1);
      Top_Panel->setPalette(text_color_1);
      Top_Panel->setStyleSheet("background-color: lightblue");

      Top_Panel->show();
    }

    void Execute_Vertical_Left_Layout(void)
    {
      QLabel *panel_2 = new QLabel(this);
      panel_2->setGeometry(0,80,100,420);
      panel_2->setStyleSheet("background-color: rgba(241,156,187)");
      panel_2->show();
    }



 public slots:
    void On_Enter_button_Clicked(){
        QString file_in, file_out;
        QString line_of_file;
        file_in = txt_of_TextEdit();  //the string

        //convert from Qstring to string
        string parserinput = file_in.toLocal8Bit().constData();
        parserinput.push_back('\n');

        Node* Tree = new Node();

        Parser P;
        P.Parser_input(parserinput);
        Tree = P.Program();

        Parser R;
        R.Parser_input(parserinput);
        Tree = R.Program();

        Third_Window *Window_3 = new Third_Window ();
        Window_3->setStyleSheet("background-color: blue");
        Window_3->show();
         if (Tree != NULL)
         {
            Window_3->setWindowTitle("Syntax tree");
            Window_3->setFixedSize(900,600);
            Window_3->set_graphicview();
            Window_3->add_label("The input grammar is valid, and The Syntax Tree is:");
            Window_3->draw(Tree);
         }

         else
         {
             Window_3->setWindowTitle("Error Message");
             Window_3->setFixedSize(600,80);
             Window_3->add_label("The input grammar isn't valid");
             Window_3->setStyleSheet("background-colo: white");
         }

         /*
         else
         {

         }
         */

         /*
        for (int i=0; i<file_in.length(); i++)
        {
            if (file_in[i] == '\n')
                file_in[i] = ' ';
        }
        file_in.push_back(' ');
        file_out = File_Token_Types(file_in);

        //The Output:
        QTextBrowser *message_box = new QTextBrowser();
        message_box->setText(file_out);
        message_box->setWindowTitle("Parser Output");
        message_box->scroll(50,50);
        QSize message_box_size;
        message_box_size.scale(800,250,Qt::KeepAspectRatio);
        message_box->setFixedSize(message_box_size);
        message_box->show();
        */
    }


};

#endif // SECOND_WINDOW_H
