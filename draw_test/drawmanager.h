#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <QMap>
#include <QVector>
#include <QPixmap>



class DrawManager {
public:
    static const int SPRITE_SIZE = 25;
    static const int FIELD_WIDTH = 625;

    enum FieldType {
        UNKNOWN,

        NON_WALKABLE,
        WALKABLE,
        USER1,
        USER2,
        USER3,
    };

    typedef QPair<QPoint, DrawManager::FieldType> tile_type;
    typedef QVector<tile_type> map_type;
    typedef QMap<FieldType, QPixmap> data_type ;

private:
    static data_type data_map;

public:
    static QPixmap& get_sprite_by_type(const FieldType &type);
    static FieldType get_type_by_char(const char &c);

    static void set_data_map(const data_type &new_data);
};

#endif // DRAWMANAGER_H
