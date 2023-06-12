#ifndef RESOURCE_IDENTIFIERS_HPP_
#define RESOURCE_IDENTIFIERS_HPP_

namespace sf {
class Texture;
class Font;
}

enum class TexturesID {
    SUN,
    DIRT,
    ENGINEER,
    BACKGROUND,
    HALO,
    MAP_TEXTURE,
    WORM,
    CANON_BALL,
    WEAPON_BOX,
    BAZOOKA,
};

enum class FontsID {

};

template <typename Resource, typename Identifier>
struct ResourceHolder;

using TextureHolder = ResourceHolder<TexturesID, sf::Texture>;
using FontHolder = ResourceHolder<FontsID, sf::Font>;

#endif