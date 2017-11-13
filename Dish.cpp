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
{
//    qDebug() << "Debug: initializing constructor is called";
}

double Dish::caloricity() const{
//    qDebug() << "Debug: caloricity method is called";
//    return (fat * 9.3 + (protein + carboh) * 4.3 + org_acids * 2.2 + fiber * 1.9) * weight / 100;
    return weight;
}

Dish::~Dish(){
//    qDebug() << "Debug: destructor is called";
}

void Dish::set_name(QString const & name){
//    qDebug() << "Debug: set_name method is called";
    this->name = name;
}

void Dish::set_weight(double const & weight){
//    qDebug() << "Debug: set_weight method is called";
    this->weight = weight > 0 ? weight : 0;
}

void Dish::set_fat(double const & fat){
//   qDebug() << "Debug: set_fat method is called";
    this->fat = fat <= 100 - protein - carboh - org_acids - fiber && fat > 0 ? fat : 0;
}

void Dish::set_protein(double const & protein){
//    qDebug() << "Debug: set_protein method is called";
    this->protein = protein <= 100 - carboh - org_acids - fiber - fat && protein > 0 ? protein : 0;
}

void Dish::set_carboh(double const & carboh){
//    qDebug() << "Debug: set_carboh method is called";
    this->carboh = carboh <= 100 - org_acids - fiber - fat - protein && carboh > 0 ? carboh : 0;
}

void Dish::set_org_acids(double const & org_acids){
//    qDebug() << "Debug: set_acids method is called";
    this->org_acids = org_acids <= 100 - fiber - fat - protein - carboh && org_acids > 0 ? org_acids : 0;
}

void Dish::set_fiber(double const & fiber){
//    qDebug() << "Debug: set_fiber method is called";
    this->fiber = fiber <= 100 - fat - protein - carboh - org_acids && fiber > 0 ? fiber : 0;
}

QString Dish::get_name() const{
//    qDebug() << "Debug: get_name method is called";
    return name;
}

double Dish::get_weight() const{
//    qDebug() << "Debug: get_weight method is called";
    return weight;
}

double Dish::get_fat() const{
//    qDebug() << "Debug: get_fat method is called";
    return fat;
}

double Dish::get_protein() const{
//    qDebug() << "Debug: get_protein method is called";
    return protein;
}

double Dish::get_carboh() const{
//    qDebug() << "Debug: get_carboh method is called";
    return carboh;
}

double Dish::get_org_acids() const{
//    qDebug() << "Debug: get_org_acids method is called";
    return org_acids;
}

double Dish::get_fiber() const{
//    qDebug() << "Debug: get_fiber method is called";
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
//    qDebug() << "Debug: copy constructor is called";
}

//std::ostream& operator<<(std::ostream & os, Dish const & dish){
////    qDebug() << "Debug: ostream operator<< is called";
//    os <<"\n    "<< dish.name <<":"
//    <<"\n       weight: "<< dish.weight << " g"
//    <<"\n       fats: " << dish.fat
//    <<"\n       proteins: "<< dish.protein
//    <<"\n       carbohudrates: "<< dish.carboh
//    <<"\n       organic acids: "<< dish.org_acids
//    <<"\n       fiber: "<< dish.fiber <<"\n\n";
//    return os;
//}

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


void Dish_inJSFile(Dish const * dish, QJsonArray & JSArray){
    QJsonObject JSdish;
    JSdish.insert("Name", QJsonValue::fromVariant(dish->get_name()));
    JSdish.insert("Weight", QJsonValue::fromVariant(dish->get_weight()));
    JSdish.insert("Protein", QJsonValue::fromVariant(dish->get_protein()));
    JSdish.insert("Carbohydrates", QJsonValue::fromVariant(dish->get_carboh()));
    JSdish.insert("Organic acids", QJsonValue::fromVariant(dish->get_org_acids()));
    JSdish.insert("Fats", QJsonValue::fromVariant(dish->get_fat()));
    JSArray.push_back(JSdish);
}

void Dish_fromJSFile(Tree_RB<Dish *> * tree, QJsonArray & JSArray){
    foreach (auto element, JSArray) {
        Dish * dish = new Dish();
        dish->set_name(element.toObject()["Name"].toString());
        dish->set_weight(element.toObject()["Weight"].toDouble());
        dish->set_fat(element.toObject()["Fats"].toDouble());
        dish->set_protein(element.toObject()["Protein"].toDouble());
        dish->set_carboh(element.toObject()["Carbohydrates"].toDouble());
        dish->set_org_acids(element.toObject()["Organic acids"].toDouble());
        tree->insert(dish);
    }
}

bool cmp(Dish * d1, Dish * d2){
    d1->compare(d2);
}

