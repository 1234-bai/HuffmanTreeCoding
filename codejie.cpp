/************codejie.cpp**************/
//建树，建表。字符串转换


#include "struct.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<share.h>
#include <QString>

//下面三个函数为建树(编码)函数
HuffmanCode initHuffmanCode(int n)
{
    HuffmanCode HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
    if (!HC) exit(0);
    return HC;
}

void Select(HuffmanTree HT,int n,unsigned int *s1,unsigned int *s2)
{
    int mininx = 0, minweight = 100000000, min2inx = 0, min2weight = 100000000;
    for (int i = 1; i <= n; ++i) {
        if (HT[i].parent != 0) continue;
        int weight = HT[i].weight;
        if (weight > min2weight) continue;
        if (weight < minweight) {
            min2inx = mininx, min2weight = minweight;
            mininx = i, minweight = weight;
        }
        else min2inx = i, min2weight = weight;
    }
    *s1 = mininx; *s2 = min2inx;
}

HuffmanTree HuffmanCoding(HuffmanCode HC, alph w[], int n)
{
    int m;
    if (n < 1) return NULL;
    m = 2 * n - 1;
    HuffmanTree HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
    if (!HT) exit(0);
    int i;
    HuffmanTree p = HT+1;
    for ( i = 1; i <= n; ++i,++p, ++w) {
        p->weight = w->fre;
        p->parent = p->lchild = p->rchild = 0;
    }
    if(n == 1){
        HC[1] = (char*)("1");
        return HT;
    }
    for (; i <= m; ++i, ++p) {
        p->lchild = p->parent = p->rchild = p->weight = 0;
    }
    for (i = n + 1; i <= m; ++i) {
        unsigned int s1, s2;
        Select(HT, i-1,&s1,&s2);
        HT[s1].parent = i; HT[s2].parent = i;
        HT[i].lchild = s1; HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    char *cd = (char*)malloc(n * sizeof(char));
    if (!cd) exit(0);
    cd[n - 1] = '\0';
    for (int i = 1; i <= n; ++i) {
        int start = n - 1;
        for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
            if (HT[f].lchild == (unsigned)c) cd[--start] = '0';
            else cd[--start] = '1';
        }
        HC[i] = (char*)malloc((n - start) * sizeof(char));
        if (!HC[i]) exit(0);
        strcpy_s(HC[i], n - start, &cd[start]);
    }
    free(cd);
    return HT;
}

//下面两个为解码函数
//字符串变字符串（01字符串变字母字符串，返回解码后的字母串）
QString Huffman_decodeStr(char s[],int lens, HuffmanTree HT,int n,alph a[]) {
    QString str;
    int p = 2*n-1;
    int i = 0;
    for (i = 0; i < lens; i++)
    {
        if (s[i] == '0') {
            if (HT[p].lchild != 0){
                p = HT[p].lchild;
            }
        }
        else if (s[i] == '1'){
            if (HT[p].rchild != 0){
                p = HT[p].rchild;
            }
        }
        if (HT[p].lchild == 0 && HT[p].rchild == 0)
        {
           // printf("%c", a[p-1].letter);
            str+=a[p-1].letter;
            p = 2*n-1;
        }
    }
    return str;
}

/*
//字符串变文件（01字符串变成储存字母串的文本文件，返回解码后的字母串）
QString Huffman_decodeFILE(char str01[], const char *tofilename,HuffmanTree HT, int n, alph a[]) {
    QString str;
    int p = 2 * n - 1;
    char ch;
    FILE  *ftop;
    if ((ftop = fopen( tofilename, "w")) == NULL) {
        printf("要写入的文件出问题");
        exit(0);
    }
        while ((ch = *(str01++)) != '\0') {
            if (ch == '0')
            {
                if (HT[p].lchild != 0)
                {
                    p = HT[p].lchild;
                }
            }
            else if (ch == '1')
            {
                if (HT[p].rchild != 0)
                {
                    p = HT[p].rchild;
                }
            }
           // else if (ch == ' ' || ch == '\n')
            //    if (ftop != 0) fputc(ch, ftop);
            if (HT[p].lchild == 0 && HT[p].rchild == 0)
            {
                //printf("%c", a[p - 1].letter);
                if (ftop == 0) exit(0);
                str+=a[p-1].letter;
                fputc(a[p - 1].letter, ftop);
                p = 2 * n - 1;
            }
        }
        fclose(ftop);
    return str;
}


//文件变文件（字母文件变成01文件，Qt中返回解码后的字符串）
QString Huffman_decodeFILE(const char *filename, const char *tofilename,HuffmanTree HT, int n, alph a[]) {
    QString str;
    int p = 2 * n - 1;
    char ch;
    FILE *fp, *ftop;
    if ((ftop = fopen( tofilename, "w")) == NULL) {
        printf("要写入的文件出问题");
        exit(0);
    }
    if ((fp = fopen(filename, "r")) != NULL) {
        if (fp == 0)exit(-1);
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '0')
            {
                if (HT[p].lchild != 0)
                {
                    p = HT[p].lchild;
                }
            }
            else if (ch == '1')
            {
                if (HT[p].rchild != 0)
                {
                    p = HT[p].rchild;
                }
            }
           // else if (ch == ' ' || ch == '\n')
            //    if (ftop != 0) fputc(ch, ftop);
            if (HT[p].lchild == 0 && HT[p].rchild == 0)
            {
                //printf("%c", a[p - 1].letter);
                if (ftop == 0) exit(0);
                str+=a[p-1].letter;
                fputc(a[p - 1].letter, ftop);
                p = 2 * n - 1;
            }
        }
        fclose(fp);
        fclose(ftop);
    }
    else
        printf("\ndecodescore:fail to open! \n");
    return str;
}

//文件变字符串（01文件变成字母串，Qt返回解码后的字母串）
QString Huffman_decodeStr(const char *filename,HuffmanTree HT, int n, alph a[]) {
    QString str;
    int p = 2 * n - 1;
    char ch;
    FILE *fp;
    if ((fp = fopen(filename, "r")) != NULL) {
        if (fp == 0)exit(-1);
        while ((ch = fgetc(fp)) != EOF) {
            if (ch == '0')
            {
                if (HT[p].lchild != 0)
                {
                    p = HT[p].lchild;
                }
            }
            else if (ch == '1')
            {
                if (HT[p].rchild != 0)
                {
                    p = HT[p].rchild;
                }
            }
           // else if (ch == ' ' || ch == '\n')
             //   str+=ch;
            if (HT[p].lchild == 0 && HT[p].rchild == 0)
            {
                //printf("%c", a[p - 1].letter);
                str+=a[p-1].letter;
                p = 2 * n - 1;
            }
        }
        fclose(fp);
    }
    else
        printf("\ndecodescore:fail to open! \n");
    return str;
}*/

//下面为编码生成函数
//字符串变字符串（字母字符串变01字符串。返回编码后的字符串）
QString Huffman_codeStr(char alstr[], HuffmanCode HC, int hash[])
{
    QString str;
    for(int i = 0; alstr[i]; ++i){
        int ch = alstr[i];
        //if (ch < 'a' || ch>'z') continue;
        str += HC[hash[ch]+1];
    }
    return str;
}

/*
//字符串变文件(字母串变成01串的文件)
QString Huffman_codeFILE(char alstr[],const char *tofilename,HuffmanCode HC)
{
    QString str;
    char ch;
    FILE * ftop;
    if ((ftop = fopen( tofilename, "w")) == NULL) {
        printf("要写入的文件出问题");
        exit(0);
    }
    while ((ch = *(alstr++)) != '\0') {
         //if (ch == ' ' || ch == '\n'){
         //     str+=ch;
         //     fprintf(ftop, "%c", ch);
         //}
         //else
           if (ch < 'a' || ch>'z') continue;
         else if (ftop != 0) {
               fprintf(ftop, "%s", HC[ch - 'a' + 1]);
               str+=HC[ch-'a'+1];
         }
      }
      fclose(ftop);
     return str;
}

//文件变文件(字母串文件变成01串文件，Qt中返回编码后的01串)
QString Huffman_codeFILE(const char *fromfilename,const char *tofilename,HuffmanCode HC)
{
    QString str;
    char ch;
    FILE* fp, * ftop;
    if ((ftop = fopen( tofilename, "w")) == NULL) {
        printf("要写入的文件出问题");
        exit(0);
    }
    if ((fp = fopen(fromfilename, "r")) != NULL) {
        if (fp == 0)exit(-1);
        while ((ch = fgetc(fp)) != EOF) {
            //if (ch == ' ' || ch == '\n'){
             //   str+=ch;
            //    fprintf(ftop, "%c", ch);
            //}
            // else
            if (ch < 'a' || ch>'z') continue;
            else if (ftop != 0) {
                fprintf(ftop, "%s", HC[ch - 'a' + 1]);
                str+=HC[ch-'a'+1];
            }
        }
        fclose(fp);
        fclose(ftop);
    }
    else
        printf("\ncodescore:fail to open! \n");
    return str;
}

//文件变字符串（字母串文件变成01串）
QString Huffman_codeStr(const char *fromfilename,HuffmanCode HC)
{
    QString str;
    char ch;
    FILE* fp;
    if ((fp = fopen(fromfilename, "r")) != NULL) {
        if (fp == 0)exit(-1);
        while ((ch = fgetc(fp)) != EOF) {
            //if (ch == ' ' || ch == '\n'){
             //   str+=ch;
             //   fprintf(ftop, "%c", ch);
            }
            //else*
            if (ch < 'a' || ch>'z') continue;
            else
                str+=HC[ch-'a'+1];
        }
        fclose(fp);
    }
    else
        printf("\ncodescore:fail to open! \n");
    return str;
}
*/

//下面为字符串和文件相互转化
//将字符串（无所谓是字母串还是01串）直接变成文件
bool saveStrToFile(const char* filename,const char *str)
{
    FILE *fp = fopen(filename,"a+");
    if(!fp) return false;
    for(int i = 0; str[i]; ++i){
        fputc(str[i],fp);
    }
    fclose(fp);
    return true;
}

//将文件内容直接变成字符串
QString transFileToStr(const char* filename)
{
    QString str;
    FILE *fp = fopen(filename,"r");
    if(!fp) return str;
    char ch;
    while((ch = fgetc(fp)) != EOF)
        str += ch;
    fclose(fp);
    return str;
}
