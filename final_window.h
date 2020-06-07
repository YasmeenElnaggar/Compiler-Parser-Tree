#ifndef FINAL_WINDOW_H
#define FINAL_WINDOW_H

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
#include<mymainwindow.h>
#include <second_window.h>
#include <algorithm>

class Final_Window: public Second_Window
{
    Q_OBJECT

public:
    Final_Window() {}  //Constructor

    QString Is_An_ID (const QString inword)
    {
        int state = 1;
        int i=0;
        QString s = "Identifier";

        if ( (inword[i]>='a' && inword[i]<='z') || (inword[i]>='A' && inword[i]<='Z') )
        {
            if (inword.length() == 1 )
                return  s;
            state = 2;
            i++;
            while (state == 2)
            {
               if ( (inword[i]>='a' && inword[i]<='z') || (inword[i]>='A' && inword[i]<='Z') )
                       i++;
               else
               {
                 s = "Non_Token";
                 return s;
               }
               if (i == inword.length() )
                     return s;
            }
        }
        else {
            s = "Non_Token";
            return s;
        }
    }

    QString Is_a_Symbol(QString s)
    {
         int i = 0;
         if (s[i] == '+')
              return ("plus");

         else if (s[i] == '-')
              return ("minus");

         else if (s[i] == '*')
              return ("mul");

         else if (s[i] == '/')
                return ("div");

         else if (s[i] == '(')
             return ("left bracket");

         else if (s[i] == ')')
             return ("right bracket");

         else if (s[i] == '=')
             return ("equal");

         else if (s[i] == '<')
             return ("smaller than");

         else if (s[i] == ';')
             return ("semi colon");

         else if (s[i] == ':' && s[i + 1] == '=')
             return ("assign");

         else
             return ("Non_Token");
    }

    QString Is_a_Num(QString s)
    {
        bool flag = false;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
                flag = true;

            else
                return ("Non_Token");
        }
        return ("Num");
    }

    QString Check_Keyword(QString s)
    {
      QString ss;
      if (s=="read")       return ("READ");
      else if(s=="write")  return ("WRITE");
      else if(s=="then")   return ("THEN");
      else if(s=="else")   return ("ELSE");
      else if(s=="end")    return ("END");
      else if(s=="if")     return ("IF");
      else if(s=="until")  return ("UNTIL");
      else if(s=="return") return ("RETURN");
      else if(s=="main")   return ("MAIN");
      else if(s=="begin")  return ("BEGIN");
      else if(s=="string") return ("STRING");
      else if(s=="int")    return ("INT");
      else if(s=="real")   return ("REAL");
      else if(s=="repeat") return ("REPEAT");
      else                 return ("Non_Token");
      /*
      for (int i=0; i<s.length(); i++)
          ss[i] = s[i] - '32';
          */
    }


};
#endif // FINAL_WINDOW_H
