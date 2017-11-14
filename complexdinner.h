#ifndef COMPLEXDINNER_H
#define COMPLEXDINNER_H

#include "dinner.h"
#include "Dish.h"

class ComplexDinner: public Dinner{
public:
    explicit ComplexDinner(QString const & name = "Water dinner",Dish const & first = Dish(), Dish const & second = Dish(),
                           Dish const & beverage = Dish(), Dish const & dessert = Dish());
    ComplexDinner(ComplexDinner const & dinner);
    bool equal(Dish const & dish) const;
    QString get_name() const;
    double  get_weight() const;
    double get_fat() const;
    double get_protein() const;
    double get_carboh() const;
    double get_org_acids() const;
    double get_fiber() const;
    Dish get_first();
    Dish get_second();
    Dish get_beverage();
    Dish get_dessert();
    void set_name(QString const & name);
    void set_first(Dish const & dish);
    void set_second(Dish const & dish);
    void set_beverage(Dish const & dish);
    void set_dessert(Dish const & dish);
    virtual double caloricity() const;
    virtual void inJSFile(QJsonArray & JSArray) const;
    virtual void fromJSFile(QJsonObject const & obj);
    ~ComplexDinner();
private:
    DinnerType type = COMPLEX_DINNER;
    Dish first;
    Dish second;
    Dish beverage;
    Dish dessert;
    QString name;
    double weight, fat, protein, carboh, org_acids, fiber;
};

#endif // COMPLEXDINNER_H
