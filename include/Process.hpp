#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <SFML/Graphics.hpp>

struct Process {
    virtual bool update(sf::Time) = 0;
};

#endif // PROCESS_HPP_
