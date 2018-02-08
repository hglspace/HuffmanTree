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
struct Node * HuffmanCodings(int n,char * * huffmanCode){
    int i,m=2*n-1,start;
    char * cd=(char *)malloc(n*sizeof(char));
    struct Node * HT=(struct Node *)malloc((m)*(sizeof(struct Node)));//开辟连续内存，存放结点
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
    for(i=n;i<m;i++){//建Huffman树 i不断的变大，相当于集合F不断的变大，变相的把新的二叉树放到F中了 第m-1个结点是树根
        Select(HT,i,s1,s2);
        (HT+*s1)->parent=(HT+i);
        (HT+*s2)->parent=(HT+i);
        (HT+i)->lchild=(HT+*s1);//以权重小的放到左子树，权重大的放到右子树，当然也可以按照其他规则
        (HT+i)->rchild=(HT+*s2);
        (HT+i)->weight=(HT+*s1)->weight+(HT+*s2)->weight;
    }
    
    //从叶子到根逆向求每个字符的Huffman编码 是从叶子到根，当然也可以从根到叶子，遍历的范围是1-n，也就是叶子结点
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
    free(cd);
    free(s1);
    free(s2);
    return HT;
}

/*
  选择两棵根结点的权值最小的和次小的树，按照Huffman算法，是要删除选择过的结点，但是可以额外加一个条件判断，从而不会选择它，相当于删除了，就是p->parent==null
  一次遍历选出最小 次小的两个值
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

/*
  根据字符串解码 从根结点根据字符串进行解码,找到叶子结点后就停止，然后再从根结点开始
 */
void Huffmandecode(struct Node * HT,char * data,int n){
    int i,m=2*n-1;
    struct Node * p=(HT+m-1);//p的值为根结点(最后一个为根结点，上面的方法生成Huffman树时，最后一个结点就是树根)
    for(i=0;*(data+i)!='\0';i++){
        if(*(data+i)=='0'){//向左
            p=p->lchild;
            if(p->rchild==NULL && p->lchild==NULL){//说明是叶子结点
                printf("%c\t",p->data);
                p=(HT+m-1);
            }
        }else{//向右
            p=p->rchild;
            if(p->rchild==NULL && p->lchild==NULL){
                printf("%c\t",p->data);
                p=(HT+m-1);
            }
        }
    }
}

//无栈非递归遍历Huffman树，求Huffman编码,从根到叶子
void newCoding(struct Node * HT,int n,char * * huffmanCode){
    char * cd=(char *)malloc(n*sizeof(char));
    int m=2*n-1,i,count=0;
    struct Node * p=(HT+m-1);//p的值为根结点(最后一个为根结点，上面的方法生成Huffman树时，最后一个结点就是树根)
    for(i=0;i<m;i++) (HT+i)->weight=0;
    i=0;
    while(p>=HT && p<=HT+m-1){
        if(p->weight==0){//值是0，代表刚开始访问结点
            p->weight=1;//把它的值置为1，开始访问左孩子
            if(p->lchild!=NULL){
                p=p->lchild;
                cd[count++]='0';
            }else if(p->rchild==NULL){//意思是上面的判断不成立，说明左孩子是null，到这右孩子也是null，说明它是个叶子结点,在它判断左孩子为null时要加上对右孩子的判断
                huffmanCode[i]=(char *)malloc((count+1)*sizeof(char));
                cd[count]='\0';
                strcpy(huffmanCode[i], cd);
                i++;
            }
        }else if(p->weight==1){//值是1，代表已经访问完左孩子了,开始访问右孩子
            p->weight=2;//把它的值置为2，开始访问右孩子
            if(p->rchild!=NULL){
                p=p->rchild;
                cd[count++]='1';
            }
        }else{//值是2，代表以后再回到这个结点时，需要回退到父结点，因为左右孩子都访问了
            p->weight=0;
            p=p->parent;
            --count;
        }
    }
    free(cd);
}
