#include"UI.h"


string Incrementare(int &i)
{
    string Result;
    ostringstream convert;
    convert <<i;
    Result = convert.str();
    return Result;
}


Bara::Bara()
{
    //Font
     font.loadFromFile("Resourses/simboluri.otf");
     culoare.r=102;
     culoare.g=255;
     culoare.b=178;

     //Nivel
     Nivel.setFont(font);
     Nivel.setCharacterSize(40);
     Nivel.setPosition(265,-1);
     Nivel.setColor(culoare);

     //Level Maxim
     HighScore.setFont(font);
     HighScore.setCharacterSize(40);
     HighScore.setPosition(330,-1);
     HighScore.setColor(culoare);

     //Bara De Scor
     bara_score.setSize(sf::Vector2f(386,50));
     bara_score.setFillColor(sf::Color::Black);
     bara_score.setOutlineColor(sf::Color::Cyan);
     bara_score.setOutlineThickness(2);
     bara_score.setPosition(2,0);

     //Timpul
     Secunde.setFont(font);
     Secunde.setCharacterSize(40);
     Secunde.setPosition(210,-1);
     Secunde.setColor(culoare);

     Minute.setFont(font);
     Minute.setCharacterSize(40);
     Minute.setPosition(150,-1);
     Minute.setColor(culoare);

     //Muzica
     soundtrack.openFromFile("Resourses/MuzicaFundal.ogg");
     soundtrack.play();
     soundtrack.setLoop(true);
     soundtrack.setVolume(75);

     //Volum
     VolumeDown.loadFromFile("Resourses/VolumeDown.png");
     VolumeUp.loadFromFile("Resourses/VolumeUp.png");
     Volum.setTexture(VolumeUp);
     Volum.setPosition(10,10);
     Volum.setScale(0.1,0.1);

     //Restart
     re.loadFromFile("Resourses/Restart.png");
     Restart.setTexture(re);
     Restart.setScale(0.1,0.1);
     Restart.setPosition(70,10);

     //Numar mingi
     Nr_mingi.setFont(font);
     Nr_mingi.setCharacterSize(20);
     Nr_mingi.setOrigin(Nr_mingi.getPosition().x,Nr_mingi.getPosition().y+10);

};
int Bara::draw(sf::RenderWindow &window)
 {

      sf::Vector2i localPosition = sf::Mouse::getPosition(window);

      Nr_mingi.setString("x" + Incrementare(Numar));
      if(!Numar)Nr_mingi.setColor(sf::Color::Transparent);
      else Nr_mingi.setColor(sf::Color::White);

     //VOLUM
     if(Volum.getGlobalBounds().contains(localPosition.x,localPosition.y) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        click.getElapsedTime().asSeconds() > 0.5)
    {
        if(Canta)
        {
            Volum.setTexture(VolumeDown);
            Volum.setPosition(10,10);
            Canta=false;
            soundtrack.pause();
            click.restart();
        }
        else
        {
            Volum.setTexture(VolumeUp);
            Volum.setPosition(10,10);
            Canta=true;
            soundtrack.play();
            click.restart();
        }
    }

    //Restart
    if(Restart.getGlobalBounds().contains(localPosition.x,localPosition.y) &&
       sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        click.getElapsedTime().asSeconds() > 0.5)
    {
        click.restart();
        return 1;
    }

     //CEAS

     if(timp_precedent!=(int)durata.getElapsedTime().asSeconds() && !stop){
            timp_precedent=durata.getElapsedTime().asSeconds();
            secundar++;
     }


     if(secundar==60)
     {
         secundar=0;
         ++minutar;
         durata.restart();
     }
     if(secundar<10)Secunde.setString("0"+Incrementare(secundar));
     else Secunde.setString(Incrementare(secundar));
     if(minutar<10)Minute.setString("0"+Incrementare(minutar)+ " : ");
     else Minute.setString(Incrementare(minutar)+ " : ");

     if(Level>LevelMax)LevelMax=Level;

     HighScore.setString(Incrementare(LevelMax));
     Nivel.setString(Incrementare(Level));

     //DRAW
     window.draw(bara_score);
     window.draw(Nivel);
     window.draw(HighScore);
     window.draw(Minute);
     window.draw(Secunde);
     window.draw(Volum);
     window.draw(Restart);
     window.draw(Nr_mingi);

     return 0;
 };

void Bara::SetarePozitie(float x,float y)
{
    if(x+30>360)x-=30;
    Nr_mingi.setPosition(x,y);
};

void Bara::SetareSecunde(int timp,int Hs)
{
    minutar=timp/60;
    secundar=timp%60;
    LevelMax=Hs;
};
 Sfarsit::Sfarsit()
 {
     //Culoare
     culoare_background.r=204;
     culoare_background.g=255;
     culoare_background.b=153;

     culoare_buton.r=102;
     culoare_buton.g=178;
     culoare_buton.b=255;

     //Background
     background.setSize(sf::Vector2f(300,450));
     background.setPosition(40,50);
     background.setFillColor(culoare_background);
     background.setOutlineColor(sf::Color::Blue);
     background.setOutlineThickness(5);

     //Buton
     buton.setSize(sf::Vector2f(175,60));
     buton.setPosition(background.getPosition().x+70,background.getPosition().y+340);
     buton.setFillColor(culoare_buton);

     font.loadFromFile("Resourses/simboluri.otf");
     text_buton.setFont(font);
     text_buton.setCharacterSize(30);
     text_buton.setColor(sf::Color::Black);
     text_buton.setPosition(buton.getPosition().x+10,buton.getPosition().y+10);
     text_buton.setString("Joaca din nou!");

     //Scor
     Scor.setFont(font);
     Scor.setCharacterSize(50);
     Scor.setColor(sf::Color::Black);
     Scor.setPosition(background.getPosition().x+5,background.getPosition().y+100);

     HighScore.setFont(font);
     HighScore.setCharacterSize(50);
     HighScore.setColor(sf::Color::Black);
     HighScore.setPosition(background.getPosition().x+5,background.getPosition().y+160);

     //Timp

     Timp.setFont(font);
     Timp.setCharacterSize(50);
     Timp.setColor(sf::Color::Black);
     Timp.setPosition(background.getPosition().x+5,background.getPosition().y+210);

     //Mesaj

     Mesaj.setFont(font);
     Mesaj.setCharacterSize(70);
     Mesaj.setColor(sf::Color::Black);
     Mesaj.setString("Ai Pierdut!");
     Mesaj.setPosition(background.getPosition().x+10,background.getPosition().y+10);



 };

int Sfarsit::draw(sf::RenderWindow &window)
 {
     sf::Vector2i localPosition = sf::Mouse::getPosition(window);

     if(buton.getGlobalBounds().contains(localPosition.x,localPosition.y) &&
        sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        click.getElapsedTime().asSeconds()>0.5 )
     {
         click.restart();
         return 1;
     }

     window.draw(background);
     window.draw(buton);
     window.draw(text_buton);
     window.draw(Scor);
     window.draw(HighScore);
     window.draw(Timp);
     window.draw(Mesaj);

     return 0;
 }

 void Sfarsit::Timp_Score(int secunde, int minute, int nivel, int HS)
 {
     if(minute)Timp.setString("Timp: " + Incrementare(minute) + " : " + Incrementare(secunde));
     else Timp.setString("Timp: "  + Incrementare(secunde));
     Scor.setString("Score: "+ Incrementare(nivel));
     HighScore.setString("High Score: " + Incrementare(HS));
 };

 Pauza::Pauza()
 {
     //Culorii
     culoare.r=160;
     culoare.g=160;
     culoare.b=160;

     contur.r=96;
     contur.g=96;
     contur.b=96;

     //Background
     background.setSize(sf::Vector2f(300,450));
     background.setPosition(40,50);
     background.setFillColor(culoare);
     background.setOutlineColor(contur);
     background.setOutlineThickness(5);

     //Resume
     resume.setSize(sf::Vector2f(125,50));
     resume.setFillColor(contur);
     resume.setPosition(background.getPosition().x+25,background.getPosition().y+320);

     font.loadFromFile("Resourses/simboluri.otf");
     text_resume.setFont(font);
     text_resume.setCharacterSize(25);
     text_resume.setColor(sf::Color::Black);
     text_resume.setPosition(resume.getPosition().x+10,resume.getPosition().y+10);
     text_resume.setString("Resume");

     //Replay
     replay.setSize(sf::Vector2f(125,50));
     replay.setFillColor(contur);
     replay.setPosition(resume.getPosition().x+130,resume.getPosition().y);

     text_replay.setFont(font);
     text_replay.setCharacterSize(25);
     text_replay.setColor(sf::Color::Black);
     text_replay.setPosition(replay.getPosition().x+15,replay.getPosition().y+10);
     text_replay.setString("Replay");

     text.setFont(font);
     text.setCharacterSize(70);
     text.setColor(contur);
     text.setPosition(background.getPosition().x+50,background.getPosition().y+80);

 };

int Pauza::draw(sf::RenderWindow &window,bool mesaj)
{
    if(mesaj)
    {
        text.setString("BB-Tan 2");
        text.setPosition(background.getPosition().x+50,background.getPosition().y+80);
    }
    else
    {
        text.setString("Pause");
        text.setPosition(background.getPosition().x+90,background.getPosition().y+80);
    }

    sf::Vector2i localPosition = sf::Mouse::getPosition(window);

    if(resume.getGlobalBounds().contains(localPosition.x,localPosition.y) && click.getElapsedTime().asSeconds()>0.5
       && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        click.restart();
        return 1;
    }
    else if (replay.getGlobalBounds().contains(localPosition.x,localPosition.y) && click.getElapsedTime().asSeconds()>0.5 &&
             sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        click.restart();
        return 2;
    }

    window.draw(background);
    window.draw(text);
    window.draw(resume);
    window.draw(text_resume);
    window.draw(replay);
    window.draw(text_replay);

    return 0;
};
