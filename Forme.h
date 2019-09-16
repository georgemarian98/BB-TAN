#ifndef FORME_H_INCLUDED
#define FORME_H_INCLUDED
#include<SFML/Graphics.hpp>
#include<sstream>
#include<string>
#include<iostream>
#include<math.h>
#include<fstream>
using namespace std;


class Minge
{
private:
    sf::CircleShape circle;
    float xVelocity=1;
    float yVelocity=1;
    float xVelocity2;
    float yVelocity2;

public:
    Minge(sf::RenderWindow &window);
    void SchimbaViteza(int,int);
    void draw(sf::RenderWindow &);
    void Movement(sf::RenderWindow &);
    void SetPosition(float ,float);
    void Viteza(float ,float);
    sf::FloatRect GlobalBounds(){return circle.getGlobalBounds(); };
    sf::Vector2f GetPosition(){return circle.getPosition(); };
    float getVitezaX(){return xVelocity;}
    float getVitezaY(){return yVelocity;}
    void Stop();
    void Start();
    void Animatie(float );
};



class Patrat
{
public:
    Patrat(float , float ,short ,short );
    int draw(sf::RenderWindow &);
    void SetPosition(float ,float );
    void Collision(Minge * );
    int GetViata(){return viata; };
    void SetViata(int viata){this->viata=viata; f=viata; }
    sf::Vector2f GetPosition(){return rectangle.getPosition(); };
    int Destinatie();
    void ScriereFisier(ofstream &);
    void SetareViata(int n){f=n;};

private:
    sf::RectangleShape rectangle;
    int  viata;
    int f;
    sf::Text text;
    sf::Font font;
    sf::Color culoare;
};

 class PowerUp
 {
 private:
    sf::CircleShape circle;
    sf::Text text;
    sf::Font font;
    int y;
 public:
    PowerUp(float ,float);
    int Power(Minge *);
    void draw(sf::RenderWindow &);
    void SetPosition(float , float );
    void Destinatie();
    sf::Vector2f GetPosition(){return circle.getPosition(); };
 } ;



#endif // FORME_H_INCLUDED
