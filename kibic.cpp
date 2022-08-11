#include "kibic.hpp"
#include "miasto.hpp"
#include <cmath>
#include <string>
#include <cstdlib>


using namespace std;

Kibic::Kibic(string klub){
  x = 25 * ((double)rand()/RAND_MAX); //losownaie współrzędnej x
  y = 25 * ((double)rand()/RAND_MAX); //losowanie współrzędnej y
  this ->klub = klub;
}


int Kibic::zadowolenie(vector<Kibic> & kibice, double r){
  int ziomki = 0; //kibice tego samego klubu
  int nieziomki = 0; //kibice przeciwnego klubu
  for(int i = 0; i < kibice.size(); i++){
    Kibic a;
    a = kibice.at(i);
    if(((x - a.get_x())*(x - a.get_x()) + (y - a.get_y())*(y - a.get_y())) <= r*r){ //sprawdzanie, czy i-ty kibic leży w promieniu r od kibica na rzecz którego wywołujemy tę funkcję
      if(klub == a.get_klub()){
        ziomki++;
      }
      else{
        nieziomki++;
      }
    }
  }
  return ziomki - nieziomki -1 ; //odejmujemy 1, bo dla każdego kibica poziom zadowolenia wynosi minimum jeden, gdyż on sam znajduje się w odpowiednim obszarze i kibicuje swojemu klubowi
}

void Kibic::przeprowadzka(double s){
  double z, w, losowa;
  z = this ->x;
  w = this ->y;
  x = z + s*(2*((double)rand()/RAND_MAX) - 1); //losowanie nowej współrzędnej x w przedziale [x-1,x+1]
  if(x > 25){ //zawracanie kibica, który chce przeprowadzić się poza miasto
    x = x - 25;
  }
  else if(x < 0){
    x = 25 + x;
  }
  losowa = (double)rand()/RAND_MAX; //ta liczba zapewni nam losowe wybranie y spośród 2 opcji, wyjaśnienie poniżej
  if(losowa <= 0.5){
    y = w + sqrt((z - x)*(z - x) + s); //dobieramy y tak, żeby dla wyliczonego wcześniej x wylądować na okręgu. Wystarczy wyliczyć y z równania odległości dwóch punktów
    if(y > 25){ //sprawdzenie, czy nie musimy zawrócić kibica, który chce się przeprowadzić poza miasto
      y = y - 25;
    }
    else if(y < 0){ //sprawdzenie, czy nie musimy zawrócić kibica, który chce się przeprowadzić poza miasto
      y = 25 + y;
    }
  }
  else{
    y = w - sqrt((z - x)*(z - x) + s); //drugie rozwiązanie y z równania
    if(y > 25){ //sprawdzenie, czy nie musimy zawrócić kibica, który chce się przeprowadzić poza miasto
      y = y - 25;
    }
    else if(y < 0){ //sprawdzenie, czy nie musimy zawrócić kibica, który chce się przeprowadzić poza miasto
      y = 25 + y;
    }
  }
}
