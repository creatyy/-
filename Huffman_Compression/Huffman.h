#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <mainwindow.h>
#include<QFileDialog>
#include<QMenu>
#include<QAction>
#include <fstream>
using namespace std;


struct TreeNode {
    char name;
    double weight;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char chara, double cweight) :name(chara), weight(cweight), left(NULL), right(NULL) {}
    TreeNode() :name('0'), weight(0.0), left(NULL), right(NULL) {}
};
typedef TreeNode* pTree;

pTree CreatHuffman(vector<pTree> NodeSet);

pTree KeyboardIN(string s, unordered_map<char, int>& alph);

void traceback(pTree root, string code, unordered_map<char, string>& CodeSet);

unordered_map<char, string> GetHash(pTree root);

QString getRate(unordered_map<char, string> codeset, unordered_map<char, int> alph, int Sumweight);

QString Compression(string s,unordered_map<char, string> codeset,QString fileName);

QString Excute(string s,QString save_path);

QString s2q(const string& s);

string q2s(const QString& s);

string inttobinarystring(int value);

int binarystringtoint(string binarystring);

QString decode(QString path,QString save_path);

#endif // HUFFMAN_H
