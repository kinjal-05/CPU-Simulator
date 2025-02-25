#include<bits/stdc++.h>
#include<fstream>
#include <ctime>  
#include <bitset>
using namespace std;

void customSleep(int seconds) 
{
    clock_t start_time = clock();
    while (clock() < start_time + seconds * CLOCKS_PER_SEC);
}
set<string>label;
map<string,string>mymemory;
string name="test.asm";
ofstream fout("test.txt");

string pc="0000";
map<string,string>memory;
string start="0000";

map<string,string>registers;
map<string,string>flags;


unordered_set<string>instr={"MOV","MVI","LXI","LDA","STA","LHLD","SHLD","LDAX","STAX","XCHG","ADD","ADI","ADC","ACI","SUB","SUI","SBB","SBI","SBI","INR",
"DCR","INX","DCX","DAD","ANA","ANI","XRA","XRI","ORA","ORI","CMA","CMC","STC"};

unordered_set<string>onetoken={"XCHG","CMC","CMA","STC","DAD","LSL","LSR"};

unordered_set<string>threetoken={"MOV","MVI","LXI"};

unordered_set<string>twotoken={"LDA","STA","LHLD","SHLD","LDAX","STAX","ADD","CMP","ADI","ADC","ACI","SUB","SUI","SBB","SBI","INR","DCR","INX","DCX","ANA","ANI","XRA","XRI","ORA","ORI"};

unordered_set<string>twotoken8bit={"ADI","ACI","SUI","SBI","ANI","XRI","ORI"};

unordered_set<string>twotoken16bit={"LDA","STA","LHLD","SHLD"};

unordered_set<string>logicaltoken={"JMP","JC","JNC","JZ","JNZ"};

bool isValid8bit(string str)
{
    if(str.size()!=3) return false;
    if(str[2]!='H' && str[2]!='h') return false;
    if(((str[0]>='0' && str[0]<='9') || (str[0]>='A' && str[0]<='F')) && ((str[1]>='0' && str[1]<='9') || (str[1]>='A' && str[1]<='F')))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isValid16bit(string str)
{
    if(str.size()!=5) return false;
    if(str[4]!='H' && str[4]!='h') return false;
    bool f=true;
    for(int i=0;i<4;i++)
    {
        if((str[i]>='0' && str[i]<='9') || (str[i]>='A' && str[i]<='F'))
        {
            f=true;
        }
        else
        {
            f=false;
        }
    }
    return f;
}

char plusone(char c)
{
    if((c>='0' && c<'9') || (c>='A' && c<='E'))
    {
        c=(char)(c+1);
    }
    else if(c=='9')
    {
        c=(char)('A');
    }
    return c;
}

void incrementCounter()
{
    if(pc[3]!='F')
    {
        pc[3]=plusone(pc[3]);
    }
    else
    {
        if(pc[2]!='F')
        {
            pc[2]=plusone(pc[2]);
            pc[3]='0';
        }
        else
        {
            if(pc[1]!='F')
            {
                pc[1]=plusone(pc[1]);
                pc[2]=pc[3]='0';
            }
            else
            {
                if(pc[0]!='F')
                {
                    pc[0]=plusone(pc[0]);
                    pc[1]=pc[2]=pc[3]='0';
                }
                else
                {
                    pc="0000";
                }
            }
        }
    }
}


string incrementCounter1(string pc)
{
    if(pc[3]!='F')
    {
        pc[3]=plusone(pc[3]);
    }
    else
    {
        if(pc[2]!='F')
        {
            pc[2]=plusone(pc[2]);
            pc[3]='0';
        }
        else
        {
            if(pc[1]!='F')
            {
                pc[1]=plusone(pc[1]);
                pc[2]=pc[3]='0';
            }
            else
            {
                if(pc[0]!='F')
                {
                    pc[0]=plusone(pc[0]);
                    pc[1]=pc[2]=pc[3]='0';
                }
                else
                {
                    pc="0000";
                }
            }
        }
    }
    return pc;
}


bool isValidRegister(string str)
{
    if(str=="A" || str=="B" || str=="C" || str=="D" || str=="E" || str=="H" || str=="L")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void addToMemory(string opcode,string data1,string data2,string data3)
{
    memory[pc]=opcode;
    fout<<pc<<' ';
    incrementCounter();
    if(data1!="")
    {
        memory[pc]=(data1.size()==1)?data1:data1.substr(0,data1.size()-1);
        fout<<pc<<' ';
        incrementCounter();
       
    }
    if(data2!="")
    {
        memory[pc]=(data2.size()==1)?data2:data2.substr(0,data2.size()-1);
        fout<<pc<<' ';
        incrementCounter();
    }
    if(data3!="")
    {
        memory[pc]=(data3.size()==1)?data3:data3.substr(0,data3.size()-1);
        fout<<pc<<' ';
        incrementCounter();
    }
}








bool isValidIntrunction(string str)
{
    vector<string>token;
    stringstream ss(str);
    string temp;
    while(getline(ss,temp,' '))
    {
        stringstream ss1(temp);
        string temp1;
        while(getline(ss1,temp1,','))
        {
            token.push_back(temp1);
        }

    }
    for(auto a:token)
    {
        cout<<a<<' ';
    }
    cout<<endl;
    // return true;

    string opcode=token[0];
    int n=token.size();
    if(opcode[opcode.size()-1]==':')
    {
        if(token.size()==1) return false;
        string str=opcode;
        str.pop_back();
        label.insert(str);
        addToMemory(str,"","","");
        vector<string>v;
        for(int i=1;i<token.size();i++)
        {
            v.push_back(token[i]);
        }
        token=v;
    }
    n=token.size();
    opcode=token[0];
    if(n==1)
    {
        if(onetoken.find(opcode)==onetoken.end())
        {
            return false;
        }
        else
        {
            addToMemory(opcode,"","","");
            fout<<endl;
            return true;
        }
    }
    else if(n==2)
    {
        if(logicaltoken.find(opcode)!=logicaltoken.end())
        {
            string data=token[1];
            if(label.find(data)==label.end())
            {
                return false;
            }
            addToMemory(opcode,data,"","");
        }
        else if(twotoken.find(opcode)==twotoken.end())
        {
            return false;
        }
        else
        {
            if(twotoken8bit.find(opcode)!=twotoken8bit.end())
            {
                // cout<<"KINJAL"<<endl;
                string data1=token[1];
                // cout<<data1<<endl;
                if(isValid8bit(data1)==false) return false;
                addToMemory(opcode,data1,"","");
                fout<<endl;
                return true;
            }
            else if(twotoken16bit.find(opcode)!=twotoken16bit.end())
            {
                string d1=token[1];
                // if(d1.size()!=5) return false;
                if(isValid16bit(d1)==false) return false;
                string data1=d1.substr(2,5);
                string data2=d1.substr(0,3);
                addToMemory(opcode,data1,data2,"");
                fout<<endl;
                return true;
            }
            else
            {
                string data1=token[1];
                if(isValidRegister(data1)==false) return false;
                addToMemory(opcode,data1,"","");
                fout<<endl;
                return true;
            }
        }
    }
    else if(n==3)
    {
        if(threetoken.find(opcode)==threetoken.end())
        {
            return false;
        }
        else
        {
            if(opcode=="MOV")
            {
                string data1=token[1];
                string data2=token[2];
                if(isValidRegister(data1)==false || isValidRegister(data2)==false) return false;
                addToMemory(opcode,data1,data2,"");
                fout<<endl;
                return true;
            }
            else if(opcode=="LXI")
            {
                string data1=token[1];
                string d2=token[2];
                if(isValidRegister(data1)==false) return false;
                if(isValid16bit(d2)==false) return false;
                string data2=d2.substr(2,5);
                string data3=d2.substr(0,3);
                addToMemory(opcode,data1,data2,data3);
                fout<<endl;
                return true;
            }
            else if(opcode=="MVI")
            {
                string data1=token[1];
                string data2=token[2];
                if(isValidRegister(data1)==false || isValid8bit(data2)==false) return false;
                addToMemory(opcode,data1,data2,"");
                fout<<endl;
                return true;
            }
            else
            {
                return false;
            }
            
        }
    }
    else
    {
        return false;
    }
}


string trim(string str)
{
    size_t end=str.find_last_not_of(" \t\n\r\f\v");
    if(end==string::npos) return "";
    else return str.substr(0,end+1);
}

void readFile()
{
    // stringstream ss;
    ifstream fin;
    fin.open(name);
    string str;
    while(getline(fin,str))
    {
        str=trim(str);
        if(str.find(';')==0)
        {
            continue;
        }
        if(str=="HLT" || str=="STOP")
        {
            break;
        }
        if(isValidIntrunction(str)==false)
        {
            cout<<"Error Occur"<<endl;
            break;
        }
    }
}
bool executemov(vector<string>token)
{
    if(token.size()!=3) return false;
    string data1=memory[token[1]];
    string data2=memory[token[2]];
    registers["data1"]=registers["data2"];
    if(registers["data1"]=="00")
    {
        flags["Z"]="01";
    }
    else
    {
        flags["Z"]="00";
    }
    return true;
}

bool executemvi(vector<string>token)
{
    if(token.size()!=3) return false;
    string data1=memory[token[1]];
    string data2=memory[token[2]];
    registers[data1]=data2;
    if(registers[data1]=="00")
    {
        flags["Z"]="01";
    }
    else
    {
        flags["Z"]="00";
    }
    return true;
}
void display()
{
    cout<<"---------------Content Of Registers--------------------"<<endl;
    for(auto a:registers)
    {
        cout<<a.first<<"->"<<a.second<<endl;
    }
    cout<<"----------------Content Of Flags------------------------"<<endl;
    for(auto a:flags)
    {
        cout<<a.first<<"->"<<a.second<<endl;
    }
    cout<<"--------------------------------------------------------------------------------------------"<<endl;
}

bool executelxi(vector<string>token)
{
    if(token.size()!=4) return false;
    string data1=memory[token[1]];
    string d2=memory[token[2]];
    string d1=memory[token[3]];
    if(data1=="B")
    {
        registers["B"]=d1;
        registers["C"]=d2;
        if(d1=="00" && d2=="00")
        {
            flags["Z"]="01";
        }
        else
        {
            flags["Z"]="00";
        }
        return true;
    }
    else if(data1=="D")
    {
        registers["D"]=d1;
        registers["E"]=d2;
        if(d1=="00" && d2=="00")
        {
            flags["Z"]="01";
        }
        else
        {
            flags["Z"]="00";
        }
        return true;
    }
    else if(data1=="H")
    {
        registers["H"]=d1;
        registers["L"]=d2;
        if(d1=="00" && d2=="00")
        {
            flags["Z"]="01";
        }
        else
        {
            flags["Z"]="00";
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool executelda(vector<string>token)
{
    if(token.size()!=3) return false;
    string d2=memory[token[1]];
    string d1=memory[token[2]];
    string s="";
    s+=d1;
    s+=d2;
    string data=mymemory[s];
    registers["A"]=data;
    if(registers["A"]=="00")
    {
        flags["Z"]="01";
    }
    else
    {
        flags["Z"]="00";
    }
    return true;

}

bool executesta(vector<string>token)
{
    if(token.size()!=3) return false;
    string d2=memory[token[1]];
    string d1=memory[token[2]];
    string s="";
    s+=d1;
    s+=d2;
    string data=registers["A"];
    mymemory[s]=data;
    return true;
}

bool executelhld(vector<string>token)
{
    if(token.size()!=3) return false;
    string d2=memory[token[1]];
    string d1=memory[token[2]];
    string s="";
    s+=d1;
    s+=d2;
    registers["H"]=mymemory[s];
    s=incrementCounter1(s);
    registers["L"]=mymemory[s];
    return true;

}
bool executeshld(vector<string>token)
{
    if(token.size()!=3) return false;
    string d2=memory[token[1]];
    string d1=memory[token[2]];
    string s="";
    s+=d1;
    s+=d2;
    registers["L"]=mymemory[s];
    s=incrementCounter1(s);
    registers["H"]=mymemory[s];
    return true;
}

bool executeldax(vector<string>token)
{
    if(token.size()!=2) return false;
    string d1=memory[token[1]];
    if(d1=="B")
    {
        string s1=registers["B"];
        string s2=registers["C"];
        string s="";
        s+=s1;
        s+=s2;
        registers["A"]=mymemory[s];
        return true;
    }
    else if(d1=="D")
    {
        string s1=registers["D"];
        string s2=registers["E"];
        string s="";
        s+=s1;
        s+=s2;
        registers["A"]=mymemory[s];
        return true;
    }
    else
    {
        return false;
    }

}

bool executestax(vector<string>token)
{
    if(token.size()!=2) return false;
    string d1=memory[token[1]];
    if(d1=="B")
    {
        string s1=registers["B"];
        string s2=registers["C"];
        string s="";
        s+=s1;
        s+=s2;
        string data=registers["A"];
        mymemory[s]=data;
        return true;
    }
    else if(d1=="D")
    {
        string s1=registers["D"];
        string s2=registers["E"];
        string s="";
        s+=s1;
        s+=s2;
        string data=registers["A"];
        mymemory[s]=data;
        return true;
    }
    else
    {
        return false;
    }
}

bool executexchg(vector<string>token)
{
    if(token.size()!=1) return false;
    string dd=registers["D"];
    string ed=registers["E"];
    string hd=registers["H"];
    string ld=registers["L"];
    registers["D"]=hd;
    registers["E"]=ld;
    registers["H"]=dd;
    registers["L"]=ed;
    return true;
}

int hextodecimal(string str)
{
    map<char,int>mp;
    mp['A']=10;
    mp['B']=11;
    mp['C']=12;
    mp['D']=13;
    mp['E']=14;
    mp['F']=15;
    mp['0']=0;
    mp['1']=1;
    mp['2']=2;
    mp['3']=3;
    mp['4']=4;
    mp['5']=5;
    mp['6']=6;
    mp['7']=7;
    mp['8']=8;
    mp['9']=9;
    int num=0;
    num=(mp[str[0]]*16);
    num+=mp[str[1]];
    return num;
}

string decimaltohex(int num)
{
    // cout<<num<<endl;
    map<int,string>mp;
    mp[1]='1';
    mp[2]='2';
    mp[3]='3';
    mp[4]='4';
    mp[5]='5';
    mp[6]='6';
    mp[7]='7';
    mp[8]='8';
    mp[9]='9';
    mp[10]='A';
    mp[11]='B';
    mp[12]='C';
    mp[13]='D';
    mp[14]='E';
    mp[15]='F';
    mp[0]='0';
    string s="";
    while(num>0)
    {
        int re=num%16;
        s+=mp[re];
        num/=16;
        
    }
    if(s.size()>=3)
    {
        flags["C"]="01";
    }
    else
    {
        flags["C"]="00";
    }
    
    reverse(s.begin(),s.end());
    // cout<<s<<endl;
    string str="";
    if(s.size()>=2)
    str+=s[s.size()-2];
    str+=s[s.size()-1];
    // if(str.size()==1)
    // {
    //     cout<<"KINJAL"<<endl;
    // }
    if(str.size()==1)
    {
        cout<<"KINJAL"<<endl;
        char c=str[0];
        cout<<c<<endl;
        str.pop_back();
        cout<<str<<endl;
        str+='0';
        str+=c;
    }
    if(str=="00")
    {
        flags["Z"]="01";
    }
    else
    {
        flags["Z"]="00";
    }
    // if(str.size()==1)
    // {
    //     cout<<"KINJAL"<<endl;
    //     char c=str[0];
    //     cout<<c<<endl;
    //     str.pop_back();
    //     cout<<str<<endl;
    //     str+='0';
    //     str+=c;
    // }
    // cout<<str<<endl;
    return str;
    
}

bool executeadd(vector<string>token)
{
    if(token.size()!=2)
    {
        return false;
    }
    string s1=registers["A"];
    int num=hextodecimal(s1);
    // cout<<num<<endl;
    string s2=registers[memory[token[1]]];
    // cout<<s2<<endl;
    int num1=hextodecimal(s2);
    // cout<<num1<<endl;
    int num2=num+num1;
    // cout<<num2<<endl;
    string s=decimaltohex(num2);
    registers["A"]=s;
    return true;

}
bool executeadi(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    int num1=hextodecimal(s1);
    string s2=memory[token[1]];
    int num2=hextodecimal(s2);
    int num=num1+num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    return true;
}

char plus1(char c)
{
    if(c=='9') return 'A';
    else return (char)(c+1);
}

bool executeadc(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=registers[memory[token[1]]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1+num2;
    string s=decimaltohex(num);
    // cout<<s<<endl;
    if(flags["C"]=="01")
    {
        if(s[1]!='F')
        {
            s[1]=plus1(s[1]);
        }
        else
        {
            s[0]=plus1(s[0]);
            s[1]='0';
        }
    }
    registers["A"]=s;
    return true;
}

bool executeaci(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=memory[token[1]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1+num2;
    string s=decimaltohex(num);
    if(flags["C"]=="01")
    {
        if(s[1]!='F')
        {
            s[1]=plus1(s[1]);
        }
        else
        {
            s[0]=plus1(s[0]);
            s[1]='0';
        }
    }
    registers["A"]=s;
    return true;
}

bool executesub(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=registers[memory[token[1]]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1-num2;
    // cout<<num1<<" "<<num2<<" "<<num<<endl;
    if(num>=0)
    {
        string s=decimaltohex(num);
        registers["A"]=s;
        return true;
    }
    else
    {
        
        num=abs(num);
        num=~num;
        num=num+1;
        std::bitset<8> binary(num);

        unsigned long unsignedValue = binary.to_ulong();
        int data =(int)(unsignedValue);
        // cout<<data<<endl;
        string s=decimaltohex(data);
        flags["C"]="01";
        flags["S"]="01";
        registers["A"]=s;
    }
    return true;
}

bool executesui(vector<string>token)
{
    if(token.size()!=2) return false;
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=memory[token[1]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1-num2;
    // cout<<num1<<" "<<num2<<" "<<num<<endl;
    if(num>=0)
    {
        string s=decimaltohex(num);
        registers["A"]=s;
        return true;
    }
    else
    {
        
        num=abs(num);
        num=~num;
        num=num+1;
        std::bitset<8> binary(num);

        unsigned long unsignedValue = binary.to_ulong();
        int data =(int)(unsignedValue);
        // cout<<data<<endl;
        string s=decimaltohex(data);
        flags["C"]="01";
        flags["S"]="01";
        registers["A"]=s;
    }
    return true;
}

bool executesbb(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=registers[memory[token[1]]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num2+1;
    int numf=num1-num;
    if(num>=0)
    {
        string s=decimaltohex(num);
        registers["A"]=s;
        return true;
    }
    else
    {
        
        num=abs(num);
        num=~num;
        num=num+1;
        std::bitset<8> binary(num);

        unsigned long unsignedValue = binary.to_ulong();
        int data =(int)(unsignedValue);
        // cout<<data<<endl;
        string s=decimaltohex(data);
        flags["C"]="01";
        flags["S"]="01";
        registers["A"]=s;
        return true;
    }
    if(flags["C"]=="01")
    {
        flags["P"]="01";
    }
    return true;

}

bool executesbi(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=memory[token[1]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num2+1;
    int numf=num1-num;
    if(num>=0)
    {
        string s=decimaltohex(num);
        registers["A"]=s;
        return true;
    }
    else
    {
        
        num=abs(num);
        num=~num;
        num=num+1;
        std::bitset<8> binary(num);

        unsigned long unsignedValue = binary.to_ulong();
        int data =(int)(unsignedValue);
        // cout<<data<<endl;
        string s=decimaltohex(data);
        flags["C"]="01";
        flags["S"]="01";
        registers["A"]=s;
        return true;
    }
    if(flags["C"]=="01")
    {
        flags["P"]="01";
    }
    return true;
}

bool executeinr(vector<string>token)
{
    if(token.size()!=2) return false;
    string s=registers[memory[token[1]]];
    int num=hextodecimal(s);
    num=num+1;
    string str=decimaltohex(num);
    registers[memory[token[1]]]=str;
    return true;
}




bool executedcr(vector<string>token)
{
    if(token.size()!=2) return false;
    string s=registers[memory[token[1]]];
    int num=hextodecimal(s);
    num=num-1;
    if(num>=0)
    {
        string s=decimaltohex(num);
        registers[memory[token[1]]]=s;
        return true;
    }
    else
    {
        
        num=abs(num);
        num=~num;
        num=num+1;
        std::bitset<8> binary(num);

        unsigned long unsignedValue = binary.to_ulong();
        int data =(int)(unsignedValue);
        // cout<<data<<endl;
        string s=decimaltohex(data);
        flags["C"]="01";
        flags["S"]="01";
        registers[memory[token[1]]]=s;
        return true;
    }
    return true;
}


string decimaltohex1(int num)
{
    // cout<<num<<endl;
    map<int,string>mp;
    mp[1]='1';
    mp[2]='2';
    mp[3]='3';
    mp[4]='4';
    mp[5]='5';
    mp[6]='6';
    mp[7]='7';
    mp[8]='8';
    mp[9]='9';
    mp[10]='A';
    mp[11]='B';
    mp[12]='C';
    mp[13]='D';
    mp[14]='E';
    mp[15]='F';
    mp[0]='0';
    string s="";
    // cout<<num<<endl;
    while(num>0)
    {
        int re=num%16;
        s+=mp[re];
        num/=16;
        
    }
    // cout<<s<<endl;
    if(s.size()>=3)
    {
        flags["AC"]="01";
    
    }
    else
    {
        flags["AC"]="00";
    }
    
    reverse(s.begin(),s.end());
    // cout<<s<<endl;
    string str="";
    if(s.size()>=2)
    str+=s[s.size()-2];
    str+=s[s.size()-1];
    // if(str.size()==1)
    // {
    //     cout<<"KINJAL"<<endl;
    // }
    if(str.size()==1)
    {
        // cout<<"KINJAL"<<endl;
        char c=str[0];
        // cout<<c<<endl;
        str.pop_back();
        // cout<<str<<endl;
        str+='0';
        str+=c;
    }
    if(str=="00")
    {
        flags["Z"]="01";
    }
    else
    {
        flags["Z"]="00";
    }
    // if(str.size()==1)
    // {
    //     cout<<"KINJAL"<<endl;
    //     char c=str[0];
    //     cout<<c<<endl;
    //     str.pop_back();
    //     cout<<str<<endl;
    //     str+='0';
    //     str+=c;
    // }
    // cout<<str<<endl;
    return str;
    
}

bool executedcx(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=memory[token[1]];
    if(s1=="B")
    {
        s1=registers["C"];
        string s2=registers["B"];
        int num=hextodecimal(s1);
        num=num-1;
        if(num>=0)
        {
            registers["C"]=decimaltohex(num);
            return true;
        }
        else
        {
            num=abs(num);
            num=~num;
            num=num+1;
            std::bitset<8> binary(num);
            unsigned long unsignedValue = binary.to_ulong();
            num =(int)(unsignedValue);
            registers["C"]=decimaltohex1(num);
            flags["AC"]="01";
            if(flags["AC"]=="01")
            {
                int num1=hextodecimal(s2);
                num1=num1-1;
                // cout<<num1<<endl;
                if(num1>=0)
                {
                    registers["B"]=decimaltohex(num1);
                    return true;
                }
                else
                {
                    num1=abs(num1);
                    num1=~num1;
                    num1=num1+1;
                    std::bitset<8> binary(num1);

                    unsigned long unsignedValue = binary.to_ulong();
                    int data =(int)(unsignedValue);
                    // cout<<data<<endl;
                    string s=decimaltohex(data);
                    flags["C"]="01";
                    flags["S"]="01";
                    registers["B"]=s;
                    return true;
                }
            }
            return true;
        }
    }
    else if(s1=="D")
    {
        s1=registers["E"];
        string s2=registers["D"];
        int num=hextodecimal(s1);
        num=num-1;
        if(num>=0)
        {
            registers["E"]=decimaltohex(num);
            return true;
        }
        else
        {
            num=abs(num);
            num=~num;
            num=num+1;
            std::bitset<8> binary(num);
            unsigned long unsignedValue = binary.to_ulong();
            num =(int)(unsignedValue);
            registers["E"]=decimaltohex1(num);
            flags["AC"]="01";
            if(flags["AC"]=="01")
            {
                int num1=hextodecimal(s2);
                num1=num1-1;
                if(num1>=0)
                {
                    registers["D"]=decimaltohex(num1);
                    return true;
                }
                else
                {
                    num1=abs(num1);
                    num1=~num1;
                    num1=num1+1;
                    std::bitset<8> binary(num1);

                    unsigned long unsignedValue = binary.to_ulong();
                    int data =(int)(unsignedValue);
                    // cout<<data<<endl;
                    string s=decimaltohex(data);
                    flags["C"]="01";
                    flags["S"]="01";
                    registers["D"]=s;
                    return true;
                }
            }
            return true;
        }
    }
    else if(s1=="H")
    {
        // cout<<"KINJAL"<<endl;
        s1=registers["L"];
        string s2=registers["H"];
        int num=hextodecimal(s1);

        num=num-1;
        // cout<<num<<endl;
        if(num>=0)
        {
            registers["L"]=decimaltohex(num);
            return true;
        }
        else
        {
            num=abs(num);
            num=~num;
            num=num+1;
            std::bitset<8> binary(num);

            unsigned long unsignedValue = binary.to_ulong();
            num =(int)(unsignedValue);
            registers["L"]=decimaltohex1(num);
            // cout<<"KINJAL"<<endl;
            flags["AC"]="01";
            if(flags["AC"]=="01")
            {
                // cout<<"KINJAL"<<endl;
                int num1=hextodecimal(s2);
                num1=num1-1;
                // cout<<num1<<endl;
                if(num1>=0)
                {
                    registers["H"]=decimaltohex(num1);
                    return true;
                }
                else
                {
                    num1=abs(num1);
                    num1=~num1;
                    num1=num1+1;
                    std::bitset<8> binary(num1);

                    unsigned long unsignedValue = binary.to_ulong();
                    int data =(int)(unsignedValue);
                    // cout<<data<<endl;
                    string s=decimaltohex(data);
                    flags["C"]="01";
                    flags["S"]="01";
                    registers["H"]=s;
                    return true;
                }
            }
            return true;
        }
    }
    else
    {
        return false;
    }
}

bool executeinx(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=memory[token[1]];
    if(s1=="B")
    {
        s1=registers["C"];
        string s2=registers["B"];
        int num=hextodecimal(s1);
        int num1=hextodecimal(s2);
        num=num+1;
        s1=decimaltohex1(num);
        registers["C"]=s1;
        if(flags["AC"]=="01")
        {
            s2=decimaltohex(num1+1);
            registers["B"]=s2;
        }
        return true;
    }
    else if(s1=="D")
    {
        s1=registers["E"];
        string s2=registers["D"];
        int num=hextodecimal(s1);
        int num1=hextodecimal(s2);
        num=num+1;
        s1=decimaltohex1(num);
        registers["E"]=s1;
        if(flags["AC"]=="01")
        {
            s2=decimaltohex(num1+1);
            registers["D"]=s2;
        }
        return true;
    }
    else if(s1=="H")
    {
        s1=registers["L"];
        string s2=registers["H"];
        int num=hextodecimal(s1);
        int num1=hextodecimal(s2);
        num=num+1;
        s1=decimaltohex1(num);
        registers["L"]=s1;
        if(flags["AC"]=="01")
        {
            s2=decimaltohex(num1+1);
            registers["H"]=s2;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool executeana(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=registers[memory[token[1]]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1 & num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    return true;
}

bool executeani(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=memory[token[1]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1 & num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    return true;
}

bool executexra(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=registers[memory[token[1]]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1 ^ num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    return true;
}

bool executexri(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=memory[token[1]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1 ^ num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    return true;
}

bool executeora(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=registers[memory[token[1]]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1 | num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    return true;
}

bool executecmc(vector<string>token)
{
    if(token.size()!=1) return false;
    if(flags["C"]=="01") flags["C"]="00";
    else flags["C"]="01";
    return true;
}

bool executestc(vector<string>token)
{
    if(token.size()!=1) return false;
    flags["C"]="01";
    return true;
}

bool executecma(vector<string>&token)
{
    if(token.size()!=1) return false;
    string s=registers["A"];
    int num=hextodecimal(s);
    //num=abs(num);
    num=~num;
            
    std::bitset<8> binary(num);

    unsigned long unsignedValue = binary.to_ulong();
    num =(int)(unsignedValue);
    s=decimaltohex(num);
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    registers["A"]=s;
    return true;
}

bool executeori(vector<string>token)
{
    if(token.size()!=2) return false;
    string s1=registers["A"];
    string s2=memory[token[1]];
    int num1=hextodecimal(s1);
    int num2=hextodecimal(s2);
    int num=num1 | num2;
    string s=decimaltohex(num);
    registers["A"]=s;
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    return true;
}

bool executelsl(vector<string>token)
{
    if(token.size()!=1) return false;
    string s=registers["A"];
    int num=hextodecimal(s);
    num=num<<1;
    s=decimaltohex(num);
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    registers["A"]=s;
    return true;
}

bool executelsr(vector<string>token)
{
    if(token.size()!=1) return false;
    string s=registers["A"];
    int num=hextodecimal(s);
    num=num>>1;
    s=decimaltohex(num);
    if(s=="00") flags["Z"]="01";
    else flags["Z"]="00";
    registers["A"]=s;
    return true;
}

bool executecmp(vector<string>token)
{
    if(token.size()!=2) return false;
    string s=registers[memory[token[1]]];
    int num=hextodecimal(s);
    string s1=registers["A"];
    int num1=hextodecimal(s1);
    if(num==num1)
    {
        flags["Z"]="01";
        flags["C"]="00";
    }
    else if(num1>num)
    {
        flags["Z"]="00";
        flags["C"]="00";
    }
    else
    {
        flags["Z"]="00";
        flags["C"]="01";
    }
    return true;
}


void executeanddisplay(string str)
{
    vector<string>token;
    string temp;
    stringstream ss(str);
    while(getline(ss,temp,' '))
    {
        token.push_back(temp);
    }
    string opcode=memory[token[0]];
    if(opcode=="MOV")
    {
        if(executemov(token)==false) 
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="MVI")
    {
        if(executemvi(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="LXI")
    {
        if(executelxi(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="LDA")
    {
        if(executelda(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="STA")
    {
        if(executesta(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="LHLD")
    {
        if(executelhld(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="SHLD")
    {
        if(executeshld(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="LDAX")
    {
        if(executeldax(token)==false) 
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="STAX")
    {
        if(executestax(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="XCHG")
    {
        if(executexchg(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ADD")
    {
        if(executeadd(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ADI")
    {
        if(executeadi(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ADC")
    {
        if(executeadc(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ACI")
    {
        if(executeaci(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="SUB")
    {
        if(executesub(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="SUI")
    {
        if(executesui(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="SBB")
    {
        if(executesbb(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="SBI")
    {
        if(executesbi(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="INR")
    {
        if(executeinr(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="DCR")
    {
        if(executedcr(token)==false) 
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="INX")
    {
        if(executeinx(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="DCX")
    {
        if(executedcx(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ANA")
    {
        if(executeana(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ANI")
    {
        if(executeani(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }

    else if(opcode=="XRA")
    {
        if(executexra(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="XRI")
    {
        if(executexri(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ORA")
    {
        if(executeora(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="ORI")
    {
        if(executeori(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="CMC")
    {
        if(executecmc(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="STC")
    {
        if(executestc(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="CMA")
    {
        if(executecma(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="LSL")
    {
        if(executelsl(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="LSR")
    {
        if(executelsr(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else if(opcode=="CMP")
    {
        if(executecmp(token)==false)
        {
            cout<<"Error During Running"<<endl;
            return;
        }
        display();
    }
    else
    {
        return;
    }
}

void execute()
{
    string str;
    // fout.open();
    ifstream finnew;
    finnew.open("test.txt");
    while(getline(finnew,str))
    {
        str=trim(str);
        executeanddisplay(str);
        customSleep(5);
    }
}



int main()
{

    // fin.open(name);

    registers["A"]="00";
    registers["B"]="00";
    registers["C"]="00";
    registers["D"]="00";
    registers["E"]="00";
    registers["H"]="00";
    registers["L"]="00";

    flags["S"]="00";
    flags["Z"]="00";
    flags["C"]="00";
    flags["AC"]="00";
    flags["P"]="00";
    // mymemory["FFEE"]="26";
    readFile();
    for(auto a:memory)
    {
        cout<<a.first<<' '<<a.second<<endl;
    }
    cout<<"----------Now Program is Executing----------"<<endl;
    execute();
    fout.close();
    cout<<"Succesfully Complied"<<endl;
    return 0;
}