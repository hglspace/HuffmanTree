//
//  Huffman.c
//  HuffmanTree
//
//  Created by hgl on 2018/2/5.
//  Copyright © 2018年 hgl. All rights reserved.
//

#include <stdio.h>
#include "custom.h"
#include <stdlib.h>
#include <string.h>
#define  MAX_NUM 9999
void HuffmanCodings(int n,char * * huffmanCode){
    int i,m=2*n-1,start;
    char * cd=(char *)malloc(n*sizeof(char));
    struct Node * HT=(struct Node *)malloc((m)*(sizeof(struct Node)));//开辟内存，存放结点
    struct Node * p,* c,* c1;
    int * s1=(int *)malloc(sizeof(int)),* s2=(int *)malloc(sizeof(int));//s1 和 s2 分别是权重最小的结点的位置和权重次小的结点的位置
    void Select(struct Node * HT,int n,int * s1,int * s2);//求出权重最小和次小的结点的位置
    for(p=HT,i=0;i<n;i++,p=p+1){
        printf("请输入第%d个叶子结点的字符:",i+1);
        scanf(" %c",&p->data);
        printf("请输入第%d个叶子结点的权重:",i+1);
        scanf("%d",&p->weight);
        p->parent=NULL;
        p->lchild=NULL;
        p->rchild=NULL;
    }
    for(;i<m;i++,p=p+1){//其他的结点也初始化
        p->weight=0;
        p->data='\0';
        p->parent=NULL;
        p->lchild=NULL;
        p->rchild=NULL;
    }
    for(i=n;i<m;i++){//建Huffman树 i不断的变大，相当于集合F不断的变大，变相的把新的二叉树放到F中了
        Select(HT,i,s1,s2);
        (HT+*s1)->parent=(HT+i);
        (HT+*s2)->parent=(HT+i);
        (HT+i)->lchild=(HT+*s1);//以权重小的放到左子树，权重大的放到右子树，当然也可以按照其他规则
        (HT+i)->rchild=(HT+*s2);
        (HT+i)->weight=(HT+*s1)->weight+(HT+*s2)->weight;
    }
    
    //从叶子到根逆向求每个字符的Huffman编码
    cd[n-1]='\0';
    for(i=0;i<n;i++){
        start=n-1;
        c1=(HT+i);
        for(c=(HT+i)->parent;c!=NULL;c=c->parent){
            if(c->lchild==c1){
                cd[--start]='0';
            }else{
                cd[--start]='1';
            }
            c1=c;
        }
        huffmanCode[i]=(char *)malloc((n-start)*sizeof(char));
        strcpy(huffmanCode[i], &cd[start]);
    }
}

/*
  选择两棵根结点的权值最小的和次小的树，按照Huffman算法，是要删除选择过的结点，但是可以额外加一个条件判断，从而不会选择它，相当于删除了，就是p->paren==null
 */
void Select(struct Node * HT,int n,int * s1,int * s2){
    struct Node * p;
    int i,tmp1=MAX_NUM,tmp2=0;
    *s1=0;
    for(p=HT,i=0;i<n;i++,p=p+1){
        //条件是：根结点的权值最小，并且parent的值是null
        if(p->parent==NULL && p->weight<tmp1){
            tmp2=tmp1;
            tmp1=p->weight;
            *s2=*s1;
            *s1=i;
        }else if(p->parent==NULL && p->weight<tmp2){
            tmp2=p->weight;
            *s2=i;
        }
    }
}

