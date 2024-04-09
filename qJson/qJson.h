#pragma once

#include<unordered_map>
#include<map>
#include<vector>
#include<string>
#include<iostream>



class qJsonArray;

class qJsonObject
{
public:
	qJsonObject() {

	}
	std::string getString(std::string key) {
		for (std::unordered_map<std::string, std::string>::iterator it = maps_string.begin(); it != maps_string.end(); ++it) {
			if (key.compare(it->first) == 0)
			{
				return it->second;
			}
		}
		return "";
	}
	void setString(std::string key,std::string value) {
		maps_string.insert(std::make_pair(key,value));
	}
	qJsonObject getJsonObject(std::string key) {
		for (std::unordered_map<std::string, qJsonObject>::iterator it = maps_JsonObject.begin(); it != maps_JsonObject.end(); ++it) {
			if (key.compare(it->first) == 0)
			{
				return it->second;
			}
		}
		return qJsonObject();
	}
	void setJsonObject(std::string key, qJsonObject value) {
		maps_JsonObject.insert(std::make_pair(key, value));
	}
	void setInt(std::string key,int value) {
		maps_double.insert(std::make_pair(key, value));
	}
	int getInt(std::string key) {
		for (std::unordered_map<std::string, double>::iterator it = maps_double.begin(); it != maps_double.end(); ++it) {
			if (key.compare(it->first) == 0)
			{
				return it->second;
			}
		}
		return -1;
	}
	void setDouble(std::string key, double value) {
		maps_double.insert(std::make_pair(key, value));
	}
	double getDouble(std::string key) {
		for (std::unordered_map<std::string, double>::iterator it = maps_double.begin(); it != maps_double.end(); ++it) {
			if (key.compare(it->first) == 0)
			{
				return it->second;
			}
		}
		return -1;
	}
	void setFloat(std::string key, float value) {
		maps_double.insert(std::make_pair(key, value));
	}
	float getFloat(std::string key) {
		for (std::unordered_map<std::string, double>::iterator it = maps_double.begin(); it != maps_double.end(); ++it) {
			if (key.compare(it->first) == 0)
			{
				return it->second;
			}
		}
		return -1;
	}
	std::string toString() {
		//等待编写

	}
	void setJsonArray(std::string key, qJsonArray* jsonArray) {
		maps_JsonArray.insert(std::make_pair(key, jsonArray));
	}
	qJsonArray* getJsonArray(std::string key) {
		for (std::unordered_map<std::string, qJsonArray*>::iterator it = maps_JsonArray.begin(); it != maps_JsonArray.end(); ++it) {
			if (key.compare(it->first) == 0)
			{
				return it->second;
			}
		}
		return NULL;
	}
private:
	std::unordered_map<std::string, std::string> maps_string;
	std::unordered_map<std::string, double> maps_double; //整数 浮点数 全部放在这里 自动转换
	std::unordered_map<std::string, qJsonObject> maps_JsonObject;
	std::unordered_map<std::string, qJsonArray*> maps_JsonArray;
};





class obj
{
public:
	int type; // 0 str     1 digital   2  jsonobject  3 jsonarray
	std::string string;
	double digital;
	qJsonObject jsonObject;
	qJsonArray* jsonArray;

public:
	obj(int type, std::string string, double digital, qJsonObject jsonObject, qJsonArray* jsonArray) {
		this->type = type;
		this->string = string;
		this->digital = digital;
		this->jsonObject = jsonObject;
		this->jsonArray = jsonArray;
	}
private:

};

class qJsonArray
{
public:
	qJsonArray() {

	}
	void addJsonObject(qJsonObject jsonObject) {
		maps_obj.push_back(obj(0, "", -1, jsonObject, NULL));
	}
	qJsonObject getJsonObject(int idx) {
		return maps_obj[idx].jsonObject;
	}
	std::string getString(int idx) {
		return maps_obj[idx].string;
	}
	int getInt(int idx) {
		return maps_obj[idx].digital;
	}
	double getDouble(int idx) {
		return maps_obj[idx].digital;
	}
	double getFloat(int idx) {
		return maps_obj[idx].digital;
	}
	int size() {
		return maps_obj.size();
	}

	void addString(std::string str) {
		maps_obj.push_back(obj(0, str, -1, qJsonObject(), NULL)); //置入字符串
	}
	void addDigital(double value) {
		maps_obj.push_back(obj(1, "", value, qJsonObject(), NULL)); //置入字符串
	}
private:
	std::vector <obj> maps_obj;
};



class qJson
{
public:
	static qJsonObject parseJsonObject(std::string str); //, qJsonObject* obj = NULL
	static qJsonArray* parseJsonArray(std::string str);
};

