#include "../include/loadTextureFromResource.hpp"
#include <windows.h>
#include <spdlog/spdlog.h>

sf::Texture loadTextureFromResource(int resourceId)
{
    HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(resourceId), "PNG");
    if (!hResource) {
        spdlog::error("Failed to find resource");
        return sf::Texture();
    }

    HGLOBAL hLoadedResource = LoadResource(NULL, hResource);
    if (!hLoadedResource) {
        spdlog::error("Failed to load resource");
        return sf::Texture();
    }

    LPVOID pLockedResource = LockResource(hLoadedResource);
    if (!pLockedResource) {
        spdlog::error("Failed to lock resource");
        return sf::Texture();
    }

    DWORD resourceSize = SizeofResource(NULL, hResource);
    if (resourceSize == 0) {
        spdlog::error("Invalid resource size");
        return sf::Texture();
    }

    sf::Texture texture;
    if (!texture.loadFromMemory(pLockedResource, resourceSize)) {
        spdlog::error("Failed to load texture from memory");
        return sf::Texture();
    }

    return texture;
}
