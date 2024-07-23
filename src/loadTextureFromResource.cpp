#include "../include/loadTextureFromResource.hpp"
#if defined(_WIN32)
#include <windows.h>
#else
#include <fstream>
#endif
#include <spdlog/spdlog.h>

sf::Texture loadTextureFromResource(const std::string& resourcePath)
{
#if defined(_WIN32)
    int resourceId = std::stoi(resourcePath); // Assuming resourcePath is the resource ID as string on Windows
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

#else
    std::ifstream file(resourcePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        spdlog::error("Failed to open file: {}", resourcePath);
        return sf::Texture();
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        spdlog::error("Failed to read file: {}", resourcePath);
        return sf::Texture();
    }

    sf::Texture texture;
    if (!texture.loadFromMemory(buffer.data(), buffer.size())) {
        spdlog::error("Failed to load texture from memory");
        return sf::Texture();
    }

    return texture;
#endif
}
