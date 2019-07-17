## my_atoi ##

函数介绍： atoi() 函数会扫描参数 str 字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），直到遇上数字或正负符号才开始做转换，而再遇到非数字或字符串结束时('\0')才结束转换，并将结果返回。最后返回转换后的整型数；如果 str 不能转换成 int 或者 str 为空字符串，那么将返回 0。

## 代码实现 ##
    #include <iostream>
    #include <string>
    #include <map>
    #include <utility>
    using namespace std;
    class Secure
    {
    public:
    	Secure() //初始化
    	{
    		warn = 0;
    		note = "";
    		valma.insert(make_pair('I', 1));
    		valma.insert(make_pair('l', 1));
    		valma.insert(make_pair('z', 2));
    		valma.insert(make_pair('Z', 2));
    		valma.insert(make_pair('o', 0));
    		valma.insert(make_pair('O', 0));			
    	}
     
    	int find(char ch)
    	{
    		if (valma.end() == valma.find(ch))
    		{
    			return -1;
    		}
    		warn++;
    		note += ch;
    		return valma.find(ch)->second;
    	}
    		
    	void showRecord()
    	{
    		if (warn == 0)
    			return;
     
    		cout << "warn:" << warn << endl;
    		for (unsigned int i = 0; i < note.size(); i++)
    		{
    			cout << valma.find(note[i])->second << " - " << note[i] << endl;
    		}
    	}
     
    	void clear()
    	{
    		warn = 0;
    		note = "";
    	}
    	
    private:
    	int warn;
    	string note;
    	map<char, int> valma;
    };
     
    class Transverter
    {
    public:
    	void my_atoi()
    	{
    		Secure secure;
    		string str, constr = "y";
    		while (constr[0] == 'y')
    		{
    			constr.clear();
    			cout << "input str: ";
     
    			getline(cin, str);
    			int ans = trans(str, secure);
     
    			cout << "out put: " << ans << endl;
    			secure.showRecord();
    			cout << "continue? yes or no:";
     
    			getline(cin, constr);
    			str.clear();
    			secure.clear();
    			cout << "-------cut------cut------" << endl;
    		}
    	}
     
    private:
     
    	bool find(Secure &secure, char ch)
    	{
    		string ostr = "O0o";
    		if (ostr.find(ch) == ostr.npos) //去除第一个参数不为0、O、o、三种情况
    			return false;
    		if (ch != '0')
    			secure.find(ch);
    		return true;
    	}
     
    	int checkVal(long long val, int flag)
    	{
    		if (val >= INT_MAX)
    		{
    			if (flag == 1)
    				return INT_MAX;
    			return INT_MIN;
    		}
    		else
    		{
    			return val*flag;
    		}
    	}
     
    	int str_to_digit(string str, int flag, Secure &secure)//10进制处理函数
    	{
    		long long val = 0;
    		for (unsigned int i = 0; i < str.size() && val != INT_MAX; i++)
    		{
    			if (str[i] == '.' && isdigit(str[i + 1]))
    			{
    				val = (str[i + 1] - '0' < 5 ? val : val + 1);
    				return checkVal(val, flag);
    			}
     
    			if (!isdigit(str[i]))//isdigit函数用来判断是否为数字字符，尽量使用库函数；
    			{
    				int tmp = secure.find(str[i]);
    				if (tmp == -1)
    					return 0;
    				str[i] = '0' + tmp;
    			}
     
    			val = checkVal(val * 10 + str[i] - '0', 1);
    		}
    		return checkVal(val, flag);
    	}
     
    	int str_to_oce(string str, int flag, Secure &secure) //8进制处理函数
    	{
    		long long val = 0;
    		for (unsigned int i = 0; i < str.size() && val != INT_MAX; i++)
    		{
    			if (str[i] == '8' || str[i] == '9')
    				return 0;
     
    			if (!isdigit(str[i]))
    			{
    				int tmp = secure.find(str[i]);
    				if (tmp == -1)
    					return 0;
    				str[i] = '0' + tmp;
    			}
     
    			val = checkVal(val * 8 + str[i] - '0', 1);
    		}
    		return checkVal(val, flag);
    	}
     
    	int str_to_hex(string str, int flag, Secure &secure) //16进制处理函数
    	{
    		long long val = 0;
    		for (unsigned int i = 0; i < str.size() && val != INT_MAX; i++)
    		{
    			if (!isxdigit(str[i]))
    			{
    				int tmp = secure.find(str[i]);
    				if (tmp == -1)
    					return 0;
    				val = checkVal(val * 16 + tmp, 1);
    			}
    			else if (isdigit(str[i]))
    				val = checkVal(val * 16 + str[i] - '0', 1);
    			else
    				val = checkVal(val * 16 + str[i] - 'A', 1);
    		}
    		return checkVal(val, flag);
    	}
     
    	int trans(string str, Secure &secure)
    	{
    		if (str.size() == 0)
    			return 0;
     
    		unsigned int i = 0;
    		int flag = 1, ans = 0;
     
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
    		if (find(secure, str[i]) && str[i + 1] == 'x' || str[i + 1] == 'X')
    		{
    			new_str = str.substr(i + 2, str.size() - i - 2);
    			return str_to_hex(new_str, flag, secure);
    		}
    		secure.clear();
     
    		if (find(secure, str[i]))
    		{
    			new_str = str.substr(i + 1, str.size() - i - 1);
    			return str_to_oce(new_str, flag, secure);
    		}
    		else
    		{
    			new_str = str.substr(i, str.size() - i);
    			return str_to_digit(new_str, flag, secure);
    		}
     
    	}
    };
     
    int main()
    {
    	Transverter transverter;
    	transverter.my_atoi();
    	return 0;
    }
