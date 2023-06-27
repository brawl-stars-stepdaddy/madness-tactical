#ifndef RESOURCE_IDENTIFIERS_HPP_
#define RESOURCE_IDENTIFIERS_HPP_

namespace sf {
class Texture;
class Font;
}  // namespace sf

enum class TexturesID {
    BACKGROUND,
    MAP_TEXTURE,
    UNIT,
    CANON_BALL,
    WEAPON_BOX,
    HEALING_BOX,
    BAZOOKA,
    GRENADE,
    PLANET_CORE,
    LAND_MINE,
    LASER,
    CASE,
    KETTLEBELL,
    METEORITE,
    GAME_TITLE,
    AIM,
};

enum class FontsID {
    BAGEL_FONT,
    SANSATION
};

template <typename Resource, typename Identifier>
struct ResourceHolder;

using TextureHolder = ResourceHolder<TexturesID, sf::Texture>;

using FontHolder = ResourceHolder<FontsID, sf::Font>;

using FontHolder = ResourceHolder<FontsID, sf::Font>;

#endif // RESOURCE_IDENTIFIERS_HPP_