#include <Huffman.h>
#define MAX_SIZE 270
#define WRITE_BUFF_SIZE 10
#define PSEUDO_EOF 256

QString s2q(const string& s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString& s)
{
    return string((const char*)s.toLocal8Bit());
}
pTree CreatHuffman(vector<pTree> NodeSet)
{
    pTree head = NULL;
    while (NodeSet.size() > 1)
    {
        pTree temp = new TreeNode;
        temp->name = 'M';
        int min1po;
        int min2po;
        if (NodeSet[1]->weight > NodeSet[0]->weight)
        {
            min1po = 0;
            min2po = 1;
        }
        else {
            min1po = 1;
            min2po = 0;
        }
        double bound = NodeSet[min2po]->weight;
        for (int i = 2; i < (int)NodeSet.size(); i++)
        {
            if (NodeSet[i]->weight < NodeSet[min1po]->weight)
            {
                min2po = min1po;
                min1po = i;
                bound = NodeSet[min2po]->weight;
            }
            else if (NodeSet[i]->weight < bound)
            {
                min2po = i;
                bound = NodeSet[min2po]->weight;
            }
        }
        temp->left = NodeSet[min1po];
        temp->right = NodeSet[min2po];
        temp->weight = NodeSet[min1po]->weight + NodeSet[min2po]->weight;
        NodeSet.erase(NodeSet.begin() + min1po);
        if (min1po > min2po)
            NodeSet.erase(NodeSet.begin() + min2po);
        else
            NodeSet.erase(NodeSet.begin() + min2po - 1);
        NodeSet.push_back(temp);
        head = temp;
    }
    return head;
}
pTree KeyboardIN(string s, unordered_map<char, int>& alph)
{
    for (int i = 0; i < (int)s.size(); i++)
    {
        if ((bool)(alph.find(s[i]) != alph.end()))
            alph[s[i]]++;
        else
            alph.insert({ s[i],1 });
    }
    vector<pTree> NodeSet;
    for (auto iter = alph.begin(); iter != alph.end(); iter++)
    {
        pTree temp = new TreeNode;
        temp->left = temp->right = NULL;
        temp->weight = iter->second;
        temp->name = iter->first;
        NodeSet.push_back(temp);
    }
    pTree root = CreatHuffman(NodeSet);
    return root;
}
void traceback(pTree root, string code, unordered_map<char, string>& CodeSet)
{
    if (root->name != 'M')
    {
        CodeSet.insert({ root->name, code });
        return;
    }
    if (root->left) {
        code.push_back('0');
        traceback(root->left, code, CodeSet);
        code.pop_back();
    }
    if (root->right) {
        code.push_back('1');
        traceback(root->right, code, CodeSet);
        code.pop_back();
    }
}

unordered_map<char, string> GetHash(pTree root) {
    unordered_map<char, string> CodeSet;
    string code;
    traceback(root, code, CodeSet);
    return CodeSet;
}
QString getRate(unordered_map<char, string> codeset, unordered_map<char, int> alph, int Sumweight)
{
    QString result;
    int bit = 1;
    for (int i = 2; i < (int)codeset.size(); i *= 2)bit++;
    double exsum = 0;
    for (auto i = alph.begin(); i != alph.end(); i++)
    {
        double p = (double)i->second / Sumweight;
        double p1 = Sumweight / i->second;
        exsum += p * log(p1) / log(2);
    }
    double expectation = exsum / bit * 100;
    double huffsum = 0;
    double real = 0;
    for (auto iter = codeset.begin(); iter != codeset.end(); iter++)
    {
        int len = (int)iter->second.size();
        huffsum += len * alph[iter->first];
    }
    real = huffsum / bit / Sumweight * 100;
    result = "Expect compression ratio:"+ QString::number(expectation)+ "%" + "\n" + "Actual compression ratio:" + QString::number(real) + "%" + "\n";
    return result;
 }

int binarystringtoint(string binarystring)
{
    int sum = 0;
    for (int i = 0; i < (int)binarystring.size(); i++)
    {
        if (binarystring[i] == '1')
        {
            int j = pow(2, binarystring.size() - i - 1);
            sum += j;
        }
    }
    return sum;
}

string inttobinarystring(int value)
{
    string binarystring;
    while (value > 0)
    {
        int r = value % 2;
        if (r == 1)binarystring.insert(0, 1, '1');
        else binarystring.insert(0, 1, '0');
        value = value / 2;
    }
    if (binarystring.size() < 8)
    {
        binarystring.insert(0, 8 - binarystring.size(), '0');
    }
    return binarystring;
}


QString Compression(string s,unordered_map<char, string> codeset,QString fileName)
{
    QString time;
    fstream out_file(fileName.toLatin1().data(),std::fstream::out);
    clock_t begin=clock();

    int size=(int)codeset.size();
    out_file << size << endl;
    string binary_string;
    for(auto it= codeset.begin(); it != codeset.end(); ++it)
    {
        out_file << it->first << " "<< it->second <<endl;
    }
    for (int i = 0; i < (int)s.size(); i++)
    {
        binary_string+= codeset[s[i]];
    }
    int n = 0;
    if (binary_string.size() % 8)
        n = 8 - binary_string.size() % 8;
    if (n)
    {
        binary_string.append(n, '0');
    }
    int length = binary_string.size();
    out_file << length << endl;
    int zero_num= n ;
    out_file << n <<endl;
    for (int i = 0; i < (int)binary_string.size(); i += 8)
    {
        string k = binary_string.substr(i, 8);
        int temp = binarystringtoint(k);
        unsigned char ch = temp;
        out_file<<ch;
    }
    out_file.close();

    clock_t end=clock();
    time = QString::number(double(end-begin)/CLOCKS_PER_SEC);
    return time;
}
QString Excute(string s,QString save_path)
{
    unordered_map<char, int> alph;
    pTree a = KeyboardIN(s, alph);
    unordered_map<char, string> codeset = GetHash(a);
    QString result = getRate(codeset, alph, (int)s.size());
    auto iter = codeset.begin();
    while (iter != codeset.end())
    {
        string ff;
        ff.push_back(iter->first);
        result += s2q(ff) +":"+ s2q(iter->second) + "\n";
        ++iter;
    }
   QString time = Compression(s,codeset,save_path);
   result=result+"zip time:"+time+"s";
   return result;
}

QString decode(QString path,QString save_path){
    clock_t begin=clock();
    QFile openfile(path);
    if(!openfile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL,QString("警告"),QString("文件打开失败"));
        return "";
    }
    fstream in_file(path.toLatin1().data(),std::fstream::in);
    int SetSize;
    in_file >> SetSize;
    unordered_map<string,char> CodeSet;
    for(int i=0;i<SetSize;++i)
    {
        char alph;
        string code;
        in_file >> alph >> code;
        CodeSet.insert({code,alph});
    }
    int valuelength;
    in_file >> valuelength;
    int zero_num;
    in_file >> zero_num;
    string valuestring;
    for (int i = 0; i < valuelength / 8 -zero_num; i++)
    {
       unsigned char ch;
       in_file>>ch;
       int zipvalue=ch;
       valuestring += inttobinarystring(zipvalue);
    }
    in_file.close();
    fstream out_file(save_path.toLatin1().data(),std::fstream::out);
    int prepoint=0;
    for(int i=0;i<valuestring.size();i++)
    {
        string code=valuestring.substr(prepoint,i-prepoint+1);
        if(CodeSet.find(code)!=CodeSet.end())
        {
            out_file << CodeSet[code];
            prepoint=i+1;
        }
    }
    clock_t end=clock();
    QString tip="解压用时:";
    tip+=QString::number(double(end-begin)/CLOCKS_PER_SEC);
    tip+="s";
    return tip;
}
