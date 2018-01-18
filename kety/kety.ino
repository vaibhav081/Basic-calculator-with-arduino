#include <Keypad.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
double first = 0;
double second = 0;
double total = 0;

char customKey;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {0, 1, 6, 7}; 
byte colPins[COLS] = {8, 9, 10, 13}; 

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup(){
lcd.begin(16,2);
lcd.print("Start");
delay(1000);
lcd.clear();
}
void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey) 
  {
  case '0' ... '9': 
    lcd.setCursor(1,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;

  case '+':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("^1/3");
    total = cubicRoot(first);
    lcd.setCursor(10,2);
    lcd.print("=");
    lcd.setCursor(11,2);
    lcd.print(total);
    first = 0, second = 0; 
    break;

  case '-':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("^1/2");
    total = SqrtMethod(first);
    lcd.setCursor(10,2);
    lcd.print("=");
    lcd.setCursor(11,2);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '*':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("e^");
    total = exponential(first);
    lcd.setCursor(4,2);
    lcd.print("=");
    lcd.setCursor(5,2);
     lcd.print(total);
    first = 0, second = 0;
    break;

case '/':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("Log");
    //second = SecondNumber();
    total = Log2n(first);
    lcd.setCursor(6,2);
    lcd.print("=");
    lcd.setCursor(7,2);  
    lcd.print(total);
    first = 0, second = 0;
    break;

  case 'C':
    total = 0;
    lcd.clear();
    break;
  }
}

long SecondNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(1,2);
      lcd.print(second);
    }

    if(customKey == '=') break; 
  }
 return second; 
}



// Returns the absolute value of n-mid*mid*mid
double diff(double n,double mid)
{
    if (n > (mid*mid*mid))
        return (n-(mid*mid*mid));
    else
        return ((mid*mid*mid) - n);
}
 
// Returns cube root of a no n
double cubicRoot(double n)
{
    // Set start and end for binary search
    double start = 0, End = n;
 
    // Set precision
    double e = 0.0000001;
 
    while (true)
    {
        double mid = (start + End)/2;
        double error = diff(n, mid);
 
        // If error is less than e then mid is
        // our answer so return mid
        if (error <= e)
            return mid;
 
        // If mid*mid*mid is greater than n set
        // end = mid
        if ((mid*mid*mid) > n)
            End = mid;
 
        // If mid*mid*mid is less than n set
        // start = mid
        else
            start = mid;
    }
}



double SqrtMethod(double n)  //Binary search method
{
    double low=0,high=n,mid,precision=0.0001;
    if(n<1)
     {
          low = n;
          high = 1;
     }
    while(low<=high)
    {
        mid = (low+high)/2;
        if(precision >= mid*mid-n <= -precision)
            return mid;
        else if(mid*mid>n)
            high=mid-precision ;
        else
            low=mid+precision;
    }
    return (high+low)/2;
}




float exponential(float x)
{int n=100;
    float sum = 1.0f; // initialize sum of series
 
    for (int i = n - 1; i > 0; --i )
        sum = 1 + x * sum / i;
 
    return sum;
}
 


unsigned int Log2n(unsigned int n)
{
   return (n > 1)? 1 + Log2n(n/2): 0;
}


float power(int x, int y)
{
    if (y == 0)
        return 1;
    int temp=power(x,y/2);
    if(y%2==0)
      return temp*temp;
    else
        return x*temp*temp;
}


float Ssin(float x){
int i, j, n=2, fact, sign =  - 1;
  float p, sum = 0;

  //printf("Enter the value of x : ");
  //scanf("%f", &x);
  //printf("Enter the value of n : ");
  //scanf("%d", &n);

  for (i = 1; i <= n; i += 2)
  {
    p = 1;
    fact = 1;
    for (j = 1; j <= i; j++)
    {
      p = p * x;
      fact = fact * j;
    }
    sign =  - 1 * sign;
    sum += sign * p / fact;
  }
return sum;
  //printf("sin %0.2f = %f", x, sum);
}
/*void in()
{
lcd.print("Enter a");
lcd.setCursor(1,0);
delay(1000);
lcd.clear();
int c=customKeypad.getKey();
char dig=c;
lcd.print(dig);
for(int i=0;c!=42;i++)
{a[i]=c-48;
c=customKeypad.getKey();
}
lcd.print("Enter b");
//lcd.setCursor(1,0);
delay(100);
lcd.clear();
int d=customKeypad.getKey();
for(int i=0;d!=42;i++)
{b[i]=d-48;
d=customKeypad.getKey();
}
}
void add(int x[],int y[])
{int s[6];
for(int i=0;i<2;i++)
{s[i]=x[i]+y[i]+48;
lcd.print(s[i]);}
  
  
}
void loop(){in();
add(a,b);}*/
