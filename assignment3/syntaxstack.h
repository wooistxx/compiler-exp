

#ifndef _SYNTAX_STACK_H_
#define _SYNTAX_STACK_H_

#include <iostream>
#include <deque>
#include <map>

using namespace std;


// typedef enum class GrammaticalSymbols
// {
//     program, 
//     stats, 
//     assignment, 
//     e, 
//     ee, 
//     t, 
//     tt, 
//     f, 
// // 这一段跟文法符号的定义是一样的
// // enum class 不需要 friend ostream& operator<<(ostream&,const Date&);
// } GS;

// map<GS, string> reGS; // for pretty print

// ostream & operator << (ostream & stream, const GS & e)
// {
//     stream << reGS[e];
//     return stream;
// }



//typedef stack<GS> SyntaxStack;
class SyntaxStack : public deque<enum yytokentype>
{
public:
    void print()
    {
        for(deque<enum yytokentype>::iterator i=begin();i!=end();i++)
        {
            cout << reToken[*i] << " ";
        }
        cout << endl;
    }

    void push(const enum yytokentype & t)
    {
        push_back(t);
    }
    
    enum yytokentype & pop()
    {
        enum yytokentype & tmp = back();
        pop_back();
        return tmp;
    }

    enum yytokentype & top()
    {
        return back();
    }



// stack 只能从一个方向插入数据
// private:
    void push_front(const enum yytokentype &) = delete;
    enum yytokentype pop_front() = delete;
    enum yytokentype & front() = delete;


};


#endif
