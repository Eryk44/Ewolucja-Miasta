#ifndef RGB_HPP
#define RGB_HPP

//klasa, która posłuży mi do rysowania obrazka o rozszerzeniu .ppm
class rgb{
private:
  int r;
  int g;
  int b;
public:
  rgb(int r, int g, int b){this->r=r;this->g=g;this->b=b;}
  void red(){this->r=255;this->g=0;this->b=0;}
  void green(){this->r=0;this->g=255;this->b=0;}
  int get_r(){return r;}
  int get_g(){return g;}
  int get_b(){return b;}
};


#endif