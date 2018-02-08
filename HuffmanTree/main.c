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
    char * * huffmanCode1;
    struct Node * HT;
    char * data;
    printf("请输入叶子结点的个数:");
    scanf("%d",&n);
    huffmanCode=(char * *)malloc(n*sizeof(char *));//分配n个字符编码的头指针向量
    HT=HuffmanCodings(n,huffmanCode);
    printf("编码的结果是:\n");
    for(i=0;i<n;i++){
        printf("%s\n",huffmanCode[i]);
    }
    printf("新方法的编码是:\n");
    huffmanCode1=(char * *)malloc(n*sizeof(char *));
    newCoding(HT,n,huffmanCode1);
    for(i=0;i<n;i++){
        printf("%s\n",huffmanCode1[i]);
    }
    data="111101100";
    printf("根据编码后的结果翻译报文:%s\n",data);
    printf("解码的结果是:");
    Huffmandecode(HT, data, n);
    printf("\n");
    free(huffmanCode);
    free(huffmanCode1);
    return 0;
}
