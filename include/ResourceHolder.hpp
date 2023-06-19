#ifndef RESOURCE_HOLDER_HPP_
#define RESOURCE_HOLDER_HPP_

#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

template <typename Identifier, typename Resource>
struct ResourceHolder {
public:
    void load(Identifier id, const std::string &filename) {
        if (m_resource_map.find(id) != m_resource_map.end()) {
            return;
        }
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename)) {
            throw std::runtime_error(
                "ResourceHolder::load - failed to load " + filename
            );
        }
        insert_resource(id, std::move(resource));
    }

    template <typename Parameter>
    void load(
        Identifier id,
        const std::string &filename,
        const Parameter &second_parameter
    ) {
        std::unique_ptr<Resource> resource(new Resource());
        if (!resource->loadFromFile(filename, second_parameter)) {
            throw std::runtime_error(
                "ResourceHolder::load - failed to load " + filename
            );
        }
        insert_resource(id, std::move(resource));
    }

    Resource &get(Identifier id) {
        auto found = m_resource_map.find(id);
        assert(found != m_resource_map.end());
        return *(found->second);
    }

    const Resource &get(Identifier id) const {
        auto found = m_resource_map.find(id);
        assert(found != m_resource_map.end());
        return *(found->second);
    }

private:
    void insert_resource(Identifier id, std::unique_ptr<Resource> resource) {
        auto inserted = m_resource_map.insert({id, std::move(resource)});
        assert(inserted.second);
    }

    std::map<Identifier, std::unique_ptr<Resource>> m_resource_map;
};

#endif