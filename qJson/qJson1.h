#pragma once

#include<string.h>
#include<stdio.h>
#include<stdlib.h>


enum ValType
{
    JSONOBJECT = 0,
    STRING,
    INT

};
class QJsonObject;

typedef struct QJsonChild {
    char* key;
    int type = 0;
    char* valStr;
    QJsonObject* valObj;

    QJsonChild* next;
}QJsonChild;


class QJsonObject
{
public:
    static QJsonObject* parseObject(char* str);
public:
    char* getString(const char* key);
    QJsonObject* getJsonObject(const char* key);
private:
    QJsonChild* m_jsonChild;
};

