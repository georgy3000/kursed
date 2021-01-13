#include "drawmanager.h"

DrawManager::data_type DrawManager::data_map = {};

QPixmap &DrawManager::get_sprite_by_type(const DrawManager::FieldType &type) {
    return DrawManager::data_map[type];
}

DrawManager::FieldType DrawManager::get_type_by_char(const char &c) {
    auto t = UNKNOWN;
    switch (c) {
        case 'x':
            t = NON_WALKABLE;
            break;
        case ' ':
            t = WALKABLE;
            break;
        case 's':
            t = USER1;
            break;
        case 't':
            t = USER2;
            break;
        case 'c':
            t = USER3;
            break;
        default:
            throw std::runtime_error("Unknown tile type");
    }
    return t;
}

void DrawManager::set_data_map(const data_type &new_data) {
    data_map.clear();
    data_map.insert(new_data);
}
