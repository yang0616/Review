## 回溯法--n后问题 ##
&nbsp; &nbsp; 在 n乘n 格棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之同一行或者同一列或者同一斜线上的棋子。n 后问题等价于在 n * n 格棋盘上放置 n 个皇后，任何两个皇后不放在同一行或者同一列或者同一斜线上；
    
    /*回溯法*/
    bool place1(int* X, int k)
    {
    	bool res = true;
    	for (int i = 0; i < k; i++)
    	{
    		if (X[i] == X[k] || abs(k - i) == abs(X[k] - X[i])) //判断是否在同一对角线，同一列
    		{
    			res = false;
    		}
    	}
    	return res;
    }
    
    void print1(int* X, int n) //一位数组X中，X[i]表示皇后i放在棋盘的第i行第X[i]列上
    {
    	for (int i = 0; i < n; i++)
    	{
    		for (int j = 0; j < n; j++)
    		{
    			if (X[i] == j)
    				cout << " Q ";
    			else
    				cout << " # ";
    		}
    		cout << endl;
    	}
    	cout << "cut-------cut---------cut" << endl;
    }
    
    void backTrack1(int* X, int k, int n)
    {
    	if (k >= n)
    		print1(X, n);
    	else
    	{
    		for (int j = 0; j < n; j++)
    		{
    			X[k] = j;
    			if (place1(X, k))//剪枝函数
    			{
    				backTrack1(X, k+1, n);
    			}
    		}
    	}
    }
    
    /*迭代回溯法--非递归*/
    bool place2(int* X, int k)
    {
    	bool res = true;
    	for (int i = 1; i < k; i++)
    	{
    		if (X[i] == X[k] || abs(k - i) == abs(X[k] - X[i])) //判断是否在同一对角线，同一列
    		{
    			res = false;
    		}
    	}
    	return res;
    }
    
    void print2(int* X, int n) //一位数组X中，X[i]表示皇后i放在棋盘的第i行第X[i]列上
    {
    	for (int i = 1; i <= n; i++)
    	{
    		for (int j = 1; j <= n; j++)
    		{
    			if (X[i] == j)
    				cout << " Q ";
    			else
    				cout << " # ";
    		}
    		cout << endl;
    	}
    	cout << "cut-------cut---------cut" << endl;
    }
    
    void backTrack2(int* X, int n)
    {
    	X[1] = 0;
    	int k = 1;
    	while (k > 0)
    	{
    		X[k] += 1; //初始化
    
    		while ( (X[k] <= n) && (!place2(X, k)) )  X[k] += 1;//当前位置不合法的时候，直接往后走
    
    		if (X[k] <= n)//找到了合适的位置
    		{
    			if (k == n)//到达最后一层，输出一个方案
    				print2(X, n);
    			else
    			{
    				k++;
    				X[k] = 0; //开始检测孩子节点
    			}
    		}
    		else  k--;//没有找到合适的位置，回退到上层祖先
    	}
    }
    
    int main()
    {
    	const int n = 4;
    	int X[n] = {0};
    	cout << "backTrack1:" << endl;
    	backTrack1(X, 0, n);
    	int Y[n + 1] = {0};
    	cout << "backTrack2:" << endl;
    	backTrack2(Y,n);
    	return 0;
    }
    