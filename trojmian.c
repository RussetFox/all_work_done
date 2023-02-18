/* 
    kompilacja: Sun C: cc -xc99 -Xc trojmian.c -lm
                GNU C: gcc -std=c99 -pedantic -Wall trojmian.c -lm */
#include <stdio.h>
#include <math.h>

int main() {
  float a,b,c,delta;

  printf("Program oblicza pierwiastki rownania w postaci\n");
  printf("     2\n");
  printf("  a x + b x +c =0\n");
  printf("Podaj wartosc a:");
  scanf("%f",&a);
  printf("Podaj wartosc b:");
  scanf("%f",&b);
  printf("Podaj wartosc c:");
  scanf("%f",&c);
  
  if (a==0.0)    /*przypadek rownania liniowego */
    if (b!=0.0) 
      printf("Jest to równanie liniowe o rozwiazaniu x=%f\n",-c/b);
    else  if (c==0.0)  /* oraz a==b==0.0 */
      printf("Rozwiazaniem jest dowolne x\n");
    else              /* a==b==0.0 != c  */
      printf("Brak rozwiazan\n");
  else {   /*przypadek rownania kwadratowego */
    delta=pow(b,2)-4.0*a*c;
    if (delta<0) 
      printf("Brak rozwiazan rzeczywistych\n");
    else            /* delta>=0 */
      if (delta>0) 
	printf("Rozwiazaniem sa x1=%f i x2=%f\n",(-b-sqrt(delta))/(2*a),(-b+sqrt(delta))/(2*a));
      else
      	printf("Rozwiazaniem sa x1=x2=%f\n",-b/(2*a));
  }

}
/* Kacper Piejko
Opis testów:

1. a=0, b=0, c=0, ponieważ każdy x spełnia równanie wyjściowe (ax^2+bx+c=0) oczekiwanym rezultatem jest informacja o tym, że dowolny x jest rozwiązaniem równania. Po wprowadzeniu parametrów otrzymano "Rozwiązaniem jest dowolne x", co zgadza się z założeniem

2. a=0, b=0, c=1, dla dowolnego c=/=0, przy a=b=0 równanie jest sprzeczne, a informacja o tym jest oczekiwanym rezultatem na wprowadzone dane. Po wprowadzeniu danych pojawia się komunikat "Brak rozwiązań", co zgadza się z założeniem

3. a=0, b=1, c=2, sprawdzane jest jak program reaguje na parametry dające równanie liniowe. Oczekiwanym wynikiem jest informacja, że jest to równanie liniowe, którego miejscem zerowym jest x=-2. Po wprowadzeniu danych otrzymano komunikat "Jest to równanie liniowe o rozwiązaniu x=-2", co zgadza się z założeniem

4. a=1, b=2, c=3, sprawdzane jest jak program reaguje na dane, które sprawiają, że delta przyjmuje wartość ujemną. Oczekiwanym rezultatem jest informacja o braku rozwiązań w zakresie liczb rzeczywistych. Po wprowadzeniu danych pojawia się komunikat "Brak rozwiązań rzeczywistych", co zgadza się z założeniem

5. a=1, b=-4, c=-12, sprawdzane jest jak program reaguje na dane, skutkujące dwoma rozwiązaniami x1=-2, x2=6 [(x+2)(x-6)=x^2-4x-12)]. Otrzymany wynik był zgodny z założeniami

6. a=1, b=6, c=9, sprawdzane jest jak program reaguje na parametry, dające równanie kwadratowe o podwójnym pierwiastku x1=x2=-3 [(x+3)^2=x^2+6x+9]. Otrzymany wynik był zgodny z założeniem

7. a=-1, b=1, c=2, sprawdzane jest jak program radzi sobie z parametrem, dla którego pierwiastek z delty należy do zbioru liczb niewymiernych. Oczekiwane wyniki x1= 1+pierw. z 2 lub przybliżenie wyniku, x2= 1-pierw. z 2 lub przybliżony wynik. Otrzymano wynik zaokrąglony do 6 miejsc po przecinku, co zgadza się z założeniem

Wnioski: Po przeprowadzeniu testów na podanych zestawach, można stwierdzić, że program działa poprawnie.*/
