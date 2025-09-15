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


char testing_num_string[] = "89"; // 测试用例，兼顾了必须进位和过于巨大两个特征

/*
// 如果把这个操作做成一个函数的话无法在循环中正常传递参数，所以将算法直接写进循环
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

void string_add_main(char **num_string_ptr, int adding) { /// 传入指针，方便后续交换
    
    char *num_string = *num_string_ptr; // 对指针解引用
    int len = strlen(num_string); // 获取数组长度
    int i = len - 1; // 索引从0开始，所以这里-1
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
    int digit = num_string[i] - '0'; // 当前位上数字字符的数值
    digit += adding; // 加
    adding = digit / 10; // 需要进位的值
    digit %= 10; // 这位上的当前值
    num_string[i] = digit + '0'; // 把它变成char后传入数组
    i--;
    }
    // 如果最高位需要进位则应该进行内存动态分配并进行最后一次进位
    if (i <= 0) {
        int new_len = len + 1;
        char *new_string = (char*)malloc((new_len + 1) * sizeof(char)); // 定义新指针，防止变量遮蔽
        new_string[0] = adding + '0';
        strcpy(new_string + 1, num_string);
        new_string[new_len] = '\0';
        *num_string_ptr = new_string; // 指针交换
    }
}


int main(void) {
    char *testing_num_string = strdup("89"); // 动态分配初始值
    if (testing_num_string == NULL) {
        perror("NULL");
        return 1;
    }
    string_add_main(&testing_num_string, 334); // 传入一个指针
    printf("%s\n", testing_num_string);
    int len = strlen(testing_num_string) - 1;
    for (len; len >= 0; len--) {
        printf("%d,%d\n",len, testing_num_string[len]);
    };
    free(testing_num_string);
    system("pause");
    return 0;
}