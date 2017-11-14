#include <QCoreApplication>
#include "Dish.h"
#include "tree_rb.h"
#include "complexdinner.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Dinner * water = new Dish("water",10);
    Dinner * fire = new Dish("Potate",20);
    Dinner * chicken = new Dish("Chck", 50);
    Dinner * burg = new Dish("Burger", 13);
    Dinner * complex = new ComplexDinner("Complex Dinner", Dish("Chck", 50),Dish("Burger", 13), Dish(), Dish("Pancake", 15));
    Tree_RB<Dinner*> tree(chicken, &cmp);
    tree.insert(complex);

    tree.saveToJSFile("take filename here", &inJSFile);
    tree.loadFromJSFile("take filename here", &fromJSFile);

    Tree_RB<Dinner *> t = tree;

    tree.remove(water);
    t.insert(fire);
    t.insert(water);
    t.insert(chicken);
    t.insert(burg);

    Dinner * din = new ComplexDinner();
    t.insert(din);

    tree.saveToJSFile("take filename here", &inJSFile);
    t.saveToJSFile("C:/users/Artyom Mirabyan/Desktop/TREE1.txt", &inJSFile);
    return a.exec();
}
