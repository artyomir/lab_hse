#include "complexdinner.h"

ComplexDinner::ComplexDinner(QString const & name,Dish const & first, Dish const & second,
                       Dish const & beverage, Dish const & dessert)
        : name(name)
        , first(first)
        , second(second)
        , beverage(beverage)
        , dessert(dessert)
        , weight(first.get_weight() + second.get_weight() + beverage.get_weight() + dessert.get_weight())
        , fat (first.get_fat() + second.get_fat() + beverage.get_fat() + dessert.get_fat())
        , protein (first.get_protein() + second.get_protein() + beverage.get_protein() + dessert.get_protein())
        , carboh (first.get_carboh() + second.get_carboh() + beverage.get_carboh() + dessert.get_carboh())
        , org_acids (first.get_org_acids() + second.get_org_acids() + beverage.get_org_acids() + dessert.get_org_acids())
        , fiber (first.get_fiber() + second.get_fiber() + beverage.get_fiber() + dessert.get_fiber())
{}

ComplexDinner::ComplexDinner(ComplexDinner const & dinner)
    : name(dinner.name)
    , first(dinner.first)
    , second(dinner.second)
    , beverage(dinner.beverage)
    , dessert(dinner.dessert)
    , weight(dinner.weight)
    , fat (dinner.fat)
    , protein (dinner.protein)
    , carboh (dinner.carboh)
    , org_acids (dinner.org_acids)
    , fiber (dinner.fiber)
{}

ComplexDinner::~ComplexDinner(){}

double ComplexDinner::caloricity() const{
    //return (fat * 9.3 + (protein + carboh) * 4.3 + org_acids * 2.2 + fiber * 1.9) * weight / 100;
    return weight;
}

QString ComplexDinner::get_name() const{
    return name;
}

double ComplexDinner::get_weight() const{
    return weight;
}

double ComplexDinner::get_fat() const{
    return fat;
}

double ComplexDinner::get_protein() const{
    return protein;
}

double ComplexDinner::get_carboh() const{
    return carboh;
}

double ComplexDinner::get_org_acids() const{
    return org_acids;
}

double ComplexDinner::get_fiber() const{
    return fiber;
}

Dish ComplexDinner::get_first(){
    return first;
}

Dish ComplexDinner::get_second(){
    return second;
}

Dish ComplexDinner::get_beverage(){
    return beverage;
}

Dish ComplexDinner::get_dessert(){
    return dessert;
}

void ComplexDinner::set_name(QString const & name){
    this->name = name;
}

void ComplexDinner::set_first(Dish const & dish){
    this->first = dish;
    weight = first.get_weight() + second.get_weight() + beverage.get_weight() + dessert.get_weight();
    fat = first.get_fat() + second.get_fat() + beverage.get_fat() + dessert.get_fat();
    protein = first.get_protein() + second.get_protein() + beverage.get_protein() + dessert.get_protein();
    carboh = first.get_carboh() + second.get_carboh() + beverage.get_carboh() + dessert.get_carboh();
    org_acids = first.get_org_acids() + second.get_org_acids() + beverage.get_org_acids() + dessert.get_org_acids();
    fiber = first.get_fiber() + second.get_fiber() + beverage.get_fiber() + dessert.get_fiber();
}

void ComplexDinner::set_second(Dish const & dish){
    this->second = dish;
    weight = first.get_weight() + second.get_weight() + beverage.get_weight() + dessert.get_weight();
    fat = first.get_fat() + second.get_fat() + beverage.get_fat() + dessert.get_fat();
    protein = first.get_protein() + second.get_protein() + beverage.get_protein() + dessert.get_protein();
    carboh = first.get_carboh() + second.get_carboh() + beverage.get_carboh() + dessert.get_carboh();
    org_acids = first.get_org_acids() + second.get_org_acids() + beverage.get_org_acids() + dessert.get_org_acids();
    fiber = first.get_fiber() + second.get_fiber() + beverage.get_fiber() + dessert.get_fiber();
}

void ComplexDinner::set_beverage(Dish const & dish){
    this->beverage = dish;
    weight = first.get_weight() + second.get_weight() + beverage.get_weight() + dessert.get_weight();
    fat = first.get_fat() + second.get_fat() + beverage.get_fat() + dessert.get_fat();
    protein = first.get_protein() + second.get_protein() + beverage.get_protein() + dessert.get_protein();
    carboh = first.get_carboh() + second.get_carboh() + beverage.get_carboh() + dessert.get_carboh();
    org_acids = first.get_org_acids() + second.get_org_acids() + beverage.get_org_acids() + dessert.get_org_acids();
    fiber = first.get_fiber() + second.get_fiber() + beverage.get_fiber() + dessert.get_fiber();
}

void ComplexDinner::set_dessert(Dish const & dish){
    this->dessert = dish;
    weight = first.get_weight() + second.get_weight() + beverage.get_weight() + dessert.get_weight();
    fat = first.get_fat() + second.get_fat() + beverage.get_fat() + dessert.get_fat();
    protein = first.get_protein() + second.get_protein() + beverage.get_protein() + dessert.get_protein();
    carboh = first.get_carboh() + second.get_carboh() + beverage.get_carboh() + dessert.get_carboh();
    org_acids = first.get_org_acids() + second.get_org_acids() + beverage.get_org_acids() + dessert.get_org_acids();
    fiber = first.get_fiber() + second.get_fiber() + beverage.get_fiber() + dessert.get_fiber();
}

void ComplexDinner::inJSFile(QJsonArray & JSArray) const{
    QJsonObject JSdish;
    JSdish.insert("Type", QJsonValue::fromVariant(type));
    JSdish.insert("Dinner name", QJsonValue::fromVariant(name));
    JSdish.insert("Dinner Weight", QJsonValue::fromVariant(weight));
    JSdish.insert("Dinner Protein", QJsonValue::fromVariant(protein));
    JSdish.insert("Dinner Carbohydrates", QJsonValue::fromVariant(carboh));
    JSdish.insert("Dinner organic acids", QJsonValue::fromVariant(org_acids));
    JSdish.insert("Dinner Fats", QJsonValue::fromVariant(fat));

    JSdish.insert("First name", QJsonValue::fromVariant(first.get_name()));
    JSdish.insert("First Weight", QJsonValue::fromVariant(first.get_weight()));
    JSdish.insert("First Protein", QJsonValue::fromVariant(first.get_protein()));
    JSdish.insert("First Carbohydrates", QJsonValue::fromVariant(first.get_carboh()));
    JSdish.insert("First organic acids", QJsonValue::fromVariant(first.get_org_acids()));
    JSdish.insert("First Fats", QJsonValue::fromVariant(first.get_fat()));

    JSdish.insert("Second name", QJsonValue::fromVariant(second.get_name()));
    JSdish.insert("Second Weight", QJsonValue::fromVariant(second.get_weight()));
    JSdish.insert("Second Protein", QJsonValue::fromVariant(second.get_protein()));
    JSdish.insert("Second Carbohydrates", QJsonValue::fromVariant(second.get_carboh()));
    JSdish.insert("Second organic acids", QJsonValue::fromVariant(second.get_org_acids()));
    JSdish.insert("Second Fats", QJsonValue::fromVariant(second.get_fat()));

    JSdish.insert("Beverage name", QJsonValue::fromVariant(beverage.get_name()));
    JSdish.insert("Beverage Weight", QJsonValue::fromVariant(beverage.get_weight()));
    JSdish.insert("Beverage Protein", QJsonValue::fromVariant(beverage.get_protein()));
    JSdish.insert("Beverage Carbohydrates", QJsonValue::fromVariant(beverage.get_carboh()));
    JSdish.insert("Beverage organic acids", QJsonValue::fromVariant(beverage.get_org_acids()));
    JSdish.insert("Beverage Fats", QJsonValue::fromVariant(beverage.get_fat()));

    JSdish.insert("Dessert name", QJsonValue::fromVariant(dessert.get_name()));
    JSdish.insert("Dessert Weight", QJsonValue::fromVariant(dessert.get_weight()));
    JSdish.insert("Dessert Protein", QJsonValue::fromVariant(dessert.get_protein()));
    JSdish.insert("Dessert Carbohydrates", QJsonValue::fromVariant(dessert.get_carboh()));
    JSdish.insert("Dessert organic acids", QJsonValue::fromVariant(dessert.get_org_acids()));
    JSdish.insert("Dessert Fats", QJsonValue::fromVariant(dessert.get_fat()));

    JSArray.push_back(JSdish);
}

void ComplexDinner::fromJSFile(QJsonObject const & obj){
    type = (DinnerType)obj["Type"].toInt();
    name = obj["Dinner name"].toString();
    weight = obj["Dinner Weight"].toDouble();
    fat = obj["Dinner Fats"].toDouble();
    protein = obj["Dinner Protein"].toDouble();
    carboh = obj["Dinner Carbohydrates"].toDouble();
    org_acids = obj["Dinner Organic acids"].toDouble();

    first.set_name(obj["First name"].toString());
    first.set_weight(obj["First Weight"].toDouble());
    first.set_fat(obj["First Fats"].toDouble());
    first.set_protein(obj["First Protein"].toDouble());
    first.set_carboh(obj["First Carbohydrates"].toDouble());
    first.set_org_acids(obj["First Organic acids"].toDouble());

    second.set_name(obj["Second name"].toString());
    second.set_weight(obj["Second Weight"].toDouble());
    second.set_fat(obj["Second Fats"].toDouble());
    second.set_protein(obj["Second Protein"].toDouble());
    second.set_carboh(obj["Second Carbohydrates"].toDouble());
    second.set_org_acids(obj["Second Organic acids"].toDouble());

    beverage.set_name(obj["Beverage name"].toString());
    beverage.set_weight(obj["Beverage Weight"].toDouble());
    beverage.set_fat(obj["Beverage Fats"].toDouble());
    beverage.set_protein(obj["Beverage Protein"].toDouble());
    beverage.set_carboh(obj["Beverage Carbohydrates"].toDouble());
    beverage.set_org_acids(obj["Beverage Organic acids"].toDouble());

    dessert.set_name(obj["Dessert name"].toString());
    dessert.set_weight(obj["Dessert Weight"].toDouble());
    dessert.set_fat(obj["Dessert Fats"].toDouble());
    dessert.set_protein(obj["Dessert Protein"].toDouble());
    dessert.set_carboh(obj["Dessert Carbohydrates"].toDouble());
    dessert.set_org_acids(obj["Dessert Organic acids"].toDouble());
}

