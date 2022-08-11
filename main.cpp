#include "miasto.hpp"
#include "kibic.hpp"
#include "rgb.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <sstream>

using namespace std;

int main(){
  srand(time(0));
  Miasto m;

  cout << "W jaki sposób chcesz przeprowadzić symulację miasta?" << endl;
  cout << "1. Chcę wylosować mieszkańców." << endl;
  cout << "2. Chcę wczytać dane mieszkańców z pliku." << endl;
  double decyzja; // zmienna służąca sprawdzeniu, którą opcję wybrał użytkownik
  while(true){ //na wypadek, gdyby ktoś wpisał niepoprawną liczbę
    cin >> decyzja;
    if(decyzja != 1 && decyzja != 2){
      cout << "Podaj liczbę 1 lub 2." << endl;
    }
    else{
      break;
    }
  }

  if(decyzja == 1){ // jeśli użytkownik chce losować mieszkańców, to zostaną zadane dodatkowe pytania o szczegóły miasta
    cout << "Podaj liczbę mieszkańców miasta. " << endl;
    double n;
    cin >> n;
    while(true){ // sprawdzam, czy na pewno podano liczba
      if(n > 0 && int(n) - n == 0){
        break;
      }
      else{
        cout << "Podaj dodatnią liczbę całkowitą. " << endl;
        cin >> n;
        continue;
      }
    }

    double p;
    cout << "Jaką część wszystkich kibiców, mają stanowić kibice Legii?" << endl;
    while(true){ // sprawdzam, czy podano odpowiednią liczbę
      cin >> p;
      if(p >= 0 && p <= 1){
        break;
      }
      else{
        cout << "Podaj liczę z przedziału [0,1]." << endl;
      }
    }
    m.zaludnij(n, p); // zaludniamy mieszkańców dzięki podanym danym
  }

  else{ // jeśli użytkownik chce wczytać z pliku, to uruchomią się następujące instrukcje
    cout << "Podaj nazwę pliku, z którego chcesz wczytać dane kibiców." << endl;
    string plik;
    cin >> plik;
    m.zaludnij_z_pliku(plik);
  }

  cout << "Podaj ile lat ewolucji chcesz wygenerować. " << endl;
  double x;
  cin >> x;
  while(true){ // sprawdzam, czy na pewno podano dodatnią liczbę
    if(x >= 0  && int(x) - x == 0){
      break;
    }
    else{
      cout << "Podaj dodatnią liczbę całkowitą. " << endl;
      cin >> x;
    }
  }



  double R;
  cout << "Podaj promień, w którym ma być sprawdzany poziom zadowolenia kibica. " << endl;
  while(true){ // sprawdzam, czy na pewno podano dodatnią liczbę
    cin >> R;
    if(R > 0){
      break;
    }
    else{
      cout << "Podaj liczbę dodatnią " << endl;
    }
  }

  string plik;
  cout << "Podaj nazwę pliku, do którego ma być zapisywany obrazek z kibicami." << endl;
  cin >> plik;

  double M;
  cout << "Podaj ile pikseli wysokości i szerokości ma mieć obrazek." << endl;
  while(true){ // sprawdzam, czy na pewno podano dodatnią liczbę
    cin >> M;
    if(M > 0  && int(M) - M == 0){
      break;
    }
    else{
      cout << "Podaj dodatnią liczbę całkowitą. " << endl;
    }
  }

  double r;
  cout << "Podaj promień kółka, które ma reprezentować jednego kibica w pikslach." << endl;
  while(true){ // sprawdzam, czy na pewno podano dodatnią liczbę
    cin >> r;
    if(r > 0){
      break;
    }
    else{
      cout << "Podaj liczbę dodatnią. " << endl;
    }
  }

  cout << "Średni poziom zadowolenia w mieście przed ewolucją wynosi " << m.srednie_zadowolenie(R) << endl;
  int licznik = 1; // posłuży mi do zliczania co piątej ewolucji
  m.narysuj(plik + "_przed_ewolucją.ppm", M, r);
  for(int i = 1; i <= x; i++){
    m.ewoluuj(R);
    cout << "Dokonano " << i << ". ewolucji" << endl;
    cout << "Średni poziom zadowolenia wynosi " << m.srednie_zadowolenie(R) << endl;
    if(i % 5 == 0 || i == 1){ // rysunek narysuje się za pierwszym przejściem pętli, a potem co pięć przejść
      ostringstream numer; // dzięki temu w co piątej pętli będzie zapisywał się nowy rysunek o odpowiednim indeksie
      numer << licznik;
      string numer_obrazka = numer.str();
      m.narysuj(plik + numer_obrazka + ".ppm", M, r); // zapewniam wygodę użytkownikom, którzy zapominają o wpisaniu rozszerzenia .ppm
      licznik ++;
    }
}
  return 0;
}
