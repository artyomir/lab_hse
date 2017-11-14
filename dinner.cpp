#include "dinner.h"
#include "Dish.h"
#include "complexdinner.h"
bool cmp(Dinner * a, Dinner * b){
    return a->caloricity() < b->caloricity();
}

void fromJSFile(Tree_RB<Dinner *> * tree, QJsonArray & JSArray){
    foreach (auto element, JSArray) {
        if ((DinnerType)element.toObject()["Type"].toInt() == COMPLEX_DINNER){
            Dinner * dinner = new ComplexDinner();
            dinner->fromJSFile(element.toObject());
            tree->insert(dinner);;
        } else /*if((DinnerType)element.toObject()["Type"].toInt() == DISH)*/ {
            Dinner * dinner = new Dish();
            dinner->fromJSFile(element.toObject());
            tree->insert(dinner);
        }
    }
}

void inJSFile(Dinner * din, QJsonArray & JSArray){
       din->inJSFile(JSArray);
}

