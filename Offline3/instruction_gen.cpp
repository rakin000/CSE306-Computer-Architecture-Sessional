#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mod 1000000007
#define pi acos(-1.0)

string lower(string s)
{
    string ret;

    for(auto c:s) ret += tolower(c);

    return ret;
}

vector<string> split(string x,char c)
{
    vector<string>v;

    string a;
    for(int i=0;i<x.size();i++)
    {
        if(x[i]==c)
        {
            v.push_back(a);
            a="";
        }
        else
        {
            a+=x[i];
        }
    }
    if(a.size()>0)
    {
        v.push_back(a);
    }
    return v;
}

string remove_ws(string x)
{
    string ans;
    for(int i=0;i<x.size();i++)
    {
        if(x[i]!=' ' && x[i]!=9)ans+=x[i];
    }
    return ans;
}

string convert_hex(int x)
{
    if(x<0)
    {
        x=16+x;
    }

    string p=to_string(x);
    if(p.size()==2)p='A'+(p[1]-'0');
    return p;
}

string convert_hex2(int x)
{
    string p;
    while(x>0)    
    {
        int z=x%16;
        if(z<10)p+='0'+z;
        else p+='A'+(z-10);
        x=x/16;
    }
    reverse(p.begin(),p.end());
    while(p.size()<2)p="0"+p;
    return p;
}

main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    string s;


    vector<string>insR = {"add"  , "sub"  , "and"  , "or"  , "nor"};
    vector<string>insI = {"addi" , "subi" , "andi" , "ori" , "sw"  , "lw"  , "beq" ,  "bneq"};

    vector<pair<int,string> >missing_label;
    map<string,string>map_reg;
    map<string,string>map_ins;
    map<string,int>map_label;
    vector<string>code;

    int ins_count=0;


    map_reg["$zero"] = "0";
    map_reg["$t0"]   = "1";
    map_reg["$t1"]   = "2";
    map_reg["$t2"]   = "3";
    map_reg["$t3"]   = "4";
    map_reg["$t4"]   = "5";
    map_reg["$sp"]   = "6";

    map_ins["add"]   = "0";
    map_ins["addi"]  = "C";
    map_ins["sub"]   = "7";
    map_ins["subi"]  = "B";
    map_ins["and"]   = "9";
    map_ins["andi"]  = "8";
    map_ins["or"]    = "5";
    map_ins["ori"]   = "3";
    map_ins["sll"]   = "1";
    map_ins["srl"]   = "E";
    map_ins["nor"]   = "F";
    map_ins["lw"]    = "A";
    map_ins["sw"]    = "4";
    map_ins["beq"]   = "D";
    map_ins["bneq"]  = "2";
    map_ins["j"]     = "6";


    while(cin>>s)
    {
         s=lower(s);
         if(s=="ex")break;

         if(find(insR.begin(),insR.end(),s)!=insR.end())
         {
             string x;
             getline(cin,x);
             x=remove_ws(x);
             vector<string> v=split(x,',');
             //cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[2].size()<<endl;
             string m;
             m=map_ins[s]+map_reg[v[1]]+map_reg[v[2]]+map_reg[v[0]];

             code.push_back(m);
         }
         else if(find(insI.begin(),insI.end(),s)!=insI.end())
         {
             if(s=="addi" || s=="subi" || s=="andi" || s=="ori")
             {
                 string x;
                 getline(cin,x);
                 //cout<<x<<endl;
                 x=remove_ws(x);
                 vector<string> v=split(x,',');

                 string m;

                 v[2]=convert_hex(stoi(v[2]));
                 //cout<<v[2]<<endl;
                 //if(v[2].size()==2)v[2]='A'+(v[2][1]-'0');
                 m=map_ins[s]+map_reg[v[1]]+map_reg[v[0]]+v[2];
                 code.push_back(m);
             }
             else if(s=="sw" || s=="lw")
             {
                 string x;
                 getline(cin,x);
                 //cout<<x<<endl;
                 x=remove_ws(x);
                 vector<string> v=split(x,',');
                 string v1,v2;
                 int a=0;
                 for(int j=0;j<v[1].size();j++)
                 {
                     if(a==0)
                     {
                         if(v[1][j]=='(')
                         {
                             a=1;continue;
                         }
                         v1+=v[1][j];
                     }
                     else if(a==1)
                     {
                        if(v[1][j]==')')
                         {
                             break;
                         }
                        v2+=v[1][j];
                     }
                 }
                 //cout<<v1<<" "<<v2<<endl;
                 string m;
                 if(v1.size()==2)v1='A'+(v1[1]-'0');
                 m=map_ins[s]+map_reg[v2]+map_reg[v[0]]+v1;
                 code.push_back(m);
             }
             else
             {
                 string x;
                 getline(cin,x);
                 //cout<<x<<endl;
                 x=remove_ws(x);
                 vector<string> v=split(x,',');

                 string m;
                 m=map_ins[s]+map_reg[v[0]]+map_reg[v[1]];
                 if(map_label.find(v[2])==map_label.end())
                 {
                    if(map_label[x]-v[2]-1>7 || map_label[x]-v[2]-1<-8)
                    {

                    }
                     missing_label.push_back({ins_count,v[2]});
                 }
                 else
                 {
                     if( map_label[v[2]]-ins_count-1 > 7 || map_label[v[2]]-ins_count-1 < -8 ) {
                        if( map_ins[s] == map_ins["beq"])
                        {
                            m=map_ins["bneq"];
                        }
                        else
                        {
                            m=map_ins["beq"];
                        }
                        m=m+map_reg[v[0]]+map_reg[v[1]]+"1";
                        code.push_back(m);
                        ins_count++;
                        m=map_ins[j];
                        m+=convert_hex2(map_label[v[2]])+"0";


                     }
                     else 
                        m+=convert_hex(map_label[v[2]]-ins_count-1);
                 }
                 code.push_back(m);
             }
         }
         else if(s=="sll" || s=="srl")
         {
             string x;
             getline(cin,x);
             x=remove_ws(x);
             vector<string> v=split(x,',');

             string m;
             if(v[2].size()==2)v[2]='A'+(v[2][1]-'0');
             m=map_ins[s]+map_reg[v[1]]+map_reg[v[0]]+v[2];
             code.push_back(m);
         }
         else if(s=="j")
         {
             string x;
             getline(cin,x);
             x=remove_ws(x);
             //cout<<x<<endl;
             //x.pop_back();

             string m=map_ins[s];
             if(map_label.find(x)==map_label.end())
                 {
                     missing_label.push_back({ins_count,x});
                 }
                 else
                 {
                     m+=convert_hex2(map_label[x]);
                     m+="0";
                 }
                 code.push_back(m);
         }
         else if(s=="push")
         {
             string x;
             getline(cin,x);
             x=remove_ws(x);

             code.push_back(map_ins["sw"]+map_reg["$sp"]+map_reg[x]+"0");
             code.push_back(map_ins["subi"]+map_reg["$sp"]+map_reg["$sp"]+"1");

             ins_count++;
         }
         else if(s=="pop")
         {
             string x;
             getline(cin,x);
             x=remove_ws(x);

             code.push_back(map_ins["addi"]+map_reg["$sp"]+map_reg["$sp"]+"1");
             code.push_back(map_ins["lw"]+map_reg["$sp"]+map_reg[x]+"0");
             ins_count++;
         }
         else
         {

             s.pop_back();
             map_label[s]=ins_count;

             continue;
         }

         ins_count++;
    }

    for(int i=0;i<missing_label.size();i++)
    {
        int c=missing_label[i].first;
        string x=missing_label[i].second;
        //cout<<map_ins["j"][0]<<" "<<code[c][0]<<endl;
        if(map_ins["j"][0]==code[c][0])
        {
            //cout<<x<<" "<<map_label[x]<<endl;
            code[c]+=convert_hex2(map_label[x]+1);
            code[c]+="0";
        }
        else
        {
            if(map_label[x]-c-1>7 || map_label[x]-c-1<-8)
            {
                string m;
                if( code[c][0] == map_ins["beq"][0])
                {
                    m=map_ins["bneq"];
                }
                else
                {
                    m=map_ins["beq"];
                }
                m=m+code[c][1]+code[c][2]+"1";
                code.push_back(m);
                ins_count++;
                m=map_ins[j];
                m+=convert_hex2(map_label[v[2]])+"0";
            }
            else
            {
                 code[c]+=convert_hex(map_label[x]-c-1);
            }            
        }
    }


    cout<<"v2.0 raw"<<endl;
    cout<<map_ins["addi"]<<map_reg["$zero"]<<map_reg["$sp"]<<"F ";
    for(int i=0;i<code.size();i++)
    {
        cout<<code[i]<<" ";
    }
}


/*
l1:
add $t0,$t1,$t2
beq $t1,$t2,l1
ex
*/
