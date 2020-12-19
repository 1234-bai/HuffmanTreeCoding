/************struct.h************/
//各个结构体的定义

#ifndef STRUCT_H
#define STRUCT_H

#include <QString>

typedef struct{
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode, *HuffmanTree;
typedef char ** HuffmanCode;

typedef struct {
    char letter;
    int fre;
}alph;

HuffmanCode initHuffmanCode(int n);
HuffmanTree HuffmanCoding(HuffmanCode HC, alph w[], int n);

//字符串变字符串（01字符串变字母字符串，返回解码后的字母串）
QString Huffman_decodeStr(char s[],int lens, HuffmanTree HT,int n,alph a[]);

//字符串变字符串（字母字符串变01字符串。返回编码后的字符串）
QString Huffman_codeStr(char alstr[], HuffmanCode HC, int hash[]);

//文件同字符串的相互变化。
bool saveStrToFile(const char* filename,const char* str);
QString transFileToStr(const char* filename);

alph* read_txtFile(const char* filename, int hash[], int &n);
alph* read_yFile(const char* filename, QString &str, int *n);
//alph* read_txt(const char* str, int hash[], int &n);

bool write_headData_decodeFile(char* filename,alph table[],int numoftable);

//extern alph alphtable[26];

#endif // STRUCT_H
