#ifndef MIASTO_HPP
#define MIASTO_HPP
#include <vector>
#include <iostream>
#include <string>

using namespace std;
class Kibic;

class Miasto{
public:
  friend class Kibic;
  friend class rgb;
  Miasto(){}
  Miasto(int n, double p); //nieużywany przeze mnie konstruktor (ale wymieniony w wymaganiach) do tworzenia zaludnionego losowo miasta z odsetkiem kibiców Legii wynoszącym p
  void zaludnij(int n, double p); // funkcja zaludniająca miasto lososwo n mieszkańcami o p odsetku kibiców Legii
  void ewoluuj(double r); //funkcja ewoluująca miasto,gdzie poziom zadowolenia sprawdzany jest w promieniu r od kibica
  void zapisz_i_narysuj(); // funkcja uruchamiająca gnuplota
  double srednie_zadowolenie(double r); //funkcja liicząca średnie zadowolenie w promieniu r od każdego z kibiców
  void zaludnij_z_pliku(string dane); // funckja biorąca plik dane i zaludniająca kibicami z tego pliku miasto
  void narysuj(string plik, int m, double r); // funkcja tworząca obrazem o rozszerzeniu .ppm
private:
  vector<Kibic> mieszkancy; // prywatna składowa, która jest wektorem wszystkich kibiców
};

#endif
