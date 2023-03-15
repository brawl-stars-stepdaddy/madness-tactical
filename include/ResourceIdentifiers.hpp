#ifndef RESOURCE_IDENTIFIERS_HPP_
#define RESOURCE_IDENTIFIERS_HPP_

namespace sf {
    class Texture;
}

enum class TexturesID {
    SUN,
    DIRT,
    ENGINEER,
};

template <typename Resource, typename Identifier>
struct ResourceHolder;

typedef ResourceHolder<TexturesID, sf::Texture> TextureHolder;

#endif