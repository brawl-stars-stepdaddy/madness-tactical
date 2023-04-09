#ifndef RESOURCE_IDENTIFIERS_HPP_
#define RESOURCE_IDENTIFIERS_HPP_

namespace sf {
class Texture;
}

enum class TexturesID {
    SUN,
    DIRT,
    ENGINEER,
    BACKGROUND,
    HALO,
    MAP_TEXTURE,
    WORM,
};

template <typename Resource, typename Identifier>
struct ResourceHolder;

using TextureHolder = ResourceHolder<TexturesID, sf::Texture>;

#endif