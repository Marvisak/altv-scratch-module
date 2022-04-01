#include "MultiType.h"
#include <ostream> // the code will compile on g++ without this "include" statement, but you'll get a very weird bug
                   // Explanation: without this statement, when you call "ostream& operator<<(std::ostream& out, const MultiType& obj)",
                   // this is what will happen if the MultiType passed in is a double: (if it's a string, this operator will behave as expected)
                   // 1. obj.type is checked and it is a DOUBLE
                   // 2. "out << obj.doubleVar" is called, but since we haven't included ostream, the compiler can't find the function "ostream& operator<< (double val);"
                   // 3. As a result, the compiler implicitly converts obj.doubleVar to a MultiType using the constructor MultiType::MultiType(double d)
                   // 4. This newly created MultiType is then passed back to "ostream& operator<<(std::ostream& out, const MultiType& obj)"
                   // 5. Go back to step 1
                   // 6. This infinite recursion causes a stack overflow and the program crashes.
                   // This is one of the weirdest bugs I've ever seen! Lesson learned: implicit conversions are dangerous.

MultiType::MultiType(const std::string &s)
{
    stringVar=s;
    type=STRING;
}
MultiType::MultiType(double d)
{
    doubleVar=d;
    type=DOUBLE;
}
std::string MultiType::getString()
{
    if(type!=STRING)
    {
        stringVar=std::to_string(doubleVar);
        type=STRING;
    }
    return stringVar;
}
double MultiType::getDouble()
{
    if(type!=DOUBLE)
    {
        try
        {
            doubleVar=std::stod(stringVar);
        }
        catch(const std::invalid_argument& ia)
        {
            doubleVar=0;
        }
        type=DOUBLE;
    }
    return doubleVar;
}
void MultiType::setString(const std::string &s)
{
    stringVar=s;
    type=STRING;
}
void MultiType::setDouble(const double &d)
{
    doubleVar=d;
    type=DOUBLE;
}
MultiType::CompareResult MultiType::stringDoubleCompare(std::string s,double d) 
{ // returns EQUAL if equal, LESS if string less than double, GREATER if string greater than double
    try 
    {
        double sd=std::stod(s);
        if(sd<d) return LESS;
        else if(sd>d) return GREATER;
        else return EQUAL;
    } 
    catch (std::invalid_argument& e) 
    {
        std::string ds=std::to_string(d);
        if(s<ds) return LESS;
        else if(s>ds) return GREATER;
        else return EQUAL;
    }
}
bool MultiType::operator==(const MultiType &other) const
{
    if(type==STRING)
    {
        if(other.type==STRING)
        {
            return stringVar==other.stringVar;
        }
        else
        {
            return stringDoubleCompare(stringVar,other.doubleVar)==EQUAL;
        }
    }
    else
    {
        if(other.type==STRING)
        {
            return stringDoubleCompare(other.stringVar,doubleVar)==EQUAL;
        }
        else
        {
            return doubleVar==other.doubleVar;
        }
    }
}
bool MultiType::operator<(const MultiType &other) const
{
    if(type==STRING)
    {
        if(other.type==STRING)
        {
            return stringVar<other.stringVar;
        }
        else
        {
            return stringDoubleCompare(stringVar,other.doubleVar)==LESS; // this string must be LESS
        }
    }
    else
    {
        if(other.type==STRING)
        {
            return stringDoubleCompare(other.stringVar,doubleVar)==GREATER; // other string must be GREATER
        }
        else
        {
            return doubleVar<other.doubleVar;
        }
    }
}
bool MultiType::operator>(const MultiType &other) const
{
    return other<(*this);
}
std::ostream& operator<<(std::ostream& out, const MultiType& obj)
{
    if(obj.type==STRING)
    {
        out << obj.stringVar;
    }
    else
    {
        out << obj.doubleVar;
    }
    return out;
}
