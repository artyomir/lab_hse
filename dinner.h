#ifndef DINNER_H
#define DINNER_H

#include <QJsonArray>
#include <QJsonObject>
#include "tree_rb.h"

typedef enum{DISH, COMPLEX_DINNER} DinnerType;

class Dinner
{
public:
    virtual double caloricity() const = 0;
    virtual void inJSFile(QJsonArray & JSArray) const = 0;
    virtual void fromJSFile(QJsonObject const & obj) = 0;
};

bool cmp(Dinner * a, Dinner * b);
void fromJSFile(Tree_RB<Dinner *> * tree, QJsonArray & JSArray);
void inJSFile(Dinner * din, QJsonArray & JSArray);


#endif // DINNER_H
