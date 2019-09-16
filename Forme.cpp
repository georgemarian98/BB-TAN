#include"Forme.h"
#define Pi 3.14159265

string Scadere(int i)
{
    string Result;
    ostringstream convert;
    convert <<i;
    Result = convert.str();
    return Result;
}

Patrat::Patrat(float x, float y , short color,short g)
{
        rectangle.setPosition(x,y);
        if(color==1)culoare.r=255;
        else culoare.b=255;
        culoare.g=g;

        //Patrat
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setSize(sf::Vector2f(50,50));
        rectangle.setOutlineThickness(2);

        //Text
        font.loadFromFile("Resourses/text.ttf");
        text.setFont(font);
        text.setCharacterSize(20);


};
int Patrat::draw(sf::RenderWindow &window)
{
    rectangle.setOutlineColor(culoare);
    text.setColor(culoare);

    text.setString(Scadere(viata));
    text.setPosition(rectangle.getPosition().x+13,rectangle.getPosition().y+13);

    window.draw(rectangle);
    window.draw(text);

    if(rectangle.getPosition().y==window.getSize().y-55)return 1;
    return 0;
};

void Patrat::SetPosition(float x,float y)
{
    rectangle.setPosition(x,y);

};

void Patrat::Collision(Minge *m)
{
    if(rectangle.getGlobalBounds().intersects(m->GlobalBounds()) && rectangle.getPosition().y!=495)
    {

        if(m->GetPosition().y-m->getVitezaY()+10<=rectangle.getPosition().y)
        {
            m->SetPosition(m->GetPosition().x,m->GetPosition().y-5);
            m->SchimbaViteza(1,-1);
        }
        else if(m->GetPosition().x-m->getVitezaX()+10<=rectangle.getPosition().x)
             {
                m->SetPosition(m->GetPosition().x-5,m->GetPosition().y);
                m->SchimbaViteza(-1,1);
             }
             else if(m->GetPosition().y-m->getVitezaY()+10>=rectangle.getPosition().y+50)
             {
                 m->SetPosition(m->GetPosition().x,m->GetPosition().y+5);
                 m->SchimbaViteza(1,-1);
             }
                  else if(m->GetPosition().x-m->getVitezaX()+10>=rectangle.getPosition().x+50)
                  {
                      m->SetPosition(m->GetPosition().x+5,m->GetPosition().y);
                      m->SchimbaViteza(-1,1);
                  }
        viata--;
        culoare.g=255-((viata*255)/f);
    }
};

int Patrat::Destinatie()
{
    if(fmod(rectangle.getPosition().y,55)!=0)
    {
        rectangle.move(0,2.5);
        return 0;
    }else return 1;
};


void Patrat::ScriereFisier(ofstream &g)
{
    g<<rectangle.getPosition().x<<" "<<rectangle.getPosition().y<<" "<<viata<<" ";
    if(culoare.r==255)g<<1<<" ";
    else g<<2<<" ";
    g<<(int)culoare.g<<endl;
};

Minge::Minge(sf::RenderWindow &window)
{
    circle.setRadius(10);
    circle.setOrigin(circle.getGlobalBounds().width/2,circle.getGlobalBounds().height/2);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(window.getSize().x/2 ,window.getSize().y-10);
};
void Minge::draw(sf::RenderWindow &window)
{
    window.draw(circle);
}

void Minge::Movement(sf::RenderWindow &window)
{
    if(circle.getPosition().x>=window.getSize().x-10)
    {
        circle.setPosition(window.getSize().x-10,circle.getPosition().y);
        xVelocity*=-1;
    }
    if(circle.getPosition().x<=10)
    {
        circle.setPosition(10,circle.getPosition().y);
        xVelocity*=-1;
    }
    if(circle.getPosition().y<60)
    {
        circle.setPosition(circle.getPosition().x,60);
        yVelocity*=-1;
    }
    if(circle.getPosition().y>window.getSize().y-10  )
    {
        circle.setPosition(circle.getPosition().x,window.getSize().y-10);
        xVelocity=0;
        yVelocity=0;
    }
    circle.move(xVelocity,yVelocity);

};
void Minge::SetPosition(float x,float y)
{
    circle.setPosition(x,y);
};

void Minge::Viteza(float xVelocity,float yVelocity)
{
    this->xVelocity=xVelocity;
    this->yVelocity=yVelocity;
};

void Minge::Stop()
{
    xVelocity2=xVelocity;
    yVelocity2=yVelocity;
    xVelocity=0;
    yVelocity=0;
};
void Minge::Start()
{
    xVelocity=xVelocity2;
    yVelocity=yVelocity2;
}

void Minge::SchimbaViteza(int xVelocity,int yVelocity)
{
    this->xVelocity*=xVelocity;
    this->yVelocity*=yVelocity;
};

void Minge::Animatie(float x)
{
    if(circle.getPosition().x!=x)circle.move((x-circle.getPosition().x)*0.1,0);
};


PowerUp::PowerUp( float x, float y)
{
    circle.setRadius(10);
    circle.setFillColor(sf::Color::Black);
    circle.setOutlineColor(sf::Color::Yellow);
    circle.setOutlineThickness(2);
    circle.setOrigin(circle.getGlobalBounds().width/2,circle.getGlobalBounds().height/2);
    circle.setPosition(x,y);

    font.loadFromFile("Resourses/simboluri.otf");
    text.setString("+");
    text.setFont(font);
    text.setColor(sf::Color::Yellow);
    text.setCharacterSize(37);
};

void PowerUp::draw(sf::RenderWindow &window)
{
    window.draw(circle);
    text.setPosition(circle.getPosition().x-10,circle.getPosition().y-30);
    window.draw(text);
};

int PowerUp::Power(Minge *p)
{
    if(circle.getGlobalBounds().intersects(p->GlobalBounds()))return 0;
    return 1;
};

void PowerUp::SetPosition(float x, float y)
{
    circle.setPosition(x,y);
};

void PowerUp::Destinatie()
{
    if(fmod(circle.getPosition().y,55)!=25)circle.move(0,2.5);
}

