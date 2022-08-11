#include "miasto.hpp"
#include "kibic.hpp"
#include "rgb.hpp"
#include <vector>
#include <string>
#include <cmath>
#include <typeinfo>
#include <cstdlib>
#include <fstream>

using namespace std;


void Miasto::zaludnij(int n, double p){
  for(int i = 0; i < n*p; i++){
    Kibic k1("Legia");
    mieszkancy.push_back(k1);
  }
  for(int i = 0; i < n * (1 - p); i++){
    Kibic k2("Polonia");
    mieszkancy.push_back(k2);
  }
}

void Miasto::ewoluuj(double r){
  for(int i = 0; i < mieszkancy.size(); i++){
    Kibic a;
    a = mieszkancy.at(i);
    if(a.zadowolenie(mieszkancy, r) < 0){
      a.przeprowadzka(r);
      mieszkancy.at(i) = a;
    }
  }
}
//funkcja rysująca w gnuplot
void Miasto::zapisz_i_narysuj(){
  ofstream f1("legia.txt");
  ofstream f2("polonia.txt");
  for(int i=0; i < mieszkancy.size(); i++){
    if(mieszkancy.at(i).get_klub() == "Legia")
      f1 << mieszkancy.at(i).get_x() << " " << mieszkancy.at(i).get_y() << endl;
    if(mieszkancy.at(i).get_klub() == "Polonia"){
      f2 << mieszkancy.at(i).get_x() << " " << mieszkancy.at(i).get_y() << endl;
    }
  }
  f1.close();
  f2.close();
  ofstream rysunek("skrypt.gp");
  rysunek << "plot \"polonia.txt\" with points pointtype 7,\"legia.txt\" with points pointtype 7" << endl;
  rysunek << "pause -1 \"Wciśnij ENTER\"" << endl;
  system("gnuplot skrypt.gp");
}



double Miasto::srednie_zadowolenie(double r){
  double suma = 0;
  for(int i = 0; i < mieszkancy.size(); i++){ //w tej pętli dodajemy do siebie zadowolenie wszystkich kibiców
    Kibic a;
    a = mieszkancy.at(i);
    suma = suma + a.zadowolenie(mieszkancy, r);
  }
  return suma/mieszkancy.size();
}

Miasto::Miasto(int n, double p){
  zaludnij(n, p);
}

void Miasto::zaludnij_z_pliku(string plik){
  while(true){ // pętla wpisująca mieszkańców do wektora mieszkancy z klasy Miasto
  ifstream dane(plik.c_str());
  if(dane.fail()){ // sprawdzamy, czy plik istnieje
    cout << "Taki plik nie istnieje. Podaj poprawną nazwę" << endl;
    cin >> plik;
    continue;
  }
  while(true){ // wczytanie danych i sprawdzenie ich poprawności
    double x, y;
    string klub;
    dane >> x >> y >> klub;
    if(dane.fail()){ // skończy pracę wewnętrznej pętli, gdy plik się skończy
      break;
    }
    else if(x > 25 || x < 0){ // sprawdzenie, czy x jest w odpowienim zakresie
      cout << "Wczytana wartość x dla jednego z kibiców jest spoza zakresu [0,25]. Jakie działanie chcesz podjąć? Wpisz odpowiednią liczbę" << endl;
      cout << "1. Chcę podać z klawiatury nową wartość x" << endl;
      cout << "2. Chcę zignorować tego kibica" << endl;
      cout << "3. Chcę zakończyć działanie programu" << endl;
      int decyzja; // decyzja o dalszych akcjach
      cin >> decyzja;
      if(decyzja == 1){
        cout << "Podaj nową wartość x" << endl;
        while(true){
          cin >> x;
          if(x < 0 || x > 25){ // sprawdzamy, czy użytkownik podał wartość z odpowiedniego zakresu
            cout << "Podaj wartość z zakresu [0,25]" << endl;
            continue;
          }
          break;
        }
      }
      else if(decyzja == 2){
          continue;
      }
      else if(decyzja == 3){
        exit(EXIT_FAILURE);
      }
      }
      else if(y > 25 || y < 0){ // sprawdzenie, czy y jest w odpowiendim zakresie
        cout << "Wczytana wartość y dla jednego z kibiców jest spoza zakresu [0,25]. Jakie działanie chcesz podjąć? Wpisz odpowiednią liczbę" << endl;
        cout << "1. Chcę podać z klawiatury nową wartość y" << endl;
        cout << "2. Chcę zignorować tego kibica" << endl;
        cout << "3. Chcę zakończyć działanie programu" << endl;
        int decyzja; // decyzja o dlaszych działaniach
        cin >> decyzja;
        if(decyzja == 1){
          cout << "Podaj nową wartość y" << endl;
          while(true){
            cin >> y;
            if(y < 0 || y > 25){ // sprawdzamy, czy użytkownik podał wartość z odpowiedniego zakresu
              cout << "Podaj wartość z zakresu [0,25]" << endl;
              continue;
            }
            break;
          }
        }
        else if(decyzja == 2){
            continue;
        }
        else if(decyzja == 3){
          exit(EXIT_FAILURE);
        }
        }
        if(klub != "Legia" && klub != "Polonia"){ // sprawdzamy, czy nazwy klubu są prawidłowo zapisane w pliku
          cout << "Jeden z kibiców nie jest kibicem ani Legii ani Polonii. Jakie działanie chcesz podjąć? Wpisz odpowiednią liczbę" << endl;
          cout << "1. Chcę podać z klawiatury klub, któremu kibicuje ten kibic" << endl;
          cout << "2. Chcę zignorować tego kibica" << endl;
          cout << "3. Chcę zakończyć działanie programu" << endl;
          int decyzja; // decyzja o dlaszych działaniach
          cin >> decyzja;
          if(decyzja == 1){
            cout << "Podaj klub" << endl;
            while(true){
              cin >> klub;
              if(klub != "Legia" && klub != "Polonia"){ // sprawdzamy, czy użytkownik podał prawidłową nazwę
                cout << "Wybierz Legię lub Polonię" << endl;
                continue;
              }
              break;
            }
          }
          else if(decyzja == 2){
              continue;
          }
          else if(decyzja == 3){
            exit(EXIT_FAILURE);
          }
          }
          Kibic a(x, y, klub);
          mieszkancy.push_back(a); //wektor mieszkancy jest powiększony o kibica z jednej z linijek pliku tekstowego
      }
      break;
    }
}

void Miasto::narysuj(string plik, int M, double r){
  vector<rgb> v1(M,rgb(255,255,255)); // dzięki temu standardowo otrzymamy biały obrazek
  vector<vector<rgb>> v2(M,v1); //wektor wektorów, w którym będziemy składować dane o kolorach poszcegółnych pikseli na płaszczyźnie dwuwymiarowej
  for(int i = 0; i < mieszkancy.size(); i++){
    Kibic a;
    a = mieszkancy.at(i);
    int pozycja_x = round((a.get_x()/25) * M); // otrzymujemy współrzędną x piksla, w którym powinien znaleźć się kibic
    int pozycja_y = round((a.get_y()/25)*M); // otrzymujemy współrzędną y piksla, w którym powinien znaleźć się kibic
    for(int iy = pozycja_y - r; iy <= pozycja_y + r; iy++){
    for(int ix = pozycja_x - r; ix <= pozycja_x + r; ix++){
      if (((pozycja_x-ix) * (pozycja_x-ix) + (pozycja_y-iy) * (pozycja_y-iy) <= r * r) && ix < M && ix >= 0  && iy < M && iy >= 0){
        if(a.get_klub() == "Polonia"){
          v2.at(iy).at(ix).red(); //kolorujemy odpowiendie piksele na czerwono
        }
        else{
          v2.at(iy).at(ix).green(); // kolorujemy odpowiednie piksele na zielono
        }
      }
    }
  }
  }
  ofstream rysunek(plik.c_str()); //zapisywanie do pliku
  rysunek << "P3" << endl;
  rysunek << M << " " << M << endl;
  rysunek << "255" << endl;
  for(int iy = M - 1; iy >= 0; iy--){
    for(int ix = 0 ;ix < M; ix++){
      rysunek << v2.at(iy).at(ix).get_r() << " " << v2.at(iy).at(ix).get_g() << " " << v2.at(iy).at(ix).get_b() << endl;
    }
  }

  rysunek.close();

}
