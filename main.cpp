#include <QCoreApplication>
#include "Dish.h"
#include "tree_rb.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Dish * water = new Dish("Paste",10);
    Dish * fire = new Dish("Potate",20);

    Tree_RB<Dish*> tree(water, &cmp);

    tree.saveToJSFile("take filename here", &Dish_inJSFile);
    tree.loadFromJSFile("take filename here", &Dish_fromJSFile);

    Tree_RB<Dish *> t = tree;

    tree.remove(water);
    t.insert(fire);
    tree.saveToJSFile("take filename here", &Dish_inJSFile);
    t.saveToJSFile("take filename here", &Dish_inJSFile);
    return a.exec();
}
