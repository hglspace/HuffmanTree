//
//  main.c
//  HuffmanTree
//
//  Created by hgl on 2018/2/5.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include "custom.h"
#include <stdlib.h>
int main(int argc, const char * argv[]) {

    int n,i;
    char * * huffmanCode;
    printf("请输入叶子结点的个数:");
    scanf("%d",&n);
    huffmanCode=(char * *)malloc(n*sizeof(char *));//分配n个字符编码的头指针向量
    HuffmanCodings(n,huffmanCode);
    for(i=0;i<n;i++){
        printf("%s\n",huffmanCode[i]);
    }
    return 0;
}
