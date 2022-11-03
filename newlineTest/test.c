/**
 * 功能：测试续行符 \ 和 “
 */

#include <stdio.h>

#define TEST_STR1  "123456"
#define TEST_STR2  "123" \
					"456"   //宏定义使用续行符，不能省略中间的两个双引号，否则出错
#define MYPRINTF(x) printf("%s\n", \
							x);  //宏定义使用续行符

int main(void)
{
	char *str1 = "hello world!";
	char *str2 = "hello \
	world!";                 //不推荐使用此种方式，中间会多出空格符
	char *str3 = "hello " \
				"world!";    //字符串使用续行符
	char *str4 = "hello "
				"world";	
	char *str5 = "hello ""world";	
	printf("str1=%s\nstr2=%s\nstr3=%s\nstr4=%s\nstr5=%s\n", str1, str2, str3, str4, str5);

	printf("TEST_STR1=%s\nTEST_STR2=%s\n", TEST_STR1, TEST_STR2);
	
	printf("1. parameter is too long, \
			this is newline\n");
	printf("2. parameter is too long, "
            "this is newline\n");
	printf("3. parameter is too long, " \
            "this is newline\n");
	printf("\;\n");
	MYPRINTF("bye bye...");
}
