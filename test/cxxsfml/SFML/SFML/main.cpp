// Copyright (c) 2017 - Project Sunshine - Michael Moran

#include<cmath>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<string>
#include<sstream>

sf::Font font;
const int unit = 80; // 16*unit * 9*unit = 1280 * 720
class World;
class Player : public sf::Drawable {
  friend class World;
  float x, y;
  sf::Text text;
  sf::VertexArray c;
  void draw(sf::RenderTarget &target, sf::RenderStates states)const {
    target.draw(c, states);
    target.draw(text, states);
  }
public:                              //sf::LineStrip
   Player():x(unit*8.f),y(unit*4.5f), c(sf::LinesStrip, 6){
     c[0].position = sf::Vector2f(unit * 8.0f, unit * 4.5f);
     c[1].position = sf::Vector2f(unit * 8.0f, unit * 4.5f+unit/8);
     c[2].position = sf::Vector2f(unit * 8.0f, unit * 4.5f-unit/8);
     c[3].position = sf::Vector2f(unit * 8.0f, unit * 4.5f);
     c[4].position = sf::Vector2f(unit * 8.0f+unit/8, unit * 4.5f);
     c[5].position = sf::Vector2f(unit * 8.0f-unit/8, unit * 4.5f);
     text.setFont(font);
     text.setCharacterSize(unit / 4);
     text.setString("x, y"); 
     text.setPosition((unit*8.f), (unit*4.5f));
   }
   void update(float x, float y) {
     std::stringstream ss;
     this->x = x;
     this->y = y;
     ss << x << ", " << y;
     text.setString(ss.str());
   }
};
class World : public sf::Drawable{
  int len, wid;
  sf::VertexArray lines;
  Player pc;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(pc, states);
    target.draw(lines, states);
  }
  void update() {
    lines[0].position = sf::Vector2f(unit * 8.0f - pc.x,
      unit * 4.5f - pc.y);
    lines[0].color = sf::Color::Red;
    lines[1].position = sf::Vector2f(unit * 8.0f - pc.x,
      unit * 4.5f - pc.y + len);
    lines[1].color = sf::Color::Blue;
    lines[2].position = sf::Vector2f(unit * 8.0f - pc.x + wid,
      unit * 4.5f - pc.y + len);
    lines[2].color=sf::Color::Green;
    lines[3].position = sf::Vector2f(unit * 8.0f - pc.x + wid,
      unit * 4.5f - pc.y);
    lines[3].color = sf::Color::Yellow;
    lines[4].position = sf::Vector2f(unit * 8.0f - pc.x,
      unit * 4.5f - pc.y);
    lines[4].color = sf::Color::Red;

  }
public:
   World(int width, int length) :len(length), wid(width),
     lines(sf::LinesStrip, 5), pc() { // LineStrip
     update();
   }
   void move(float unit, float angle) {
     pc.update(pc.x + unit*cos(angle), pc.y + unit*sin(angle));
     update();
   }
   bool bounds(float unit, float angle){
     return pc.x - unit * .5 + unit * 1.5 * cos(angle) > 0 &&
            pc.x + unit * .5 + unit * 1.5 * cos(angle) < wid &&
            pc.y - unit * .5 + unit * 1.5 * sin(angle) > 0 &&
            pc.y + unit * .5 + unit * 1.5 * sin(angle) < len;
   }
};
std::string ichar(unsigned rate) {
  std::string d;
  do {
    d.insert(0, 1, rate % 10 + '0');
  } while (rate /= 10);
  return d;
}
int main(int argc, char*argv[]) {
  World world(1600,900);
  sf::RenderWindow  window(sf::VideoMode(16*unit, 9*unit), "Project Sunshine");
  sf::Text text;
  sf::Clock clock;
  unsigned frame = 16000;
  double angle;
  //window.setVerticalSyncEnabled(true);
  if (!font.loadFromFile("arial.ttf"))
  {
    return 1;
  }
  text.setFont(font);
  text.setCharacterSize(unit/4);
  text.setColor(sf::Color::Yellow);
  while (	window.isOpen() ) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
      }
    }
    angle = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
          sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
          angle = 1.570796327;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || 
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (angle > 0) angle = -1;  // oops...
            else angle = 4.71238898;
        }
      } else { // Just   >   was pressed not <
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
              sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            angle = 0;
          } else { angle = 5.497787144; }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
              sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            angle = 0.785398163;
        else  angle = 0;
      }
    } else  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          angle = 2.35619449;
        } else {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
              sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            angle = 3.926990817;
          else angle = 3.141592654;
       }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        angle = 1.570796327;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
               sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
      angle = 4.71238898;
    }
      //   0  >  0
      //  30     0.523598776
      //  45  J  0.785398163
      //  60     1.047197551
      //  90  v  1.570796327
      // 120     2.094395102
      // 135  L  2.35619449
      // 150     2.617993878
      // 180  <  3.141592654
      // 210     3.665191429
      // 225  F  3.926990817
      // 240     4.188790205
      // 270  ^  4.71238898
      // 300     5.235987756
      // 315  7  5.497787144
      // 330     5.759586532
      // 360  >  6.283185307
    if(angle >= 0 && world.bounds(frame / 1600.0, angle))
      world.move(frame / 1600.0, angle);
    text.setString(ichar(1000000.0 / frame));
    window.clear();
    window.draw(world);
    window.draw(text);
    window.display();
    frame = clock.restart().asMicroseconds();
  }
  return 0;
}
