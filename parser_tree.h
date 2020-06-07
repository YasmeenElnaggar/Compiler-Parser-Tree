#ifndef PARSER_TREE_H
#define PARSER_TREE_H

#include <iostream>
#include <string.h>
#include <vector>
#include <list>
using namespace std;

class Node {
  public:
    /* Nodes shape */
    enum Node_Type{
      undefined, rectangle, ellipse
    };

    /* Node info */
    Node_Type Type;
    string   Title, Details;
    Node*    Left_child;
    Node*    Right_child;
    Node*    If_ElsePart;    //3ashn al if node al wa7edah ali momken yb2a leha third child
    list<Node*> Next_to;     //ba2y al nodes ali laz2en feha ali fo2 dol 3ayalha

    Node()
    {
        Type = undefined;
        Title = " ";
        Details = " ";
        Left_child = NULL;
        Right_child = NULL;
        If_ElsePart = NULL;
    }

    ~Node()
     {
        delete Left_child;
        delete Right_child;
        delete If_ElsePart;
     }
};

class Parser{
public:
    /* Parser tree variables */
    string token;
        Parser() {  z = 0;   Match = true;}

        /* fill the vector with input scanner tokens to the parser "bnzbat al input lal parser" */
        void Parser_input (string scanner_output)
        {
            string token_value, token_type;
            bool comma_find = false;
            int size ;

            for (int i=0; i<scanner_output.length(); i++)
            {
                if ( (scanner_output[i] != ',') && (comma_find == false) )
                {
                    token_value.push_back(scanner_output[i]);
                }

                else if ( (Is_A_letter(scanner_output[i])) && (comma_find == true))
                {
                    token_type.push_back(scanner_output[i]);
                }

                else if(scanner_output[i] == '\n')
                {
                    tokenvalue_and_tokentype.push_back(make_pair(token_value,token_type));
                    size  = token_value.size();
                    for (int k=0; k<size; k++) token_value.pop_back();

                    size  = token_type.size();
                    for (int j=0; j<size; j++) token_type.pop_back();
                    comma_find = false;
                }

                else
                    comma_find = true;
            }

            token = tokenvalue_and_tokentype[z].first;  //kdh awel value heneh htkon read
            if (token[token.length()-1]==' ') token.pop_back();
        }

        /* 1.EBNF "Program-> stmt_sequence"*/
        Node* Program(void)
        {
            z = 0;
            Node* program = new Node();
            program = Stmt_Sequence();
            return program;
        }

private:
     /* Parser tree variables */
     int z;
     enum StatementTypes { IF, REPEAT, ASSIGN, READ, WRITE, ERROR };
     vector <pair<string,string>> tokenvalue_and_tokentype;
     bool Match;
     bool Is_A_Digit(char c)
     {
        return (c>='0' && c <='9')? true:false;
     }

     bool Is_A_letter(char c)
     {
        return ( (c>='a' && c <='z')  || (c>='A' && c <='Z') )? true:false;
     }

     bool Is_a_Num(string s)
     {
        bool flag = false;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= '0' && s[i] <= '9')
                 flag = true;

            else
              return (false);
        }
        return (flag);
     }

     bool Is_An_ID (string inword)
     {
        int state = 1;
        int i=0;
        //base case:
        if (inword == "read" || inword=="write" || inword=="repeat" || inword=="assign" || inword=="until" ||inword == "if")
            return  false;

            if ( (inword[i]>='a' && inword[i]<='z') || (inword[i]>='A' && inword[i]<='Z') )
            {
                if (inword.length() == 1 )
                    return  true;

                state = 2;
                i++;
                while (state == 2)
                {
                   if ( (inword[i]>='a' && inword[i]<='z') || (inword[i]>='A' && inword[i]<='Z') )
                           i++;
                   else
                     return false;

                   if (i == inword.length() )
                         return true;
                }
            }
            else
                return false;
        }

        void match(string s)
        {
            if (z!=tokenvalue_and_tokentype.size())
            {
               if (s == tokenvalue_and_tokentype[z].second)
               {
                   z++;
                   Match = true;
                   if (z == tokenvalue_and_tokentype.size()) return ;
                   token = tokenvalue_and_tokentype[z].first;
                    if (token[token.length()-1]==' ') token.pop_back();
               }
            }
            else
            {
                Match = false;
            }
        }

        /* 2.EBNF "Stmt_Sequence->statement {; statement}"*/
        Node* Stmt_Sequence(void)
        {
            Node* stmt_seq = new Node();
            Node* next_node = new Node();
            stmt_seq = Stmt();
            if (stmt_seq == NULL) return stmt_seq;

            while (token == ";" || token == "; " || token == " ; " || token == " ;")
            {
                match("SEMICOLON");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                next_node = Stmt();
                if (next_node == NULL) return next_node;
                stmt_seq->Next_to.push_back(next_node);
            }

            //if (z != tokenvalue_and_tokentype.size()) return NULL;
            return stmt_seq;
        }

        /* 3.EBNF "statement-> if_stmt | read_stmt | write_stmt | repeat_stmt | assign_stmt" */
        Node* Stmt(void)
        {
            Node* stmt = new Node();
            if (tokenvalue_and_tokentype[z].second == "IF")               stmt = If_Stmt();
            else if (tokenvalue_and_tokentype[z].second == "REPEAT")      stmt = Repeat_Stmt();
            else if (tokenvalue_and_tokentype[z].second == "UNTIL")       stmt = Repeat_Stmt();
            else if (tokenvalue_and_tokentype[z].second == "IDENTIFIER")  stmt = Assign_Stmt();
            else if (tokenvalue_and_tokentype[z].second == "READ")        stmt = Read_Stmt();
            else if (tokenvalue_and_tokentype[z].second == "WRITE")       stmt = Write_Stmt();
            else {
                return  NULL;
            }

            return stmt;
        }

        /* 4. EBNF "if_stmt-> if exp then stmt_sequence [else stmt_Sequence] end" */
        Node* If_Stmt(void)
        {
            Node* if_stmt = new Node();
            if_stmt->Type = if_stmt->rectangle;
            if_stmt->Title = "if";
            match("IF");
            if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
            if_stmt->Left_child = exp();
            match("THEN");
            if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
            if_stmt->Right_child = Stmt_Sequence();
            if (token == "else")
            {
                match("ELSE");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                if_stmt->If_ElsePart = Stmt_Sequence();
            }
            match("END");
            if (Match == false) return NULL;
            return if_stmt;
        }

        /* 5. EBNF "repeat_stmt-> repeat stmt_sequence until exp" */
        Node* Repeat_Stmt(void)
        {
            Node* repeat_Stmt = new Node();
            repeat_Stmt->Type = repeat_Stmt->rectangle;
            repeat_Stmt->Title = "repeat";
            match("REPEAT");
            if (Match == false) return NULL;
            repeat_Stmt->Left_child = Stmt_Sequence();
            match("UNTIL");
            if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
            repeat_Stmt->Right_child = exp();
            if ( repeat_Stmt->Right_child == NULL) return NULL;
            return repeat_Stmt;
        }

        /* 6. EBNF "assign_stmt-> Identifier := exp" */
        Node* Assign_Stmt(void)
        {
            Node* assign_stmt = new Node();
            assign_stmt->Type = assign_stmt->rectangle;
            assign_stmt->Title = "assign";
            assign_stmt->Details = tokenvalue_and_tokentype[z].first;  //ali howa al id
            match("IDENTIFIER");
            if (Match == false) return NULL;
            match("ASSIGN");
            if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
            assign_stmt->Left_child = exp();
            if (assign_stmt->Left_child == NULL) return NULL;
            return assign_stmt;
        }

        /* 7. EBNF "read_stmt-> read Identifier" */
        Node* Read_Stmt(void)
        {
            Node* read_stmt = new Node();
            read_stmt->Type = read_stmt->rectangle;
            read_stmt->Title = "read";
            match("READ");
            if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
            match("IDENTIFIER");
            if (Match == false) return NULL;
            read_stmt->Details = tokenvalue_and_tokentype[z-1].first;
            return read_stmt;
        }

        /* 8. EBNF "write_stmt-> write exp" */
        Node* Write_Stmt(void)
        {
            Node* write_stmt = new Node();
            write_stmt->Type = write_stmt->rectangle;
            write_stmt->Title = "write";
            match("WRITE");
            if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
            write_stmt->Left_child = exp();
            if (  write_stmt->Left_child  == NULL) return  NULL;
            return write_stmt;
        }

        /* 9. EBNF "exp-> simple_exp {comparison_opp simple_exp}" */
        Node* exp(void)
        {
            Node* Exp = new Node();
            Exp = Simple_exp();
            if (Exp == NULL) return NULL;
            while(token == "<" || token == "=")
            {
               Node* Exp_temp = new Node();
               Exp_temp = Exp;
               Exp = Comparison_Op();
               if (Exp == NULL) return NULL;
               Exp->Left_child = Exp_temp;
               Exp->Right_child = Simple_exp();
               if (Exp->Right_child == NULL) return NULL;
            }
            return Exp;
        }

        /* 10. EBNF "simple_exp-> term {addop term}" */
        Node* Simple_exp(void)
        {
            Node* simple_exp = new Node();
            simple_exp = Term();
            if (simple_exp == NULL) return NULL;
            while(token == "+" || token == "-")
            {
              Node* simple_exp_temp = new Node();
              simple_exp_temp = simple_exp;
              simple_exp = AddOp();
              if (simple_exp == NULL) return NULL;
              simple_exp->Left_child = simple_exp_temp;
              simple_exp->Right_child = Term();
              if (simple_exp->Right_child == NULL) return NULL;
            }
            return simple_exp;
        }


        /* 11. EBNF "comparison_opp-> < | = " */
        Node* Comparison_Op(void)
        {
            Node* comparison_op = new Node();
            comparison_op->Type = comparison_op->ellipse;
            comparison_op->Title = "op";
            if (token == "<")
            {
               match("LESSTHAN");
               if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
               comparison_op->Details = "(<)";
            }
            else if (token == "=")
            {
                match("EQUAL");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                comparison_op->Details = "(=)";
            }
            return comparison_op;
        }

        /* 12. EBNF " add_op-> + | - " */
        Node* AddOp(void)
        {
            Node* addop = new Node();
            addop->Type = addop->ellipse;
            addop->Title = "op";

            if (token == "+")
            {
                match("PLUS");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                addop->Details = "(+)";
            }
            if (token == "-")
            {
                match("MINUS");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                addop->Details = "(-)";
            }
            return addop;
        }


        /* 13. EBNF " term-> factor {mulop factor} " */
        Node* Term(void)
        {
            Node* term = new Node();
            term->Type = term->ellipse;
            term =Factor();
            if (term == NULL) return NULL;
            while (token == "*" || token == "/")
            {
                Node* Termo = new Node();
                Termo = term;
                term = MulOp();
                if (term == NULL) return NULL;
                term->Left_child  = Termo;
                term->Right_child = Factor();
                if (term->Right_child == NULL) return NULL;
            }
            return term;
        }

        /* 14. EBNF mulop -> * | / */
        Node* MulOp()
        {
            Node* mulop = new Node();
            mulop ->Type = mulop ->ellipse;
            mulop ->Title = "op";

            if (token == "*")
            {
                match("MULT");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                mulop ->Details = "(*)";
            }
            if (token == "/")
            {
                match("DIV");
                if (Match == false || z==tokenvalue_and_tokentype.size()) return NULL;
                mulop ->Details = "(/)";
            }
            return mulop ;
        }

        /* 15. EBNF "Factor-> (exp) | number | identifier" */
        Node* Factor()
        {
            Node* factor = new Node();
            factor->Type = factor->ellipse;
            /*It can be (exp) */
            if (token == "(")
            {
                match("OPENBRACKET");
                if (Match == false) return NULL;
                factor = exp();
                if (factor == NULL)  return NULL;
                match("CLOSEDBRACKET");
                 if (Match == false) return NULL;

            }
            /* Or it can be a number */
            else if (Is_a_Num(token))
            {
                match("NUMBER");
                if (Match == false) return NULL;
                factor->Details = "("+tokenvalue_and_tokentype[z-1].first+")";
                factor->Title = "const";
            }
            /* Or it can be an Identifier */
            else if (Is_An_ID(token))
            {
                match("IDENTIFIER");
                if (Match == false) return NULL;
                factor->Details = "("+tokenvalue_and_tokentype[z-1].first+")";
                factor->Title = "id";
            }

            else
            {
                Match = false;
                return NULL;
            }

            return factor;
        }


};
#endif // PARSER_TREE_H
