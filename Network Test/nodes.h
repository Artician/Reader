#ifndef NODES_H_INCLUDED
#define NODES_H_INCLUDED

#include <vector>

using namespace std;

struct dictPay
{
    vector<string> defn;
    vector<string> context;
    string entry;
    string partSp;
    string etym;
};

struct connection
{
    void *path;
    int counter;
};

template <class T>
class node
{
public:
    string getType();
    void create();

private:
    T info;
    vector<connection>routeTable;
};

class dict
{
public:
    dict();
    dict(string type, dictPay *payload);

    string getType();

private:
    string type;
    dictPay *payload;
};

class root
{
public:
    void setName(string name);
    string getName();

private:
    string name;
};
#endif // NODES_H_INCLUDED
