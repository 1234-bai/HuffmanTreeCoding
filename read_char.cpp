/************read_char.cpp**************/
//文件读取和写入

#include "struct.h"
#include <stdio.h>
#include <QMessageBox>

//读取原始文件，得到字符串的种类和出现频率，储存在table[]中
//后利用table[]生成对应的哈弗曼树和哈夫曼表
alph* read_txtFile(const char* filename, int hash[], int &n)
{
    FILE *fp = fopen(filename,"r");
    if (!fp) return NULL;
    char ch;
    int size = 10;
    alph* table = (alph*)malloc(sizeof(alph)*size);
    (n) = 0;
    while ((ch = fgetc(fp)) != EOF) {
        int inx = ch;
        if(inx < 0) continue;
        if (hash[inx] == -1) {
            (n)++;
            if(n >= size){
                table = (alph*)realloc(table, sizeof(alph) * (size+10));
                size += 10;
            }
            if (!table) exit(0);
            table[(n) - 1].letter = ch;
            table[(n) - 1].fre = 1;
            hash[inx] = (n)-1;
        }
        else {
            table[hash[inx]].fre++;
        }
    }
    fclose(fp);
    return table;
}

/*
alph* read_txt(const char* str, int hash[], int &n)
{
    alph* table = (alph*)malloc(sizeof(alph));
    (n) = 0;
    for (int i = 0; str[i]; ++i) {
        int inx = str[i];
        if(inx < 0) continue;
        if (hash[inx] == -1) {
            (n)++;
            table = (alph*)realloc(table, sizeof(alph) * (n));
            if (!table) exit(0);
            table[(n) - 1].letter = str[i];
            table[(n) - 1].fre = 1;
            hash[inx] = (n)-1;
        }
        else {
            table[hash[inx]].fre++;
        }
    }
    return table;
}
*/

alph* read_yFile(const char* filename, QString &str, int *n)
{
    FILE* fp = fopen(filename, "r");
    int numoftable = 0;
    fscanf(fp, "%d", &numoftable);
    *n = numoftable;
    alph* table = (alph*)malloc(sizeof(alph)*numoftable);
    for(int i = 0; i < numoftable; ++i){
        int m, n;
        fscanf(fp,"%d %d", &m, &n);
        table[i].letter = (char)m;
        table[i].fre = n;
    }
    char ch;
    str = "\0";
    ch = fgetc(fp);
    while((ch = fgetc(fp)) != EOF){
        str += ch;
    }
    fclose(fp);
    return table;
}

//将从原始文件获得的字符信息table[]（头数据）写到编码文件里面，
bool write_headData_decodeFile(char* filename,alph table[],int numoftable)
{
    FILE* fp = fopen(filename,"w");
    if(!fp) return false;
    fprintf(fp, "%d\n", numoftable);
    for (int i = 0; i < numoftable; ++i) {
        fprintf(fp, "%d %d\n", table[i].letter, table[i].fre);
    }
    fclose(fp);
    return true;
}
