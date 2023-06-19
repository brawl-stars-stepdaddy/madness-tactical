#ifndef MADNESS_TACTICAL_LABEL_HPP
#define MADNESS_TACTICAL_LABEL_HPP

#include "Component.hpp"
#include "ResourceIdentifiers.hpp"

namespace GUI {
    struct Label : Component {
    public:
        Label(const std::string &text, const FontHolder &fonts);

        virtual bool is_selectable() override;

        void set_text(const std::string &text);

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::Text m_text;
    };
}

#endif
