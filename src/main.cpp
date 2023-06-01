#include "lib/lib.hpp"

sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
sf::Event event;
sf::View view;

bool full = true;

void input()
{
    if (event.type == sf::Event::Closed) window.close();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::X)
        {
            if (!full) window.create(sf::VideoMode().getDesktopMode(), "My Game", sf::Style::Fullscreen);
            else window.create(sf::VideoMode(1024, 728), "My Game", sf::Style::Default);
            full = 1 - full;
            window.setFramerateLimit(100);
            view.setSize(window.getSize().x/2, window.getSize().y/2);
        }
    }

    if (event.type == sf::Event::Resized)
    {
        view.setSize(event.size.width/2, event.size.height/2);
    }
}

int main()
{
    bool kanan;
    bool move = 0;

    float jump = 0;

    bool moveJump;

    window.setFramerateLimit(100);

    sf::Texture txt_knight;
    int frame = 0;

    sf::RectangleShape box(sf::Vector2f(1720, 1080));
    box.setOrigin(box.getSize().x/2, box.getSize().y/2);

    sf::Sprite spr_knight;

    ImageStorage Knight_run;
    ImageStorage Knight_idle;
    ImageStorage Knight_jump;
    ImageStorage Knight_fall;

    sf::Texture bg;
    bg.loadFromFile("Sprite/BG/bg.gif");

    sf::Sprite background;

    background.setTexture(bg);
    background.setTextureRect(sf::IntRect(0, 200, 1920, 1080));
    background.setOrigin(bg.getSize().x/2, bg.getSize().y/2);

    

    Knight_idle.load("Idle", 10);
    Knight_run.load("Run", 10, "Sprite/Knight");
    Knight_jump.load("Jump", 3, "Sprite/Knight");
    Knight_fall.load("Fall", 3, "Sprite/Knight");

    txt_knight.loadFromImage(Knight_idle.getImg(0));
    spr_knight.setTexture(txt_knight);

    spr_knight.setOrigin(55, 80);
    spr_knight.setScale(3,3);
    spr_knight.setPosition(100, 400);

    box.setPosition(spr_knight.getPosition());

    view.setCenter(spr_knight.getPosition().x, spr_knight.getPosition().y);
    view.setSize(window.getSize().x/2, window.getSize().y/2);

    
    background.setPosition(sf::Vector2f(view.getCenter()));
    background.move(0, 240);

    box.setPosition(background.getPosition());
    box.move(0, -580);

    sf::Color col;
    col.Black;
    col.a = 150;

    box.setFillColor(col);

    while (window.isOpen())
    {
        spr_knight.setScale(3,3);

        frame++;
        if (frame > 59) frame = 0;

        if (spr_knight.getPosition().y < 600) jump -= 0.1;

        if (spr_knight.getPosition().y >= 600) 
        {
            moveJump = 0;
            jump = 0;
        }
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::KeyReleased)
            {
                if ((event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) && jump == 0)
                {
                    if (move) moveJump = true;
                    move = false;
                    frame = 0;
                    jump = 5;
                    // std::cout<<spr_knight.getPosition().y<<std::endl;
                }
            }
            input();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            {
                if (!move)
                {
                    frame = 0;
                    move = true;
                }
                
                kanan = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (!move)
                {
                    frame = 0;
                    move = true;
                }
                kanan = false;
            }
            else 
            {
                move = false;
            }
            

        }

        spr_knight.move(sf::Vector2f(0, jump * -1));
        
        if (move) txt_knight.update(Knight_run.getImg(frame));
        else txt_knight.update(Knight_idle.getImg(frame));

        if (jump > 0) txt_knight.update(Knight_jump.getImg(frame));
        else if (jump < 0) txt_knight.update(Knight_fall.getImg(frame));

        if (kanan) spr_knight.scale(1, 1);
        else spr_knight.scale(-1, 1);

        if (( move || moveJump ) && kanan) spr_knight.move(2,0);

        else if (( move || moveJump )) spr_knight.move(-2, 0);

        view.setCenter(spr_knight.getPosition().x, view.getCenter().y);

        window.setView(view);
        window.clear(sf::Color::Black);\

        window.draw(background);
        window.draw(box);
        window.draw(spr_knight);
        window.display();
    }


    return 0;
}