#include<iostream>
 #include<stdlib.h>
 #include<cmath>
 #include <string>
 #include<sstream>
using namespace std;
class CryptoSuite
{
    public:
    long long p1,p2,e,d,n;
    CryptoSuite()
    {
    	p1=rPrime(5);
    	p2=rPrime(5);
    	n=p1*p2;
    	e=3;
    	d=invMod(e,((p1-1)*(p2-1)));
    }
    long long mExp(long long a,long long b,long long c)
   {
      long long ret=1;
      long long base=a;

       while(b>0)
       {

            if(b%2==1)
            ret=((ret)*(base))%c;
            base=((base)*(base))%c;
            b=b/2;
       }
       return ret;
   }
   long long gcd(long long a,long long b)
    {
        long long max,min;
        max=(a>=b)?a:b;
        min=(a<b)?a:b;
        if(max%min==0)
            return min;
        else
            return gcd(min,max%min);
    }
    long long mAdd(long long a,long long b,long long c)
  {
      return((a%c+b%c)%c);

  }
  long long mMult(long long a,long long b,long long c)
   {

       return(((a%c)*(b%c))%c);
   }
   bool isPrime(long long p)
   {
      bool prime=1;
      long long a=0;
      for(int i=1;i<=20;i++)
      {
        a=rand();
        if(gcd(a,p)!=1)
           {
               prime=0;
               break;
           }
        else
        {
            if(mExp(a,p-1,p)!=1)
            {
                prime=0;
                break;
        }


      }
   }
   return prime;
}
long long rPrime(int n)
{
    long long p=0;
    while(true)
    {
        p=0;
        for(int i=0;i<n;i++)
        p+=(rand()%10)*pow(10,i);
        if(isPrime(p)&&p%3!=1)
            break;
    }
    return p;
}
long long gcdExtended(long long a, long long b, long long &x, long long &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    long long x1, y1;
    long long gcd = gcdExtended(b%a, a, x1, y1);


    x = y1 - (b/a) * x1;
    y = x1;

    return gcd;
}
long long invMod(long long a,long long m)
{
    long long x=0,y=0;
    long long gcd=gcdExtended(a,m,x,y);
    if(gcd==1)
    {
    	if(x>0)
    	return (x%m);
    	else
    	return(m+x);
    }
}
long long encrypt(long long m)
    {
        return mExp(m,e,n);
    }
    long long decrypt(long long en)
    {
       return mExp(en,d,n);
    }
long long discLog(long long a,long long c,long long d){
    long long int m=sqrt(c);
    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            if(i==0&&j==0)continue;
            if(mExp(a,i*m,c)==((d%c)*mExp(invMod(a,c),j,c))%c)return (i*m+j);
        }
    }
}
string fAdd(string a, string b){
    string ans="";
    for(int i=0;i<8;i++){
        if(a[i]==b[i])ans+='0';
        else ans+='1';
    }
   return ans;
}
string fSub(string a,string b){
    return fAdd(a,b);
}
string fMul(string a, string b, string n) {
	string p = "000000000000000"; /* the product of the multiplication */
	for(int i=0;i<8;i++){
	    for(int j=0;j<8;j++){
	        int x=(int(p[i+j])+((int(a[i])-48)*(int(b[j])-48)))%2;
	        p[i+j]=x+'0';
	    }}
	for(int i=0;i<8;i++){
	    string part1="";
	    string part2=p.substr(i,8);
	    string part3="";
	    if(i!=0)part1=p.substr(0,i);
	    if(i!=7)
	    part3=p.substr(i+8,7-i);
	    if(p[i]=='0')continue;
	    else{
	    part2=fAdd(part2,n);
	    }
	    p=part1+part2+part3;

	}
	return p.substr(7,8);
	}
};
int main()
{
    int op;
    CryptoSuite cd;
    cout<<"Enter the appropriate number of the option you want"<<endl<<"1. Modular Arithmetic"<<endl<<"2. GCD"<<endl<<"3. Inverse Modulo"<<endl<<"4. RSA"<<endl<<"5. Field Operations "<<endl<<"6. Discrete Logarithm"<<endl;
	cin>>op;
	switch(op)
	{
	 case 1:
	 int a,b,c;
	 cout<<"Enter the appropriate operation"<<endl<<"1. Addition"<<endl<<"2. Subtraction"<<endl<<"3. Exponentiation"<<endl;
	 cin>>op;
	  switch(op){
	  case 1:
	  cout<<"Enter the three numbers";
	  cin>>a>>b>>c;
	  cout<<"The answer is "<<cd.mAdd(a,b,c);
	  break;
	  case 2:
	  cout<<"Enter the three numbers";
	  cin>>a>>b>>c;
	  cout<<"The answer is "<<cd.mMult(a,b,c);
	  break;
	  case 3:
	  cout<<"Enter the three numbers";
	  cin>>a>>b>>c;
	  cout<<"The answer is "<<cd.mExp(a,b,c);
	  break;
	  }
	  case 2:
	  int a2,b2;
	  cout<<"Enter the two numbers"<<endl;
	  cin>>a2>>b2;
	  cout<<"The answer is "<<cd.gcd(a2,b2);
	  break;
	  case 3:
	  int a3,b3;
	  cout<<"Enter the numbers "<<endl;
	  cin>>a3>>b3;
	  cout<<"The answer is "<<cd.invMod(a3,b3);
	  break;
	  case 4:
	  cout<<"Do you want us to encrypt/decrypt your message or do you want to enter your own encryption and decryption keys etc. Press 1/2"<<endl;
	  cin>>op;
	  switch (op)
	  {
	   case 1:
	   cout<<"Enter the number to be encrypted "<<endl;
	   long long msg;
	   cin>>msg;
	   long long m,n;
	   m=cd.encrypt(msg);
	   n=cd.decrypt(m);
	   cout<<"The encrypted number is "<<m<<endl;
	   cout<<"The decrypted number is "<<n<<" (for verification)"<<endl;
	   break;
	   case 2:
	   cout<<"Do you want to encrypt or decrypt? Press 1/2 \n"<<endl;
	   cin>>op;
	   switch(op)
	   {
	    case 1:
	    cout<<"Enter the two prime numbers and the message"<<endl;
	    long long p1,p2;
	    cin>>p1>>p2;
	    cin>>msg;
	    cout<<"Enter the encryption key"<<endl;
	    long long e;
	    cin>>e;
	    cout<<"The encrypted message is "<<cd.mExp(msg,e,(p1*p2));
	    break;
	    case 2:
	    cout<<"Enter the encrypted message and the 2 prime numbers."<<endl;
	    cin>>msg>>p1>>p2;
	    cout<<"Enter the decryption key";
	    cin>>e;
	    cout<<"The decrypted message is "<<cd.mExp(msg,e,p1*p2);
	    break;
	   }
	   break;

	  }
	  break;
	  case 6:
	  cout<<"Enter the numbers as base mod answer (using bsgs)"<<endl;
	  int a6,b6,d6;
	  cin>>a6>>b6>>d6;
	  cout<<"The answer is "<<cd.discLog(a6,b6,d6);
	  break;
	  case 5:
	  cout<<"1. Prime Field \n2. Binary Field \n";
	  cin>>op;
	  switch(op)
	  {
	   long long p1;
	   case 1:
	   cout<<"Enter the prime p"<<endl;
	   cin>>p1;
	   cout<<"1. Addition \n2. Subtraction \n3. Multiplication \n4. Inverse Calculation \n5. Division \n";
	   cin>>op;
	   if(op==1)
	   {
	    int add;
	    cout<<"Enter the two numbers\n";
	    cin>>a>>b;
	    cout<<"The answer is "<<cd.mAdd(a,b,p1);
	   }
	   if(op==2)
	   {
	    int add;
	    cout<<"Enter the two numbers\n";
	    cin>>a>>b;
	    cout<<"The answer is "<<cd.mAdd(a,-b,p1);
	   }
	   if(op==3)
	   {
	    int add;
	    cout<<"Enter the two numbers\n";
	    cin>>a>>b;
	    cout<<"The answer is "<<cd.mMult(a,b,p1);
	   }
	   if(op==4)
	   {
	    int add;
	    cout<<"Enter the number\n";
	    cin>>a;
	    cout<<"The answer is "<<cd.invMod(a,p1);
	   }
	   if(op==5)
	   {
	    int add;
	    cout<<"Enter the two numbers\n";
	    cin>>a>>b;
	    long long m=cd.invMod(b,p1);
	    cout<<"The answer is "<<cd.mMult(a,m,p1)<<endl;
	   }
	   break;
	   case 2:
	   string g1,g2;

	   cout<<"1. Add \n2. Subtraction \n3. Multiplication\n";
	   cin>>op;
	   switch(op)
	   {
	    case 1:
	    cout<<"Enter the coefficients of the polynomials in binary form with the two of them seperated by space\n";
	    cin>>g1>>g2;
	    cout<<"The answer is "<<cd.fAdd(g1,g2);
	    break;
	    case 2:
	    cout<<"Enter the coefficients of the polynomials in binary form with the two of them seperated by space\n";
	    cin>>g1>>g2;
	    cout<<"The answer is "<<cd.fSub(g1,g2);
	    break;
	    case 3:
	    cout<<"Enter the coefficients of the polynomials in binary form with the two of them seperated by space\n";
	    cin>>g1>>g2;
	    cout<<"1. Enter the irreducible polynomial\n2. Use our default polynomial\n";
	    cin>>op;
	    if(op==1)
	    {
	     string n;
	     cin>>n;
	     cout<<"The answer is "<<cd.fMul(g1,g2,n);
	    }
	    else
	    cout<<"The answer is "<<cd.fMul(g1,g2,"11000001");
	   }
	  }

	}
	return 0;
}
