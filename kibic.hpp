#ifndef KIBIC_HPP
#define KIBIC_HPP
#include <string>
#include <vector>

using namespace std;
class Miasto;

class Kibic{
public:
  friend class Miasto;
  Kibic(double x1, double y1, string klub1){x = x1; y = y1; klub = klub1;} //konstruktor, który dla danych współrzędnych i klubu tworzy kibica o tych danych
  Kibic(){x = 0; y = 0; klub = "Legia";}
  Kibic(string klub); // konstruktor, który losuje współrzędne kibica i przypisuje go do klubu jak w argumencie
  int zadowolenie(vector<Kibic> & v, double r); // funckja licząca zadowolenie kibica w promieniu r
  void przeprowadzka(double s); // funkcja przeprowadzająca kibica
  double get_x(){return x;}
  double get_y(){return y;}
  string get_klub(){return klub;}
private:
  double x;
  double y;
  string klub;
};

#endif