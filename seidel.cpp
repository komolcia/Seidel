#include<random>
#include<ctime>
#include<iostream>
#include<string>
#include<cmath>
const double eps = 1e-12;//to jest stała przybliżenia zera(to 1*10^-12)
using namespace std;
thread_local std::mt19937 gen{std::random_device{}()};
template<typename T> 
T random(T min, T max) {
    return std::uniform_int_distribution<T>{min, max}(gen);
}//randomowa funkcja
int randomowe=0;
string jakie="OK";//tutaj sprawdza czy ma rozwiązania
double *pomocnicza(double a[][10],double b[],double c[],int x,int n,char e[]){


double *tab=new double[x];
*(tab+0)=0;//tworzymy tablice w niej już wrzucamy przypadek gdy Z(0,0)
*(tab+0)=0;

double a1,a2,a3,a4,max=0,realmax=0;
//pierwszy przypadek polega na tym że szukamy najlepszego wyniku kiedy jest nieograniczenie w gaussie lub po prostu daje maksymalny OPT
a1=b[0]/a[0][0];//czyli np. dwie funkcje które się przecinają jednak jako że max-> -2x1-8x2 to wtedy najczesciej (0,0) było by maksymalnym OPT
a2=b[1]/a[1][0];//nie może być np.(0,-1) bo wtedy y>=0 się nie zgadza wiec to tez jest sprawdzane czy jest wieksze równe zero
a3=b[0]/a[0][1];
a4=b[1]/a[1][1];//tutaj sprawdzamy x0 i y0
if(a1<a2 && a1>=0) //tutaj kazdy po kolei jest porównywany i szukamy minratio czyli jesli a1=5 i a2=3 to wybieramy 3 bo jest najmniejszym czyli też najbliżej punktu 0,0
{
  max=c[0]*a1;//tu liczymy
  if(max>realmax){
   *(tab+0)=a1;
   *(tab+1)=0;
   realmax=max;}
}
if(a1>a2 && a2>=0)
{
  max=c[0]*a2;
  if(max>realmax){
   realmax=max;
   *(tab+1)=0;
   *(tab+0)=a2;

   }
}
if(a4<a3 && a4>=0)
{
  max=c[1]*a4;
  if(max>realmax){
  *(tab+1)=a4;
  *(tab+0)=0;
  realmax=max;}
}
else if(a3<a4 && a3>=0)
{
  max=c[1]*a3;
  if(max>realmax){
   *(tab+0)=0;
   *(tab+1)=a3;
   realmax=max;}
}
//nie do końca wiem czy te przypadki następne mają sens by je pisać ale są ukazane i program DZIALA!
if(a1<0){//tutaj są przypadki kiedy a1 by było mniejsze niż zero wtedy wybierane jest a2
if(a1<a2 && a2>=0)
{
  max=c[0]*a2;
  if(max>realmax){
   *(tab+1)=0; 
   *(tab+0)=a2;
   realmax=max;}
}
if(a1>a2 && a1>=0)
{
  max=c[0]*a1;
  if(max>realmax){
   realmax=max;
   *(tab+0)=a1;
  *(tab+1)=0;
   }
}
}
if(a3<0 ){
if(a4<a3 && a3>=0)
{
  max=c[1]*a3;
  if(max>realmax){
  *(tab+1)=a3;
  *(tab+0)=0;
  realmax=max;}
}
else if(a3<a4 && a4<0)
{
  max=c[1]*a4;
  if(max>realmax){
   *(tab+1)=a4;
   *(tab+0)=0;
   realmax=max;}
}}


//tutaj rozwiazujemy metodą gaussa
int i,j,k;
  double m, s;
double X[n];
a[0][2]=b[0];
a[1][2]=b[1];
  for(i=0;i<n-1;i++)
  {
    for(j=i+1;j<n;j++)
    {
      if(fabs(a[i][i])<eps) return tab;//wartosc bezwzgledna, tutaj zwracamy tablice(z wczesniejszych równań) jeśli jest niedopuszczalne rozwiazanie 
      m=-a[j][ i]/a[i][i];
      for( k=i + 1; k <= n;k++) a[j][k]+=m*a[i][k];
    }
  }

  // wyliczanie niewiadomych
for( i = n - 1; i >= 0;i--)
  {
    s=a[i][n];
    for( j = n-1;j >=i+1;j--)s-=a[i][j]*X[j];
    if(fabs(a[i][i])<eps) return tab;
    X[i]= s/a[i][i];
  }
   double v=X[0]*c[0]+X[1]*c[1];
cout<<endl<<"x"<<0<<"="<<X[0]<<endl<<"x"<<1<<"="<<X[1]<<endl;

  if(realmax<v)
  {
   *(tab+0)=X[0];
   
   *(tab+1)=X[1];//tu po prostu podstawiamy jesli zajdziemy tak daleko
   return tab;
  }
  else
  {
  return tab;
  }
}
double *Seidel(double a[][10],double b[],double c[],int x,int n,char e[])
{

double *tab=new double[x];

double max=0,realmax=0;
if(x==1){
for(int i=0;i<n;i++)
{
  max=c[0]*b[i]/a[i][0];
  if(realmax<max)
  {
    realmax=max;
    *(tab+0)=b[i]/a[i][0];//tutaj jesli mamy tylko jedną zmienna i przykład to max->2x i takie rownania 2x=4 i 3x=9 to x=3 i max->6 
  }
}
return tab;
}
if(x==n){//kiedy 2==2
double m1,m2,m3,m4;
m1=b[0]/a[0][0];
m2=b[0]/a[0][1];
m3=b[1]/a[1][0];
m4=b[1]/a[1][1];
if(m1>=0 && m2>=0 && m3>=0 && m4>=0)//tutaj znalazłam kilka sytuacji kiedy są rozwiązania a kiedy nie
{
tab=pomocnicza(a,b,c,x,n,e);//kiedy wszystkie są dodatnie to zawsze jest rozwiazanie
jakie="OK";
return tab;
} 
else if((m1<0 && m3<0) || (m2<0 && m4<0) || (m1<0 && m3<0 && m2<0 && m4<0))
{
jakie="Nie ma";// kiedy wszystkie miejsca zerowe są na minusie lub x1-dynki lub x2-ujki
*(tab+1)=1000;
*(tab+0)=1000;
return tab;//wtedy wyrzuca jakąkolwiek tablice bo może pózniej poprzez random znajdzie prawidłowy wynik

}
else if((m1>=0 && m3>=0 && m2<0 && m4<0) ||(m1<0 && m3<0 && m2>=0 && m4>=0) )
{
tab=pomocnicza(a,b,c,x,n,e);
jakie="OK";
return tab;//tutaj w sumie podobnie
}
else if(m1<0 || m3<0 || m2<0 || m4<0){
tab=pomocnicza(a,b,c,x,n,e);
jakie="OK"; //i jesli jeden z nich jest na minusie
return tab;
}
else
{
tab=pomocnicza(a,b,c,x,n,e);
jakie="OK";//i tutaj cokolwiek i tak wszystkie przypadki zostały przerobione
return tab;

}
}
srand(time(NULL)); 
int v=n-1;
randomowe=random(0,n-1);//tutaj wyszkuje randomowe ograniczenie

double f[10][10],g[n-1];
char o[n-1];
int h=0;
for(int i=0;i<n;i++)
{
 for(int j=0;j<x;j++)
 {
   if(i!=randomowe)
   {
      f[h][j]=a[i][j];
      g[h]=b[i];
      o[h]=e[i];
   }
 }
  if(i!=randomowe)
   {
      h++;//odejmuje te ograniczenie wrzucajac do nowych tablic to bez tego ograniczenia
   }

}
double *x1=new double[2];
x1=Seidel(f,g,c,x,n-1,o);//tu rekkurencyjnie az znajdzie
double wynik=0;

for(int i=0;i<2;i++)
{
wynik+=*(x1+i)*a[randomowe][i];//1*x+3*x
}
if((e[randomowe]=='<' && wynik<=b[randomowe]) || (e[randomowe]=='=' && wynik==b[randomowe]) )
{
cout<<"Jestem"<<randomowe<<endl;

  return x1;//jesli zgadza sie podstawienie pod to ograniczenie ktore usunelismy to wtedy zwracamy
}
else{
cout<<"Jestem"<<randomowe<<endl;
e[randomowe]='=';//tu jesli nie to musi być zamiast < to =
return Seidel(a,b,c,x,n,e);// i rekurencja
}

}
int main()
{
int x,n;
cout<<"Podaj ilosc zmiennych  macierzy(dziala w 2d wiec polecam 2 :D ): ";
cin>>x;
cout<<endl;
cout<<"Podaj ilosc ograniczen: ";
cin>>n;
cout<<endl;
char e[x];
double a[10][10],b[x],c[x];
for(int i=0;i<n;i<i++)
{
 for(int j=0;j<x;j++)
 {
     cout<<"["<<i<<","<<j <<"]=";
     cin>>a[i][j];
 }
}
for(int i=0;i<n;i++)
{
    cout<<"Po prawej ["<<i<<","<<n<<"]=";
    cin>>b[i];
    e[i]='<';
}
cout<<"\nPodaj c .\n";
for(int i=0;i<x;i++){
  cout<<"("<<i<<")=";
  cin>>c[i];
}
double *tab=Seidel(a,b,c,x,n,e);
double wynik=0;
wynik+=*(tab+1)*c[1];
wynik+=*(tab+0)*c[0];
if(jakie=="OK")
{
cout<<endl<<"x"<<0<<"="<<*(tab+0)<<endl<<"x"<<1<<"="<<*(tab+1)<<endl;

cout<<"OPT: "<<wynik<<"<-max"<<endl;
}
cout<<randomowe<<endl<<"Czy są rozwiązania?:"<<endl<<jakie<<endl;

return 0;
}
