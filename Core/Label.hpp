#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

enum {
    ALIGN_CENTER,
    ALIGN_RIGHT,
    ALIGN_LEFT
};

class Label {
protected:
    sf::Text text;
    unsigned int alignment;

    void adaptAlign();

public:
    Label(unsigned int alignment = ALIGN_LEFT);
    virtual ~Label();

    void modifyText(sf::String const& _text, sf::Color const& color = sf::Color::Black, unsigned int charSize = 36);
    void setAlign(unsigned int const align);
    void setPosition(float x, float y);
    void setFont(sf::Font const& font);

    sf::String getString() const;
    const sf::Color getColor() const;
    sf::FloatRect getSize() const;
    const sf::Vector2f getOrigin() const;
    const sf::Vector2f getPosition() const;

    void draw(sf::RenderWindow& window);
};

#endif // LABEL_HPP_INCLUDED
