#pragma once
#include "geo2d.h"

class Unit;
class Building;
class Tower;
class Fence;

struct GameObject {
    virtual ~GameObject() = default;

    virtual bool Collide(const GameObject& that) const = 0;
    virtual bool CollideWith(const Unit& that) const = 0;
    virtual bool CollideWith(const Building& that) const = 0;
    virtual bool CollideWith(const Tower& that) const = 0;
    virtual bool CollideWith(const Fence& that) const = 0;
};

//class Unit : public GameObject {
//public:
//    explicit Unit(geo2d::Point position);
//    bool Collide(const GameObject &that) const override;
//    bool CollideWith(const Unit &that) const override;
//    bool CollideWith(const Building &that) const override;
//    bool CollideWith(const Tower &that) const override;
//    bool CollideWith(const Fence &that) const override;
//    geo2d::Point GetPosition() const;
//private:
//    geo2d::Point position_;
//};
//
//class Building : public GameObject {
//public:
//    explicit Building(geo2d::Rectangle geometry);
//    bool Collide(const GameObject &that) const override;
//    bool CollideWith(const Unit &that) const override;
//    bool CollideWith(const Building &that) const override;
//    bool CollideWith(const Tower &that) const override;
//    bool CollideWith(const Fence &that) const override;
//    geo2d::Rectangle GetPosition() const;
//private:
//    geo2d::Rectangle position_;
//};
//
//class Tower : public GameObject {
//public:
//    explicit Tower(geo2d::Circle geometry);
//    bool Collide(const GameObject &that) const override;
//    bool CollideWith(const Unit &that) const override;
//    bool CollideWith(const Building &that) const override;
//    bool CollideWith(const Tower &that) const override;
//    bool CollideWith(const Fence &that) const override;
//    geo2d::Circle GetPosition() const;
//private:
//    geo2d::Circle position_;
//};
//
//class Fence : public GameObject {
//public:
//    explicit Fence(geo2d::Segment geometry);
//    bool Collide(const GameObject &that) const override;
//    bool CollideWith(const Unit &that) const override;
//    bool CollideWith(const Building &that) const override;
//    bool CollideWith(const Tower &that) const override;
//    bool CollideWith(const Fence &that) const override;
//    geo2d::Segment GetPosition() const;
//private:
//    geo2d::Segment position_;
//};
//
//// Реализуйте функцию Collide из файла GameObject.h
//bool Collide(const GameObject &first, const GameObject &second);
