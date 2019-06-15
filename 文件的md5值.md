## 文件的md5值 ##
（一）函数介绍

 打开/usr/include/openssl/md5.h这个文件我们可以看到一些函数：
     
    // 初始化 MD5 Contex, 成功返回1,失败返回0
     
    1、int MD5_Init(MD5_CTX *c);
     
    // 循环调用此函数,可以将不同的数据加在一起计算MD5,成功返回1,失败返回0
     
    2、int MD5_Update(MD5_CTX *c, const void *data, size_t len);
     
    // 输出MD5结果数据,成功返回1,失败返回0
     
    3、int MD5_Final(unsigned char *md, MD5_CTX *c);
     
    // MD5_Init,MD5_Update,MD5_Final三个函数的组合,直接计算出MD5的值
     
    4、 unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md);
     
    // 内部函数,不需要调用
     
    5、void MD5_Transform(MD5_CTX *c, const unsigned char *b);
（二）代码实现
    #include <openssl/md5.h>
    #include <stdio.h>
    #include <string.h>
    #include <iostream>
    #include <iomanip>
    using namespace std;
     
    int main()
    {
    MD5_CTX ctx;
    unsigned char outmd[16];
    char buffer[1024];
    char filename[32];
    FILE* fp = NULL;
    int len = 0, i = 0;
     
    memset(outmd, 0, sizeof(outmd));
    memset(filename, 0, sizeof(filename));
    memset(buffer, 0, sizeof(buffer));
     
    cout << "please enter file name:";
    cin >> filename;
     
    if((fp = fopen(filename, "rb")) == NULL)
    {
    cout << "file open error!"<< endl;
    return 0;
    }
     
    MD5_Init(&ctx);
    while((len = fread(buffer, 1, 1024, fp)) > 0 )
    {
    MD5_Update(&ctx, buffer, len);
    memset(buffer, 0, sizeof(buffer));
    }
     
    MD5_Final(outmd, &ctx);
     
    for(i = 0; i < 16; i++)
    {
    printf("%02X", outmd[i]);
    }
    cout << endl;
    return 0;
     
    }
【编译命令为g++ - o main main.cpp -lssl加上库名。】