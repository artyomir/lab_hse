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
    Dish * water = new Dish("ASHOT",10);
    Dish * fire = new Dish("ARTYOM",20);

    Tree_RB<Dish*> tree(water, &cmp);
    std::cout << "THE END";
    tree.saveToJSFile("C:/Users/Artyom Mirabyan/Desktop/qwerty.txt", &Dish_inJSFile);
    tree.loadFromJSFile("C:/Users/Artyom Mirabyan/Desktop/qwerty.txt", &Dish_fromJSFile);

    Tree_RB<Dish *> t = tree;

    tree.remove(water);
    t.insert(fire);
    tree.saveToJSFile("C:/Users/Artyom Mirabyan/Desktop/TREE1.txt", &Dish_inJSFile);
    t.saveToJSFile("C:/Users/Artyom Mirabyan/Desktop/TREE2.txt", &Dish_inJSFile);
    return a.exec();
}
