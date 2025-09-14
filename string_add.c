#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


// 突发奇想的小点子
// 既然数字字符常量的ASC2编码值是连续的
// 那显然可以将它与int直接进行加法
// 多位操作想必只需要简单的递归就能实现
// 虽然浪费很多空间和时间复杂度
// 但优势在于可以处理无限长的数
// 并且不需要对输入进行类型转换

// 目前只能加一位int，还没有想好怎么处理标准int

char testing_num_string[] = "123456789"; // 测试用例，兼顾了必须进位和过于巨大两个特征

/*
char string_add_by_place(char raw, int adding, int *carry) { // 按位进行加，将在主程序中递归使用
    int digit = raw - '0';
    digit += adding%10;
    *carry = (digit / 10);
    if (*carry) {
        digit -= 10;
    }
    return digit + '0';
}
*/

void string_add_main(char *num_string, int adding) {
    
    int len = strlen(num_string);
    int i = len - 1;
    /*
    num_string[i] = string_add_by_place(num_string[i], adding, &carry);
    i--;
    */
    while (adding > 0 && i >= 0) {
        /*
        int carry_num = carry;
        carry = 0;
        num_string[i] = string_add_by_place(num_string[i], carry_num, &carry);
        i--;
        */
       int digit = num_string[i] - '0';
       digit += adding;
       adding = digit / 10;
       digit %= 10;
       num_string[i] = digit + '0';
       i--;
    }
    // 如果最高位需要进位则应该进行内存动态分配并进行最后一次进位
}

int main(void) {
    string_add_main(testing_num_string, 34);
    printf("%s", testing_num_string);
    system("pause");
    return 0;
}