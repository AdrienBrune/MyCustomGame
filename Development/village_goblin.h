#ifndef VILLAGE_GOBLIN_H
#define VILLAGE_GOBLIN_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QVector>
#include <qrandom.h>
#include <QPainter>
#include "mapitem.h"
#include "equipment.h"
#include "monster.h"
#include "toolfunctions.h"

class Hut : public MapItem
{
public:
    Hut();
    ~Hut();
};

class TownHall : public MapItem
{
public:
    TownHall();
    ~TownHall();
};

class WatchTower : public MapItem
{
public:
    WatchTower();
    ~WatchTower();
};

class Village_Goblin : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Village_Goblin();
    ~Village_Goblin();
signals:
    void sig_clicToOpenChest(ChestEvent*);
public:
    void addInScene(QGraphicsScene*);
    void setPosition(QPointF);
    QPointF getPosition();
public:
    QPainterPath shape() const;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap mImage;
    QPointF mPosition;

    int mRoadsWeight;
    QList<Hut*> mHuts;
    QList<WatchTower*> mWatchTowers;
    TownHall * mTownHall;
    GoblinChest * mChest;
};

class Village_Goblin_Area : public QGraphicsItem
{
public:
    Village_Goblin_Area();
    ~Village_Goblin_Area();
public:
    Village_Goblin * getVillage();
    void addInScene(QGraphicsScene*);
    void setPosition(QPointF);
public:
    QPainterPath shape() const;
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    Village_Goblin * mVillage;
};

#endif // VILLAGE_GOBLIN_H
