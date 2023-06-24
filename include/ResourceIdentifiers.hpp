#ifndef RESOURCE_IDENTIFIERS_HPP_
#define RESOURCE_IDENTIFIERS_HPP_

namespace sf {
class Texture;
class Font;
}  // namespace sf

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
    HEALING_BOX,
    BAZOOKA,
    GRENADE,
    TITLE,
    PLANET_CORE,
    LAND_MINE,
    LASER,
    CASE,
    KETTLEBELL,
    METEORITE
};

enum class FontsID {
    BAGEL_FONT,
    SANSATION,
};

template <typename Resource, typename Identifier>
struct ResourceHolder;

using TextureHolder = ResourceHolder<TexturesID, sf::Texture>;
using FontHolder = ResourceHolder<FontsID, sf::Font>;

using FontHolder = ResourceHolder<FontsID, sf::Font>;

#endif