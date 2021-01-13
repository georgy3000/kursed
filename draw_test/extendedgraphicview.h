#ifndef EXTENDEDGRAPHICVIEW_H
#define EXTENDEDGRAPHICVIEW_H

#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include <QPoint>
#include <cmath>

#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>

#include "drawmanager.h"

class ExtendedGraphicView : public QGraphicsView {
Q_OBJECT

public:
    explicit ExtendedGraphicView(QWidget *parent=0);
    ~ExtendedGraphicView();

    void clear();
    void set_map(const DrawManager::map_type &map);

    void select_point(const QPoint &point);

    bool allowed_move_for(const QPoint &from, const QPoint &to);
    void perform_move(QPoint &from, QPoint &to);

    bool map_has_point(const QPoint &point);

private:
    QGraphicsScene *drawing_scene;
    QGraphicsItemGroup *drawing_layer;
    QGraphicsItemGroup *overlay_layer;

    DrawManager::map_type curr_map;

    void delete_group_items(QGraphicsItemGroup *group);

    static int round_to_multiple(int numToRound, int multiple);

    struct SelectedPoint {
        QPoint *point = nullptr;
        bool selected = false;
    } selected_point;

//    bool map_has_point(const QPoint &point);
    QVector<DrawManager::tile_type>::Iterator map_get_point(const QPoint &point);

public slots:
    void update();

private slots:
    void mousePressEvent(QMouseEvent * e);
};

#endif // EXTENDEDGRAPHICVIEW_H
