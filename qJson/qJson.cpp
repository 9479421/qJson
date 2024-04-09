#include "qJson.h"
#include <stdarg.h>
#include<vector>

std::string trim(const std::string& str) {
	// �ҵ���һ�����ǿո���ַ���λ��
	auto start = str.find_first_not_of(' ');
	// ����ַ���ȫ�ǿո񣬷���һ�����ַ���
	if (start == std::string::npos)
		return "";

	// �ҵ����һ�����ǿո���ַ���λ��
	auto end = str.find_last_not_of(' ');

	// ���شӿ�ʼ������λ�õ����ַ���
	return str.substr(start, end - start + 1);
}

int findFirstNotOf(const std::string& str, char ch...) {
	va_list chList;
	va_start(chList, ch);

	std::vector<char> chVector;


	int nArgVal = 0;
	for (;;)
	{
		nArgVal = va_arg(chList, char);
		if (nArgVal == 0)
		{
			break;
		}
		else {
			chVector.push_back(nArgVal);
		}

	}

	va_end(chList);

	for (int i = 0; i < str.size(); i++)
	{
		bool flag = false;
		for (int j = 0; j < chVector.size(); j++)
		{
			if (chVector[j] == str[i]) //���κ�һ����ȵģ���������
			{
				flag = true;
			}
		}
		if (flag == false)
		{
			return i;
		}
	}
	return -1;
}

bool isDigit(std::string str) {
	if (str[0] == '.' || str[str.size() - 1] == '.')
	{
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '.')) {
			return false;
		}
	}
	return true;
}


qJsonObject qJson::parseJsonObject(std::string str)
{
	qJsonObject* retObject = new qJsonObject();


	str = trim(str);
	int size = str.size();
	if (str[0] == '{' && str[size - 1] == '}') //�жϷ����ַ����淶
	{
		str = str.substr(1, size - 2); //ȥ������β������

		bool end = false;
		while (true)
		{
			if (end) //������json�ַ�����β
			{
				break;
			}

			////ǰ׺�ж��ŵ������ʹ���� ����Ҳ���Զ�pass��

			int idx = str.find(":"); //ֻҪkey�ﲻҪ����:��OK

			std::string front = str.substr(0, idx);
			int yin1 = front.find_first_of('"');
			int yin2 = front.find_last_of('"');
			std::string key = front.substr(yin1 + 1, yin2 - (yin1 + 1));

			std::string after = str.substr(idx + 1);
			int firstCharIdx = after.find_first_not_of(' ');
			char firstChar = after.at(firstCharIdx);
			if (firstChar == '"') //�ַ���
			{
				for (int i = firstCharIdx + 1; i < after.size(); i++)
				{
					if (after[i] == '"' && after[i - 1] != '\\')  //�ҵ�value�Ľ�β��
					{

						std::string value = after.substr(firstCharIdx + 1, i - (firstCharIdx + 1));
						////�ַ�����β��
						str = str.substr(idx + 1 + i + 1);  // + firstCharIdx

						//printf("key:%s value:%s\n", key.c_str(), value.c_str());
						//д��
						retObject->setString(key, value);


						if (str.find_first_not_of(' ') == -1) //������β��
						{
							end = true;
						}
						break;
					}
				}
			}
			else if (firstChar == '{') //jsonObject
			{
				//Ѱ��after�Ľ�β;
				int middle = 1, big = 0, shuangyinhao = 0;

				for (int i = firstCharIdx + 1; i < after.size(); i++) {


					if (after[i] == '"' && after[i - 1] != '\\')
					{
						shuangyinhao++;
					}

					if (shuangyinhao % 2 != 1)  //˵�����ڲ����ַ�����
					{
						if (after[i] == '{')
						{
							middle++;
						}
						if (after[i] == '}')
						{
							middle--;
						}
						if (after[i] == '[')
						{
							big++;
						}
						if (after[i] == ']')
						{
							big--;
						}
					}
					if (middle == 0 && shuangyinhao % 2 == 0 && big == 0) //˵������ȫ���������ˣ�������������
					{

						//��ȡ�����ַ��� {*****}
						std::string objStr = after.substr(firstCharIdx, i - firstCharIdx + 1);
						//�ضϣ�����������ı�
						str = str.substr(idx + 1 + firstCharIdx + i + 1);
						//д�� 
						retObject->setJsonObject(key, /*�ݹ�*/parseJsonObject(objStr/*�����ı�*/)); //ͬʱ���ö��󴫵�

						if (str.find_first_not_of(' ') == -1) //������β��
						{
							end = true;
						}
						break;
					}

				}
			}
			else if (firstChar == '[') //jsonObject
			{
				//Ѱ��after�Ľ�β]
				int middle = 0, big = 1, shuangyinhao = 0;
				for (int i = firstCharIdx + 1; i < after.size(); i++) {
					if (after[i] == '"' && after[i - 1] != '\\')
					{
						shuangyinhao++;
					}

					if (shuangyinhao % 2 != 1)  //˵�����ڲ����ַ�����
					{
						if (after[i] == '{')
						{
							middle++;
						}
						if (after[i] == '}')
						{
							middle--;
						}
						if (after[i] == '[')
						{
							big++;
						}
						if (after[i] == ']')
						{
							big--;
						}
					}
					if (middle == 0 && shuangyinhao % 2 == 0 && big == 0) //˵������ȫ���������ˣ�������������
					{

						//��ȡ�����ַ��� [*****]
						std::string arrStr = after.substr(firstCharIdx, i - firstCharIdx + 1);
						//�ضϣ�����������ı�
						str = str.substr(idx + 1 + firstCharIdx + i + 1);
						//д�� 
						retObject->setJsonArray(key, /*�ݹ�*/parseJsonArray(arrStr/*�����ı�*/)); //ͬʱ���ö��󴫵�

						if (str.find_first_not_of(' ') == -1) //������β��
						{
							end = true;
						}
						break;
					}

				}

			}
			else {  //˵�������ֻ���null
				std::string value;
				int endIdx = after.find(',');
				if (endIdx == -1) //˵���ǽ�β��
				{
					value = trim(after.substr(firstCharIdx));
					endIdx = after.size() - 1; //������������β
				}
				else {
					value = trim(after.substr(firstCharIdx, endIdx - firstCharIdx));
				}

				str = str.substr(idx + 1 + endIdx + 1);
				if (value.compare("NULL") == 0 || value.compare("null") == 0) //˵��ֵΪnull
				{
					//����������Ժ�����
					if (str.find_first_not_of(' ') == -1) //������β��
					{
						end = true;
					}




				}
				else {
					//�ж��Ƿ�Ϸ����֣�������ǣ�˵��json���Ϲ�
					if (isDigit(value))
					{
						retObject->setDouble(key, std::stod(value));
						if (str.find_first_not_of(' ') == -1) //������β��
						{
							end = true;
						}
					}
					else {
						//json���Ϲ棬ֱ���׳��쳣
						throw std::exception("format exception");
					}
				}

			}
		}
	}

	return *retObject;
}

qJsonArray* qJson::parseJsonArray(std::string str)
{
	qJsonArray* retJsonArray = new qJsonArray();


	str = trim(str);
	int size = str.size();
	if (str[0] == '[' && str[size - 1] == ']') //�жϷ����ַ����淶
	{
		str = str.substr(1, size - 2); //ȥ������β������


		//��ֵ����
		bool end = false;
		while (true)
		{
			if (end) //������json�ַ�����β
			{
				break;
			}

			int idx = findFirstNotOf(str, ' ', ',');  //��һ���ֵ�λ��
			//�ж����ַ������ͻ���Null������������
			if (str.at(idx) == '"')
			{
				for (size_t i = idx + 1; i < str.size(); i++)
				{
					if (str[i] == '"' && str[i - 1] != '\\')
					{
						std::string value = str.substr(idx + 1, i - (idx + 1));
						retJsonArray->addString(value);
						str = str.substr(i + 1);

						if (str.find_first_not_of(' ') == -1)
						{
							end = true;
						}
						break;
					}
				}
			}
			else if (str.at(idx) == '{') {
				std::string value;


				int middle = 1, big = 0, shuangyinhao = 0;
				for (size_t i = idx + 1; i < str.size(); i++)
				{
					if (str[i] == '"' && str[i - 1] != '\\')
					{
						shuangyinhao++;
					}

					if (shuangyinhao % 2 != 1)  //˵�����ڲ����ַ�����
					{
						if (str[i] == '{')
						{
							middle++;
						}
						if (str[i] == '}')
						{
							middle--;
						}
						if (str[i] == '[')
						{
							big++;
						}
						if (str[i] == ']')
						{
							big--;
						}
					}
					if (middle == 0 && shuangyinhao % 2 == 0 && big == 0) //˵������ȫ���������ˣ�������������
					{
						std::string jsonObjectStr = str.substr(idx, i - idx + 1);
						retJsonArray->addJsonObject(parseJsonObject(jsonObjectStr));

						str = str.substr(i + 1);

						if (str.find_first_not_of(' ') == -1)
						{
							end = true;
						}

						break;
					}
				}
			}
			else if (str.at(idx) == '[') {
				//������������

			}
			else {
				//Ϊnull��������
				std::string value;
				int endIdx = str.find(',', idx);
				if (endIdx == -1) //�ҵ��ַ�����β��
				{
					endIdx = str.size() - 1;
					value = trim(str.substr(idx, endIdx - idx + 1));
				}
				else {
					value = trim(str.substr(idx, endIdx - idx));
				}

				//��ȡֵ
				if (value.compare("NULL") == 0 || value.compare("null") == 0) //˵��ֵΪnull
				{
					//����������Ժ�����
					if (str.find_first_not_of(' ') == -1) //������β��
					{
						end = true;
					}


				}
				else {
					//�ж��Ƿ�Ϸ����֣�������ǣ�˵��json���Ϲ�
					if (isDigit(value))
					{
						retJsonArray->addDigital(std::stod(value));
						str = str.substr(endIdx + 1);
						if (str.find_first_not_of(' ') == -1) //������β��
						{
							end = true;
						}
					}
					else {
						//json���Ϲ棬ֱ���׳��쳣
						throw std::exception("format exception");
					}
				}
			}
		}

	}


	return retJsonArray;
}
