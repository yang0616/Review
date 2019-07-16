#include <iostream>
#include <string>
using namespace std;


int str_to_digit(string str, int flag)//10进制处理函数
{
	long long val = 0;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))//isdigit函数用来判断是否为数字字符，尽量使用库函数；
		{
			return 0;
		}

		val = val * 10 + str[i] - '0';
	}
	return val;
}

int str_to_oce(string str, int flag) //8进制处理函数
{
	long long val = 0;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (isdigit(str[i]) && str[i] != '8' && str[i] != '9')
		{
			val = val * 8 + str[i] - '0';
		}
		else
		{
			return 0;
		}
	}
	return val*flag;
}

int str_to_hex(string str, int flag) //16进制处理函数
{
	long long val = 0;
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (!isxdigit(str[i]))
		{
			return 0;
		}

		if (isdigit(str[i]))
		{
			val = val * 16 + str[i] - '0';
		}
		else
		{
			val = val * 16 + str[i] - 'A';
		}	
	}
	return val*flag;
}

int my_atoi(string str)
{
	if (str.size() == 0)
		return 0;

	int flag = 1;
	unsigned int i = 0;
	while (i < str.size() && isspace(str[i]))
	{
		i++;
	}
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	string new_str;
	if (str[i] == '0' && str[i+1] == 'x' || str[i+1] == 'X')
	{
		new_str = str.substr(i + 2, str.size() - i - 2);
		return str_to_hex(new_str, flag) ;
	}
	else if (str[0] == '0')
	{
		new_str = str.substr(i + 1, str.size() - i - 1);
		return str_to_oce(new_str, flag);
	}
	else
	{
		new_str = str.substr(i, str.size() - i);
		return str_to_digit(new_str, flag);
	}
}

int main()
{
	string str, constr = "y";
	while (constr[0] == 'y')
	{
		constr.clear();
		cout << "input str: ";

		getline(cin, str);
		int ans = my_atoi(str);
		
		cout << "out put: "<< ans << endl;
		cout << "continue? yes or no:";

		getline(cin, constr);
		str.clear();

		cout << "分割线************分割线" << endl;		
	}
	return 0;
}