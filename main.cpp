#include"Functii.h"


int main()
{
    srand(time(NULL));

    Pauza pause;
    Sfarsit panou_final;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(390,550), "BBTan 2", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    bool Start=Resume(window);

    bool Ok=false;
    int Trans=0;
    bool Piedut=false;
    int secunde=0,minute=0;
    bool TimeOut=false;
    sf::Clock delay;
    sf::Clock DelayLansare;
    int MingiLansate=0;
    int lansat=1;
    bool Bug=true;
    bool Primu=false;
    int indice=0;
    int MingiNoi=0;
    bool animatie_patrat=true;
    bool mesaj = true;

    while (window.isOpen())
    {

        int Termina=0;
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) )window.close();
            if (event.type == sf::Event::LostFocus || Start)
            {
                TimeOut=true;
                if(Start)mesaj=true;
                else mesaj=false;
                for(int i=0;i<bila.size();i++)bila[i]->Stop();
                Start=false;
            }
        }

        //window.clear();

        /** Movement */
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Ok  &&
           localPosition.y>50 &&
           localPosition.y<=window.getSize().y-50 &&
           localPosition.x>=0 &&
           localPosition.x<=window.getSize().x&&
           !TimeOut && animatie_patrat )
        {
            Ok=true;

            float angle=atan2(localPosition.y-bila[0]->GetPosition().y,localPosition.x-bila[0]->GetPosition().x);
            float x=7*cosf(angle);
            float y=7*sinf(angle);
            for(int i=0;i<bila.size();i++)bila[i]->Viteza(x,y);

            Trans=0;
            DelayLansare.restart();
            MingiLansate=0;
            lansat=1;
            Primu=false;
            indice=0;
        }

        //Miscarea Mingii
        if(Ok && !Piedut   && delay.getElapsedTime().asSeconds()>0.8)
        {
            if(DelayLansare.getElapsedTime().asSeconds()>0.1 && lansat<bila.size() && !TimeOut)
            {
                lansat++;
                DelayLansare.restart();
                MingiLansate++;
            }
            for(int i=0;i<lansat;i++)
             {
                bila[i]->Movement(window);
                if(!Primu && bila[i]->GetPosition().y>=window.getSize().y-10)
                    {
                        indice=i;
                        Primu=true;
                    }
             }
        }

        /** Sfarsit de Runda */
        for(int i=0;i<bila.size();i++)if(bila[i]->GetPosition().y>=window.getSize().y-15 )Termina++;
        if(Termina==bila.size())Ok=false;
        Score.SetareNumar(bila.size()-MingiLansate-1);

        if(!Ok && !Piedut && !TimeOut )
        {
            //Adaugare Patrate
            if(Trans==1 && !Start && delay.getElapsedTime().asSeconds()>1 || !Bug)
            {
                Bug=true;
                Score.CrestereNivel(1);
                Initializare();
                for(int i=0;i<obstacol.size();i++)
                    obstacol[i]->SetPosition(obstacol[i]->GetPosition().x,obstacol[i]->GetPosition().y+2.5);
                for(int i=0;i<puteri.size();i++)
                    puteri[i]->SetPosition(puteri[i]->GetPosition().x,puteri[i]->GetPosition().y+2.5);
            }
            for(int i=0;i<obstacol.size();i++)
                if(obstacol[i]->Destinatie())animatie_patrat=true;
                else animatie_patrat=false;
            for(int i=0;i<bila.size();i++)bila[i]->Animatie(bila[indice]->GetPosition().x);
            for(int i=0;i<puteri.size();i++)puteri[i]->Destinatie();

            Trans++;

            //Desenare Linie
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(bila[0]->GetPosition().x,bila[0]->GetPosition().y)),
                sf::Vertex(sf::Vector2f(localPosition.x, localPosition.y))

            };
            int a=255-3*Score.GetLevel();
            if(a<0)a=0;
            line[0].color.a=a;
            line[1].color.a=a;

            window.draw(line, 2, sf::Lines);

            while(MingiNoi)
            {
                Minge *newMinge= new Minge(window);
                newMinge->SetPosition(bila[indice]->GetPosition().x,window.getSize().y-10);
                bila.push_back(newMinge);
                MingiNoi--;
            }

            Score.SetareNumar(bila.size());
            Score.SetarePozitie(bila[0]->GetPosition().x+20,bila[0]->GetPosition().y-20);

            //Scriere in fisier
            ofstream g("Resourses/Aranjare.txt", ofstream::out | ofstream::trunc);
            g<<bila.size()<<" "<<bila[indice]->GetPosition().x<<endl;
            g<<Score.GetLevel()<<endl;
            g<<puteri.size()<<endl;
            for(int i=0;i<puteri.size();i++)g<<puteri[i]->GetPosition().x<<" "<<puteri[i]->GetPosition().y<<endl;
            g<<obstacol.size()<<endl;
            for(int i=0;i<obstacol.size();i++)obstacol[i]->ScriereFisier(g);
            g<<Score.GetMinutar()*60+Score.GetSecunde()<<endl;
            g<<Score.GetHS()<<endl;
            g.close();
        }

        /** Coliziune */
        for(int i=0;i<puteri.size();i++)
            for (int j=0;j<bila.size();j++)
                if(!puteri[i]->Power(bila[j]))
               {
                   puteri.erase(puteri.begin()+i);
                   MingiNoi++;
               }

        for(int i=0;i<obstacol.size();i++)
            for(int j=0;j<bila.size();j++)obstacol[i]->Collision(bila[j]);


        /** Draw */
        for(int i=0;i<bila.size();i++)bila[i]->draw(window);

        for(int i=0;i<puteri.size();i++)puteri[i]->draw(window);

        if(Score.draw(window))
        {
            //Buton Restart
            Restart(window);
            Ok=false;
            Trans=0;
            MingiNoi=0;
            indice=0;
        }

        for(int i=0;i<obstacol.size();i++)
        {
            if(obstacol[i]->GetViata()<=0)obstacol.erase(obstacol.begin()+i);
            //Pierdut joc
            if(obstacol[i]->draw(window))
            {
                Piedut=true;
                if(!secunde && !minute)
                {
                   secunde=Score.GetSecunde();
                   minute=Score.GetMinutar();
                }
                Score.stop=true;
                panou_final.Timp_Score(secunde,minute,Score.GetLevel(), Score.GetHS());
            }
        }

        //Sfarsit Joc
        if(Piedut)
        {
            if(panou_final.draw(window))
            {
                //Restart
                Restart(window);
                MingiNoi=0;
                Piedut=false;
                Ok=false;
                Trans=0;
                Score.stop=false;
                delay.restart();
                Bug=false;
                secunde=0;
                minute=0;
            }
        }

        //Nu mai ii in fereastra
        if(TimeOut)
        {
            switch(pause.draw(window,mesaj))
            {
            case 1:
                TimeOut=false;
                delay.restart();
                Score.stop=false;
                for(int i=0;i<bila.size();i++)bila[i]->Start();
                break;
            case 2:
                {
                Restart(window);
                MingiNoi=0;
                Ok=false;
                Trans=0;
                Score.stop=false;
                delay.restart();
                TimeOut=false;
                Bug=false;
                break;
                }

            default:
                Score.stop=true;
            }
        }

        window.display();
        window.clear();
    }

    //Eliberare Memorie
    for(int i=0;i<bila.size();i++)delete bila[i];
    for(int i=0;i<obstacol.size();i++)delete obstacol[i];
    for(int i=0;i<puteri.size();i++)delete puteri[i];

    return 0;
}
