#include "extendedgraphicview.h"

ExtendedGraphicView::ExtendedGraphicView(QWidget *parent) : QGraphicsView(parent) {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumHeight(DrawManager::FIELD_WIDTH);
    this->setMinimumWidth(DrawManager::FIELD_WIDTH);

    this->drawing_scene = new QGraphicsScene();
    this->setScene(this->drawing_scene);

    this->drawing_layer = new QGraphicsItemGroup();
    this->overlay_layer = new QGraphicsItemGroup();

    this->drawing_scene->addItem(this->drawing_layer);
    this->drawing_scene->addItem(this->overlay_layer);

    this->drawing_scene->setSceneRect(0, 0, DrawManager::FIELD_WIDTH, DrawManager::FIELD_WIDTH);
}

ExtendedGraphicView::~ExtendedGraphicView() {

}

void ExtendedGraphicView::clear() {
    this->delete_group_items(this->drawing_layer);
    this->delete_group_items(this->overlay_layer);

    int width = this->width();
    int height = this->height();

    this->drawing_scene->setSceneRect(0, 0, width, height);
}

void ExtendedGraphicView::set_map(const DrawManager::map_type &map) {
    curr_map = map;
    this->update();
}

void ExtendedGraphicView::select_point(const QPoint &point) {
    this->delete_group_items(this->overlay_layer);
    QPen pen;
    pen.setColor(QColor(0xFF, 0x00, 0x00, 0xFF));
    this->overlay_layer->addToGroup(this->drawing_scene->addRect(point.x(), point.y(), DrawManager::SPRITE_SIZE, DrawManager::SPRITE_SIZE, pen));
}

bool ExtendedGraphicView::allowed_move_for(const QPoint &from, const QPoint &to) {
    if (from == to) {
        return false;
    }

    if (!this->map_has_point(from) || !this->map_has_point(to)) {
        return false;
    }

    auto from_type = (*this->map_get_point(from)).second;
    auto to_type = (*this->map_get_point(to)).second;

    if (from_type == DrawManager::NON_WALKABLE || from_type == DrawManager::WALKABLE || to_type == DrawManager::NON_WALKABLE) {
        return false;
    }

    if (std::ceil(std::sqrt(std::pow(to.x() - from.x(), 2) + std::pow(to.y() - from.y(), 2))) != DrawManager::SPRITE_SIZE) {
        return false;
    }

    return (from_type == DrawManager::WALKABLE && to_type != DrawManager::NON_WALKABLE)
            || (to_type == DrawManager::WALKABLE && from_type != DrawManager::NON_WALKABLE);
}

void ExtendedGraphicView::perform_move(QPoint &from, QPoint &to) {
    auto pt = this->map_get_point(from);
    auto st = this->map_get_point(to);
    auto tmp = (*pt).second;
    (*pt).second = (*st).second;
    (*st).second = tmp;

    this->update();
}

void ExtendedGraphicView::delete_group_items(QGraphicsItemGroup *group) {
    foreach(QGraphicsItem *item, this->drawing_scene->items(group->boundingRect())) {
       if(item->group() == group) {
          delete item;
       }
    }
}

int ExtendedGraphicView::round_to_multiple(int numToRound, int multiple) {
    if (multiple == 0) {
        return numToRound;
    }

    int remainder = abs(numToRound) % multiple;
    if (remainder == 0) {
        return numToRound;
    }

    if (numToRound < 0) {
        return -(abs(numToRound) - remainder);
    }
    else {
        return numToRound + multiple - remainder;
    }
}

bool ExtendedGraphicView::map_has_point(const QPoint &point) {
    return this->map_get_point(point) != this->curr_map.end();
}

QVector<DrawManager::tile_type>::Iterator ExtendedGraphicView::map_get_point(const QPoint &point) {
    return std::find_if(
        this->curr_map.begin(),
        this->curr_map.end(),
        [point](const DrawManager::tile_type &element){ return element.first == point; }
    );
}

void ExtendedGraphicView::mousePressEvent(QMouseEvent *e) {
    int px = e->x();
    int py = e->y();
    QPoint qp(
        ExtendedGraphicView::round_to_multiple(px, DrawManager::SPRITE_SIZE) - DrawManager::SPRITE_SIZE,
        ExtendedGraphicView::round_to_multiple(py, DrawManager::SPRITE_SIZE) - DrawManager::SPRITE_SIZE
    );

    if (selected_point.selected) {
        if (*selected_point.point == qp) {
            selected_point.point = new QPoint(qp);
            selected_point.selected = false;
        }
        else {


            int dx = qp.x() - selected_point.point->x();
            int dy = qp.y() - selected_point.point->y();
            QPoint o_qp(qp);
            qp = *selected_point.point;

            selected_point.point = nullptr;
            selected_point.selected = false;

            while (this->allowed_move_for(qp, o_qp)) {
                this->perform_move(qp, o_qp);
                qp = QPoint(o_qp);
                o_qp = QPoint(qp.x() + dx, qp.y() + dy);
            }
        }
    }
    else {
        selected_point.point = new QPoint(qp);
        selected_point.selected = true;
    }

    this->update();
}

void ExtendedGraphicView::update() {
    this->clear();

    for (auto pair : curr_map) {
        auto sprite = DrawManager::get_sprite_by_type(pair.second);
        auto pixmap_item = this->drawing_scene->addPixmap(sprite);
        pixmap_item->setPos(pair.first);
        this->drawing_layer->addToGroup(pixmap_item);
    }

    if (this->selected_point.selected) {
        this->select_point(*this->selected_point.point);
    }
}


