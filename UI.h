#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<sstream>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;

class Bara
{
private:
    sf::Color culoare;
    sf::RectangleShape bara_score;
    sf::Text Nivel;
    sf::Text HighScore;
    sf::Font font;
    int Level=0;
    int LevelMax;

    sf::Clock durata;
    sf::Text Secunde;
    sf::Text Minute;
    int secundar=0,minutar=0;
    int timp_precedent=0;

    sf::Music soundtrack;
    sf::Texture VolumeUp;
    sf::Texture VolumeDown;
    sf::Sprite Volum;
    bool Canta=true;
    sf::Clock click;

    sf::Texture re;
    sf::Sprite Restart;

    sf::Text Nr_mingi;
    int Numar;

public:
    Bara();
    void CrestereNivel(int n){Level+=n; };
    int draw(sf::RenderWindow &);
    int GetLevel(){return Level; };
    int GetHS(){return LevelMax; };
    void Reincepe(){Level=0; durata.restart(); minutar=0;secundar=0; };
    int GetSecunde(){return secundar; };
    int GetMinutar(){return minutar; };
    void SetareNumar(int n){Numar=n; };
    void SetarePozitie(float ,float );
    void SetareSecunde(int, int);
    bool stop=false;
};

class Sfarsit
{
private:
    sf::Color culoare_background;
    sf::RectangleShape background;

    sf::Color culoare_buton;
    sf::RectangleShape buton;
    sf::Text text_buton;
    sf::Font font;

    sf::Text Scor;
    sf::Text HighScore;

    sf::Text Timp;

    sf::Text Mesaj;
    sf::Clock click;
public:
    Sfarsit();
    void Timp_Score(int ,int ,int ,int);
    int draw(sf::RenderWindow &);


};

class Pauza
{
private:
    sf::Font font;
    sf::Text text;

    sf::RectangleShape background;

    sf::RectangleShape resume;
    sf::Text text_resume;

    sf::RectangleShape replay;
    sf::Text text_replay;

    sf::Color culoare;
    sf::Color contur;

    sf::Clock click;
public:
    int draw(sf::RenderWindow &,bool );
    Pauza();

};
#endif // UI_H_INCLUDED
