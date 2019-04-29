## map表的自定义排序 ##
头文件：

    #include <iostream>
    #include <map>
    #include <time.h>
    #include <functional>
    #include <vector>
    #include <algorithm>
    using namespace std;
（一）按照key值进行排序

1.1升序

    void lessToKey()
	{
	    srand((unsigned)time(NULL)); //产生一个随机数
	    map<int, int> ma; //map表的第三个参数默认为less<int>,所以默认是按照key升序
	   	int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			int a = rand() * rand() % 5;
			int b = rand() * rand() % 8;
			ma.insert(make_pair(a, b));
		}

		for (auto it = ma.begin(); it != ma.end(); it++)
		{
			cout << "key: " << it->first << " val: " << it->second << endl;
		}	
	}	

1.2降序
   
    void greaterToKey()
	{
		srand((unsigned)time(NULL)); //产生一个随机数
		map<int, int, greater<int> > ma; //如果想要按照key值降序排列，则在第三个参数显示的调用greater降序函数,剩下的操作和升序一样；
		int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			int a = rand() * rand() % 5;
			int b = rand() * rand() % 8;
			ma.insert(make_pair(a, b));
		}

		for (auto it = ma.begin(); it != ma.end(); it++)
		{
			cout << "key: " << it->first << " val: " << it->second << endl;
		}
	}

1.3自定义结构并排序

    //对自定义类型，在map中自定义排序规则1【自定义一个比较规则的类，然后重载()】
	typedef struct mystruct //自定义键类型
	{
		int i;
		int j;
	}ms;

	class cmp1  //自定义比较规则,定义一个新的比较规则类型，重载 () 符号；
	{
	public:
		bool operator() (ms const& a, ms const& b)const 
		{
			return a.i < b.i;
		}
	};

	void  myType1()
	{
		srand((unsigned)time(NULL)); //产生一个随机数

		map<ms, int, cmp1> ma; //把第三个参数修改成自定义比较规则的类型
		int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			ms tmp;
			tmp.i = rand() * rand() % 5;
			tmp.j = rand() * rand() % 8;
			ma.insert(make_pair(tmp, i));
		}

		for (auto it = ma.begin(); it != ma.end(); it++)
		{
			cout << "i: " << it->first.i << " j: " << it->first.j << " val: " << it->second << endl;
		}
	}

    //对自定义类型，在multima中自定义排序规则2【在结构体中重载 >】
	typedef struct mystruct
	{
		int i;
		int j;
		bool operator < (struct mystruct const& a)const //注意，这里不要去重载 “>”，只重载“<”如果需要改变，则去改变判断条件；
		{
			return i > a.i;
		}
	}ms;

	void  myType2()
	{
		srand((unsigned)time(NULL)); //产生一个随机数

		map<ms, int> ma; //这种方法不需要写第三个参数
		int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			ms tmp;
			tmp.i = rand() * rand() % 5;
			tmp.j = rand() * rand() % 8;
			ma.insert(make_pair(tmp, i));
		}

		for (auto it = ma.begin(); it != ma.end(); it++)
		{
			cout << "i: " << it->first.i << " j: "<< it->first.j << " val: " << it->second << endl;
		}
	}

（二）按照val值进行排序 
 
2.1升序

    //按照value的值升序排序【将数据在可以使用sort的容器中排序，这里用vector举例】
	static bool cmp2(pair<int, int> const a, pair<int, int> const b)
	{
		return a.second > b.second;
	}

	void lessToValue()
	{
		srand((unsigned)time(NULL)); //产生一个随机数

		vector<pair<int, int>> ve;
		int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			int a = rand() * rand() % 5;
			int b = rand() * rand() % 8;
			ve.push_back(make_pair(a, b));
		}

		sort(ve.begin(), ve.end(), cmp2);
		for (auto it = ve.begin(); it != ve.end(); it++)
		{
			cout << "key: " << it->first << " val: " << it->second << endl;
		}
	}

2.2降序

    //按照value的值降序排序
	static bool cmp3(pair<int, int>const a, pair<int, int>const b)
	{
		return a.second < b.second;
	}

	void greaterToValue()
	{
		srand((unsigned)time(NULL)); //产生一个随机数

		vector<pair<int, int>> ve;
		int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			int a = rand() * rand() % 5;
			int b = rand() * rand() % 8;
			ve.push_back(make_pair(a, b));
		}

		cout << "排序前" << endl;
		for (auto it = ve.begin(); it != ve.end(); it++)
		{
			cout << "key: " << it->first << " val: " << it->second << endl;
		}

		sort(ve.begin(), ve.end(), cmp3); 


		cout << "排序后" << endl;
		for (auto it = ve.begin(); it != ve.end(); it++)
		{
			cout << "key: " << it->first << " val: " << it->second << endl;
		}
	}

2.3自定义结构并排序

    //自定义value类型，自定义排序规则；
	typedef struct myStruct //自定义结构
	{
		int i;
		int j;
	}ms;

	static	bool cmp(pair<int, ms> const a, pair<int, ms> const b) //按照每个元素中ms结构体中i的大小进行降序
	{
		return a.second.i > b.second.i;
	}

	void myToValue()
	{
		srand((unsigned)time(NULL)); //产生一个随机数

		vector<pair<int, ms>> ve;
		int len; cin >> len;
		for (int i = 0; i < len; i++)
		{
			ms tmp;
			tmp.i = rand() * rand() % 5;
			tmp.j = rand() * rand() % 8;
			ve.push_back(make_pair(i, tmp));
		}

		cout << "排序前" << endl;
		for (auto it = ve.begin(); it != ve.end(); it++)
		{
			cout << "key: " << it->first << " i: " << it->second.i << " j: " << it->second.j << endl;
		}

		sort(ve.begin(), ve.end(), cmp); //将第三个参数设置为降序函数。即：greater<type>()

		cout << "排序后" << endl;
		for (auto it = ve.begin(); it != ve.end(); it++)
		{
			cout << "key: " << it->first << " i: " << it->second.i << " j: " << it->second.j << endl;
		}
	}