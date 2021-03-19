#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
struct String{
public:
int len=0;
char* p=nullptr;
public:
String(){cout<<"in default constructor"<<endl;}
~String() {cout<<"in destructor "<<endl; delete [] p;}
String(char* c){
cout<<"in conversion constructor "<<endl;
len=strlen(c);
p=new char(len+1);
memmove(p,c,len);
p[len]='\0';
}
String(const String& r){
cout<<"In copy constructor "<<endl;
len=r.len;
p=new char[r.len+1];
memmove(p,r.p,r.len+1);
}
String( String&& r){
cout<<"In copy move constructor "<<endl;
len=r.len;
p=r.p;
//cout<<p<<endl;
r.p=nullptr;
r.len=0;
}
String operator+(const String& r){
cout<<"In concatenate "<<endl;
char* t=new char[len+r.len+1];
memmove(t,p,r.len);
strcat(t,r.p);
t[len+r.len]='\0';
String result(t);
return result;
}
String& operator=(const String& r){
if(this==&r)
return *this;
cout<<"In assign "<<endl;
delete this->p;
len=r.len;
p=new char[r.len+1];
memmove(p,r.p,r.len+1);
return *this;
}
2
String&& operator=( String&& r){
cout<<"In move assign"<<endl;
delete [] p;
len=r.len;
p=r.p;
cout<<p<<endl;
r.p=nullptr;
r.len=0;
return move(*this); // we need move here because *this is an lvalue and the copy
// constructor would get called to create the return value
}
friend ostream& operator<<(ostream & os , const String r);
};
ostream& operator<<(ostream & os , const String r){
os<<r.p<<endl;
}
int main(){
String s("hello");
String v("by bye");
//v="by bye";
cout<<v.len<<endl;
cout<<s.len<<endl;
s=move(v);
cout<<v.len<<endl;
cout<<s.len<<endl;
//cout<<v.p<<endl;
String q(String("happy ")+String("birthday"));
String z;
cout<<q.len<<endl;
cout<<q.p<<endl;
z=String("happy ")+String("birthday");
cout<<z.len<<endl;
cout<<z.p<<endl;
}