#pragma once

#include <iostream>
#include <QString>
#include "dinner.h"
#include "tree_rb.h"

class Dish: public Dinner{
public:
    explicit Dish(QString const & name = "water", double const &weight = 100,
         double const &fat = 0, double const &protein = 0,
         double const &carboh = 0, double const &org_acids = 0,
         double const &fiber = 0);
    Dish(Dish const & dish);
    bool equal(Dish const & dish) const;
    QString get_name() const;
    double  get_weight() const;
    double get_fat() const;
    double get_protein() const;
    double get_carboh() const;
    double get_org_acids() const;
    double get_fiber() const;
    void set_name(QString const & name);
    void set_weight(double const & weight);
    void set_fat(double const & fat);
    void set_protein(double const & protein);
    void set_carboh(double const & carboh);
    void set_org_acids(double const & org_acids);
    void set_fiber(double const & fiber);
    virtual double caloricity() const;
    virtual void inJSFile(QJsonArray & JSArray) const;
    virtual void fromJSFile(QJsonObject const & obj);
    ~Dish();
private:
//    DinnerType type = DISH;
    QString name;
    double weight, fat, protein, carboh, org_acids, fiber;
};

void Dish_inJSFile(Dish const * dish, QJsonArray & JSArray);
void Dish_fromJSFile(Tree_RB<Dish *> * tree, QJsonArray & JSArray);
