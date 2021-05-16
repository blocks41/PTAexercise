#include <stdio.h>

int main(void)
{
    char str[10]; 
    printf("请输入字符串：");
    scanf_s("%s", str ,10); 
    printf("输出结果：%s\n", str);
    return 0;
}