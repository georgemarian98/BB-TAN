#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED
#include"Forme.h"
#include"UI.h"
#include<math.h>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

vector<Patrat*> obstacol;
vector<Minge*> bila;
vector<PowerUp*> puteri;
Bara Score;


void Initializare()
{
    int k=0,s=0;
    while(k<=6)
    {
        int q=rand()%3+1;
        switch(q)
        {
            case 1:
            {
                int super;
                if(Score.GetLevel()%10==0)super=rand()%2+1;
                else super =1;
                Patrat *pi= new Patrat(50*k+5*(k+1),55,super,0);
                pi->SetViata(super*Score.GetLevel());
                obstacol.push_back(pi);
                k++;
                break;
            }
            case 2:
                k++;
                break;
            case 3:
                if(!s)
                {
                    PowerUp *newP= new PowerUp(50*k+30+5*k,80);
                    puteri.push_back(newP);
                    s++;
                    k++;
                }
                break;
        }
    }
}


int Resume(sf::RenderWindow &window)
{
    ifstream f("Resourses/Aranjare.txt");
    float size,x,y;
    f>>size>>x;
    Score.SetarePozitie(x+20,window.getSize().y-30);
    for(int i=0;i<size;i++)
    {
        Minge *newMinge= new Minge(window);
        newMinge->SetPosition(x,window.getSize().y-10);
        bila.push_back(newMinge);
    }

    float Nivel;
    f>>Nivel;
    Score.CrestereNivel(Nivel);

    f>>size;
    for(int i=0;i<size;i++)
    {
        f>>x>>y;
        PowerUp *newP= new PowerUp(x,y);
        puteri.push_back(newP);
    }

    f>>size;
    for(int i=0;i<size;i++)
    {
        float life,c,green;
        f>>x>>y>>life>>c>>green;
        Patrat *pi= new Patrat(x,y,c,green);
        pi->SetViata(life);
        pi->SetareViata((Nivel-(y/55)+2)*c);
        obstacol.push_back(pi);
    }
    int sec,h;
    f>>sec>>h;
    Score.SetareSecunde(sec,h);

    f.close();
    if(!size)return 0;
    else return 1;
}

void Restart(sf::RenderWindow &window)
{
    obstacol.erase(obstacol.begin(),obstacol.end());
    bila.erase(bila.begin()+1,bila.end());
    puteri.erase(puteri.begin(),puteri.end());
    bila[0]->SetPosition(window.getSize().x/2 ,window.getSize().y-15);
    Score.Reincepe();
}

#endif // FUNCTII_H_INCLUDED
