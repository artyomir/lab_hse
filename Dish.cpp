#include "Dish.h"
#include <QDebug>

Dish::Dish(const QString &name, double const & weight ,
    double const & fat , double const & protein, double const & carboh,
    double const & org_acids, double const & fiber)
        :name(name)
        ,weight(weight < 0 ? 100 : weight)
        ,fat(fat < 0 || fat > 100 ? 0 : fat)
        ,protein(protein < 0 || protein > 100 - fat? 0 : protein)
        ,carboh(carboh < 0 || carboh > 100 - fat - protein? 0 : carboh)
        ,org_acids(org_acids < 0 || org_acids > 100 - fat - protein - carboh ? 0 : org_acids)
        ,fiber(fiber < 0 || fiber > 100 - fat - protein - carboh - org_acids ? 0 : fiber)
{}

double Dish::caloricity() const{

     //return (fat * 9.3 + (protein + carboh) * 4.3 + org_acids * 2.2 + fiber * 1.9) * weight / 100;
    return weight;
}

Dish::~Dish(){}

void Dish::set_name(QString const & name){
    this->name = name;
}

void Dish::set_weight(double const & weight){
    this->weight = weight > 0 ? weight : 0;
}

void Dish::set_fat(double const & fat){
    this->fat = fat <= 100 - protein - carboh - org_acids - fiber && fat > 0 ? fat : 0;
}

void Dish::set_protein(double const & protein){
    this->protein = protein <= 100 - carboh - org_acids - fiber - fat && protein > 0 ? protein : 0;
}

void Dish::set_carboh(double const & carboh){
    this->carboh = carboh <= 100 - org_acids - fiber - fat - protein && carboh > 0 ? carboh : 0;
}

void Dish::set_org_acids(double const & org_acids){
    this->org_acids = org_acids <= 100 - fiber - fat - protein - carboh && org_acids > 0 ? org_acids : 0;
}

void Dish::set_fiber(double const & fiber){
    this->fiber = fiber <= 100 - fat - protein - carboh - org_acids && fiber > 0 ? fiber : 0;
}

QString Dish::get_name() const{
    return name;
}

double Dish::get_weight() const{
    return weight;
}

double Dish::get_fat() const{
    return fat;
}

double Dish::get_protein() const{
    return protein;
}

double Dish::get_carboh() const{
    return carboh;
}

double Dish::get_org_acids() const{
    return org_acids;
}

double Dish::get_fiber() const{
    return fiber;
}


Dish::Dish(Dish const & dish)
        :name(dish.name)
        ,weight(dish.weight)
        ,fat(dish.fat)
        ,protein(dish.protein)
        ,carboh(dish.carboh)
        ,org_acids(dish.org_acids)
        ,fiber(dish.fiber)
{
}

bool Dish::equal(Dish const & dish) const{
  if (this->caloricity() == dish.caloricity()
      && this->carboh == dish.carboh
      && this->fat == dish.fat
      && this->fiber == dish.fiber
      && this->name == dish.name
      && this->org_acids == dish.org_acids
      && this->protein == dish.protein
      && this->weight == dish.weight)
      return true;
  else
      return false;
}

void Dish::inJSFile(QJsonArray & JSArray) const{
    QJsonObject JSdish;
//    JSdish.insert("Type", QJsonValue::fromVariant(type));
    JSdish.insert("Name", QJsonValue::fromVariant(name));
    JSdish.insert("Weight", QJsonValue::fromVariant(weight));
    JSdish.insert("Protein", QJsonValue::fromVariant(protein));
    JSdish.insert("Carbohydrates", QJsonValue::fromVariant(carboh));
    JSdish.insert("Organic acids", QJsonValue::fromVariant(org_acids));
    JSdish.insert("Fats", QJsonValue::fromVariant(fat));
    JSArray.push_back(JSdish);
}

void Dish::fromJSFile(QJsonObject const & obj){
//    type = (DinnerType)obj["Type"].toInt();
    name = obj["Name"].toString();
    weight = obj["Weight"].toDouble();
    fat = obj["Fats"].toDouble();
    protein = obj["Protein"].toDouble();
    carboh = obj["Carbohydrates"].toDouble();
    org_acids = obj["Organic acids"].toDouble();
}

//void Dish_fromJSFile(Tree_RB<Dish *> * tree, QJsonArray & JSArray){
//    foreach (auto element, JSArray) {
//        Dish * dish = new Dish();
//        dish->set_name(element.toObject()["Name"].toString());
//        dish->set_weight(element.toObject()["Weight"].toDouble());
//        dish->set_fat(element.toObject()["Fats"].toDouble());
//        dish->set_protein(element.toObject()["Protein"].toDouble());
//        dish->set_carboh(element.toObject()["Carbohydrates"].toDouble());
//        dish->set_org_acids(element.toObject()["Organic acids"].toDouble());
//        tree->insert(dish);
//    }
//}

//bool cmp(Dish * d1, Dish * d2){
//    d1->compare(d2);
//}

