#ifndef THIRD_WINDOW_H
#define THIRD_WINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QFont>
#include <QColor>
#include <QObject>
#include <QString>
#include <QTextStream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include<QPainter>
#include<parser_tree.h>
#include<QPaintEvent>

class Third_Window: public QMainWindow
{
  Q_OBJECT

public:
        QGraphicsScene* scene = new QGraphicsScene(this);
        QGraphicsView*  view = new QGraphicsView (this);
        QLabel* main_label = new QLabel (this);

        int X = 0 , Y = 0;
        int dx = 0, dy=0;
        int right_child_dx = 530, left_child_dx=100,   else_child_dx=400;  //zman fl awl knet right_child_dx = 110 wl left = 30
        int next_x = 0;

    Third_Window() {}

    /*
    void Execute_Back_Button (int x, int y, int w, int h)
    {
        //Create "next Button"
       next_button->setGeometry(x,y,w,h);

       //design the font of the "next Button" text:
       next_button->setText("Back");
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
       QObject:: connect(next_button,SIGNAL(clicked()),this, SLOT(On_Back_button_Clicked()));
    }
    */

    void add_label(string s)
    {
        QString Qs  = QString::fromStdString(s);
        QFont label;
        label.setFamily("Segoe UI Emoji");
        label.setPixelSize(20);

        QPalette text_color;
        QColor color;
        color.setRgb(255,255,255);
        text_color.setColor(main_label->foregroundRole(),color);

        main_label->setText("-"+Qs);
        main_label->setFont(label);
        main_label->setGeometry(30,30,500,32);
        main_label->setAlignment(Qt::AlignCenter);
        main_label->setPalette(text_color);
        main_label->show();
    }

    void set_graphicview (void)
    {
        QBrush color (Qt::blue);
        //Set the Graphic view:
        view->setFrameStyle(0);
        view->setBackgroundBrush(color);
        //view->setStyleSheet("background-colo: blue");
        view->setVisible(true);
        view->setGeometry(0,0,900,600);
        view->scroll(100,100);
        view->show();
    }

    void draw(Node* current_node)
    {
        QBrush cyanBrush(Qt::green);
        QBrush magentaBrush(Qt::red);
        QPen   black(Qt::black);
        QPen   line(Qt::gray);
        QPen   lin(Qt::red);
        black.setWidth(2);
        line.setWidth(3);
        QFont node_font;
        node_font.setBold(true);
        node_font.setPixelSize(11);

        int X_Start = X + dx , Y_Start = Y + dy;
        int temp_X = X_Start , temp_Y = Y_Start;  //temp_X = 150 , temp_Y = 0
        int temp_dx=dx ,temp_dy=dy;
        int save_dx = 0;

        //1.convert string to Qstring to draw:
        QString QTitle  = QString::fromStdString(current_node->Title);
        QString QDetails= QString::fromStdString(current_node->Details);

        if (current_node->Type == current_node->rectangle)
        {
            scene->addRect(X_Start,Y_Start,80,50,black,magentaBrush);
            scene->addText(QTitle,QFont(node_font))->setPos(X_Start+18,Y_Start+5);
            scene->addText(QDetails,QFont(node_font))->setPos(X_Start+18,Y_Start+20);
        }

        if (current_node->Type == current_node->ellipse)
        {
          scene->addEllipse(X_Start,Y_Start,80,50,black,cyanBrush);
          scene->addText(QTitle,QFont(node_font))->setPos(X_Start+22,Y_Start+5);
          scene->addText(QDetails,QFont(node_font))->setPos(X_Start+22,Y_Start+20);
        }

        if (current_node->Left_child != NULL)
        {
            if (current_node->Right_child == NULL)
            {
                //make a straight line:
                dy = 50;
                Y = Y_Start + 50;
                scene->addLine(X_Start+40,Y,X_Start+40,Y+dy,line);
                X = X_Start;
                dx = 0;
            }

            else
            {
                //it's a leaf node:
                if ((current_node->Left_child->Right_child == NULL) && (current_node->Left_child->Left_child == NULL))
                    X = X_Start - 20;

                else
                      X = X_Start-left_child_dx ;

                dy = 50;
                Y = Y_Start + 50;
                dx = -40;
                scene->addLine(X_Start+40,Y,X,Y+dy,line);
                left_child_dx -=10 ;
            }

            draw(current_node->Left_child);
            X_Start = temp_X;    Y_Start = temp_Y;
            dx = temp_dx;        dy = temp_dy;
        }

        if (current_node->Right_child != NULL)
        {
            dy = 50;
            Y = Y_Start + 50;
            //this mean that node is a leaf
            if ((current_node->Right_child->Right_child == NULL) && (current_node->Right_child->Left_child == NULL))
                X = X_Start + 100;

            else if (current_node->Right_child->Right_child == NULL)
            {
                X = X_Start + 200;
            }

            else
            {
               X = X_Start+right_child_dx;
               right_child_dx += 250;
            }

            dx = -40;
            scene->addLine(X_Start+40,Y,X,Y+dy,line);
            draw(current_node->Right_child);
            X_Start = temp_X;         Y_Start = temp_Y;
            dx = temp_dx;             dy = temp_dy;
        }

        if (current_node->If_ElsePart != NULL)
        {
            dy = 50;
            Y = Y_Start + 50;
            X = X_Start + else_child_dx;
            scene->addLine(X_Start+40,Y,X,Y+dy,line);
            dx = -40;
            draw(current_node->If_ElsePart);
            X_Start = temp_X;         Y_Start = temp_Y;
            dx = temp_dx;             dy = temp_dy;
           // else_child_dx += 200;
        }

        if (current_node->Next_to.size() != 0)
        {
            list<Node*> L = current_node->Next_to;
            for (list<Node *>::iterator it = L.begin(); it != L.end(); it++)
            {
               X = X_Start + 80;
               //law leh node wa7da laz2ha feh wa 3ndo child wa7ed aw m3ndosh
               if ( (current_node->Next_to.size() == 1) && ((current_node->Left_child == NULL) || (current_node->Right_child == NULL)))
               {
                   dx = 130;
               }

                //law lazh2h feh node wa7dah wa al current node leha 2 child
               else if ((current_node->Next_to.size() == 1) && ((current_node->Left_child != NULL) && (current_node->Right_child != NULL)))
               {
                   dx = 420;
               }

               //henah b2a 3ando aktr mn node laz2ha feh fkol distance betzeed
               else if (current_node->Next_to.size()>1)
               {
                   dx = (save_dx) + 200 + next_x;
                   next_x += 380;
               }

               Y = Y_Start - dy;
               save_dx = dx;
               scene->addLine(X,Y_Start+25,X+dx,Y_Start+25,lin);
               draw(*it);
            }
        }
        view->setScene(scene);
    }


public slots:

  void On_Back_button_Clicked(){


  }


};

#endif // THIRD_WINDOW_H
