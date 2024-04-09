
#include"qJson.h"


int main() {


	std::string a = R"({"name":"222","tall":184,"data":{"age":{"sex":"18","age":22},"father":"shuaige"},"naocan": null,"age":18.2 ,"shabi": null})";
	qJsonObject json = qJson::parseJsonObject(a);
	printf("getString:%s\n", json.getString("name").c_str());
	printf("getString:%s\n", json.getJsonObject("data").getJsonObject("age").getString("sex").c_str());
	printf("getInt:%d\n", json.getJsonObject("data").getJsonObject("age").getInt("age"));
	printf("getString:%s\n", json.getJsonObject("data").getString("father").c_str());
	printf("shabi getString:%s\n", json.getString("shabi").c_str());

	printf("getDouble:%f\n", json.getDouble("age"));
	printf("getDouble:%f\n", json.getDouble("tall"));
	printf("getInt:%d\n", json.getInt("age"));


	std::string b = R"({"data":[{"age":18 },{"name":"wangshuaibi"}],"grade":"banianji"})";
	qJsonObject json1 = qJson::parseJsonObject(b);
	printf("jsonArray Size:%d\n", json1.getJsonArray("data")->size());
	printf("jsonArray %d\n", json1.getJsonArray("data")->getJsonObject(0).getInt("age"));
	printf("jsonArray %s\n", json1.getJsonArray("data")->getJsonObject(1).getString("name").c_str());


	std::string c = R"({"data":[{"age":18},{"name":"wangshuaibi"}],"array":["3213","11111","432432",999 ,100,{"age":120},{"name":"chenhui"}],"grade":"banianji"})";
	qJsonObject json2 = qJson::parseJsonObject(c);
	printf("jsonArray Size:%d\n", json2.getJsonArray("array")->size());
	printf("jsonArray %s\n", json2.getJsonArray("array")->getString(0).c_str());
	printf("jsonArray %s\n", json2.getJsonArray("array")->getString(1).c_str());
	printf("jsonArray %s\n", json2.getJsonArray("array")->getString(2).c_str());

	printf("jsonArray %d\n", json2.getJsonArray("array")->getInt(3));
	printf("jsonArray %d\n", json2.getJsonArray("array")->getInt(4));

	printf("jsonArray %d\n", json2.getJsonArray("array")->getJsonObject(5).getInt("age"));
	printf("jsonArray %s\n", json2.getJsonArray("array")->getJsonObject(6).getString("name").c_str());

	printf("jsonArray %s\n", json2.getJsonArray("array")->toString().c_str());

	printf("json2 ToString() %s \n", json2.toString().c_str());

	qJsonObject jsonObject;
	jsonObject.setInt("age", 19);
	jsonObject.setString("name", "È¨¸ç");
	printf("toString: %s\n", jsonObject.toString().c_str());

	qJsonArray jsonArray;
	jsonArray.addJsonObject(jsonObject);
	jsonArray.addDigital(19);
	jsonArray.addString("name");
	printf("toString: %s\n", jsonArray.toString().c_str());

	system("pause");

	return -1;
}

