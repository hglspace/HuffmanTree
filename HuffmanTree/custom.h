//
//  custom.h
//  HuffmanTree
//
//  Created by hgl on 2018/2/5.
//  Copyright © 2018年 hgl. All rights reserved.
//

#ifndef custom_h
#define custom_h
#define MAX_NODE_NUM 9
struct Node{
    int weight;
    char data;
    struct Node * parent;
    struct Node * lchild;
    struct Node * rchild;
};
struct Node * HuffmanCodings(int n,char * * huffmanCode);
void Huffmandecode(struct Node * HT,char * data,int n);
void newCoding(struct Node * HT,int n,char * * huffmanCode);
#endif /* custom_h */
