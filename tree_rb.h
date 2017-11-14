#ifndef TREE_RB_H
#define TREE_RB_H

#include<iostream>
#include <functional>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

typedef enum {BLACK, RED} DishColor;
template <class T>
struct Node{
    Node * left;
    Node * right;
    Node * parent;
    DishColor color = BLACK;
    T data;
};

template <class T>
class Tree_RB
{
public:
    explicit Tree_RB();
    explicit Tree_RB(T const & data, std::function<bool (T, T)> compare);
    Tree_RB(Tree_RB<T> & tree);
    void insert(T & data);
    size_t size() const;
    bool isEmpty();
    Node<T> * find(T const & x);
    void remove(T const & x);
    void del(Node<T> * node);

    void saveToJSFile(QString fileName, std::function<void (T, QJsonArray &)> inFile);
    void loadFromJSFile(QString fileName, std::function<void (Tree_RB<T> *, QJsonArray &)> fromFile);
    void bypass_inJSFile(Node<T> * node, QJsonArray & JArray, std::function<void (T, QJsonArray &)> inFile);

    void inorder();
private:
    void copy(Node<T> * node, Node<T> * current, Node<T> * parent);
    std::function<bool (T, T)> compare;
    void show(Node<T>* node);
    void insert_tree(Node<T> * node);
    Node<T> * tree_min(Node<T> * node);
    Node<T> * tree_succ(Node<T> * node);
    void del_balance(Node<T> * node);
    void insert_balanse(Node<T> * node);
    void rotateLeft(Node<T> * node);
    void rotateRight(Node<T> * node);
    Node<T> * root;
    size_t size_;
};

#define NIL &sentinel

template <class T>
Node<T> sentinel;

template <class T>
void Tree_RB<T>::saveToJSFile(QString fileName, std::function<void (T, QJsonArray &)> inFile){
    if (isEmpty())
        return;
    QFile sequenceFile(fileName);
    if(!sequenceFile.open(QFile::WriteOnly)){
        qDebug() << "File for saving not found\n";
        return;
    }
    QJsonArray JSArray;
    bypass_inJSFile(root, JSArray, inFile);
    QJsonDocument doc(JSArray);
    sequenceFile.write(doc.toJson());
    sequenceFile.close();
}

template <class T>
void Tree_RB<T>::loadFromJSFile(QString fileName, std::function<void (Tree_RB<T> *, QJsonArray &)> fromFile){
    QFile file (fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        //ui->ErrorInf->setText("<font color=red>Ошибка регистрации.</font>");
        qDebug() << "File for loading not found\n";
        return;
    }
    QString val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonArray array(doc.array());
    fromFile(this, array);
}

template <class T>
void Tree_RB<T>::bypass_inJSFile(Node<T> * node, QJsonArray & JArray, std::function<void (T, QJsonArray &)> inFile){
    if(node->left != NIL<T>){
        bypass_inJSFile(node->left, JArray, inFile);
    }
    inFile(node->data, JArray);
    if (node->right != NIL<T>){
        bypass_inJSFile(node->right, JArray, inFile);
    }
}

template <class T>
Tree_RB<T>::Tree_RB(Tree_RB<T> & tree)
        : size_(tree.size_)
        , compare(tree.compare)
{
        (sentinel<T>).color = BLACK;
        (sentinel<T>).left = NIL<T>;
        (sentinel<T>).right = NIL<T>;
        (sentinel<T>).parent = NIL<T>;
        if (!tree.isEmpty())
        root = new Node<T>;
        copy(this->root, tree.root, NIL<T>);
}

template <class T>
void Tree_RB<T>::copy(Node<T> * node, Node<T> * current, Node<T> * parent){
    node->color = current->color;
    node->data = current->data;
    node->parent = parent;
    if (parent != NIL<T> && compare(node->data, parent->data))
        parent->left = node;
    else
        parent->right = node;
    if(current->left != NIL<T>){
        node->left = new Node<T>;
        copy(node->left, current->left, node);
    }
    else{
        node->left = NIL<T>;
    }
    if(current->right != NIL<T>){
        node->right = new Node<T>;
        copy(node->right, current->right, node);
    }
    else{
        node->right = NIL<T>;
    }
    return;
}

template <class T>
Tree_RB<T>::Tree_RB()
        :root(NIL<T>)
        ,size_(0)
{
    compare = [](T a, T b){return (a < b);};
    (sentinel<T>).color = BLACK;
    (sentinel<T>).left = NIL<T>;
    (sentinel<T>).right = NIL<T>;
    (sentinel<T>).parent = NIL<T>;
}

template <class T>
Tree_RB<T>::Tree_RB(T const & data, std::function<bool (T, T)> compare)
        : size_(1)
        , compare(compare)
{
    (sentinel<T>).color = BLACK;
    (sentinel<T>).left = NIL<T>;
    (sentinel<T>).right = NIL<T>;
    (sentinel<T>).parent = NIL<T>;
    root = new Node<T>;
    root->color = BLACK;
    root->left = NIL<T>;
    root->right = NIL<T>;
    root->parent = NIL<T>;
    root->data = data;
}

template <class T>
void Tree_RB<T>::show(Node<T> * node){
    if(node->left != NIL<T>){
        show(node->left);
    }
    std::cout << node->data << " ";
    if (node->right != NIL<T>){
        show(node->right);
    }
    return;
}


template <class T>
void Tree_RB<T>::inorder(){
    if(root != NIL<T>)
        this->show(root);
    return;
}

template <class T>
void Tree_RB<T>::rotateLeft(Node<T> * node){
    if(node->right == NIL<T>)
        return;
    Node<T> * y = node->right;
    node->right = y->left;
    if (y->left != NIL<T>)
        y->left->parent = node;
    y->parent = node->parent;
    if(node->parent == NIL<T>)
        root = y;
    else if (node == node->parent->left)
        node->parent->left = y;
    else
        node->parent->right = y;
    y->left = node;
    node->parent = y;
}

template <class T>
void Tree_RB<T>::rotateRight(Node<T> * node){
    if(node->left == NIL<T>)
        return;
    Node<T> * y = node->left;
    node->left = y->right;
    if (y->right != NIL<T>)
        y->right->parent = node;
    y->parent = node->parent;
    if(node->parent == NIL<T>)
        root = y;
    else if (node == node->parent->right)
        node->parent->right = y;
    else
        node->parent->left = y;
    y->right = node;
    node->parent = y;
}

template <class T>
Node<T> * Tree_RB<T>::tree_min(Node<T> * node){
    while(node->left != NIL<T>)
        node = node->left;
    return node;
}

template <class T>
Node<T> * Tree_RB<T>::tree_succ(Node<T> * node){
    if (node->right != NIL<T>)
        return tree_min(node->right);
    Node<T> * parent = node->parent;
    while(parent != NIL<T> && node == parent->right){
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

template <class T>
Node<T> * Tree_RB<T>::find(T const & x){
    Node<T> * y = root;
    while(y != NIL<T> && /*y->data != x*/(compare(y->data, x) || compare(x, y->data))){
        if (/*y->data < x*/compare(y->data, x))
            y = y->right;
        else
            y = y->left;
    }
    return y;
}

template <class T>
void Tree_RB<T>::del_balance(Node<T> * node){
    while(node != root && node->color == BLACK){
        if(node == node->parent->left){
            Node<T> * w = node->parent->right;
            if(w->color == RED){
                w->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                w = node->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                node = node->parent;
            } else {
                if (w->right->color == BLACK){
                w->left->color = BLACK;
                w->color = RED;
                rotateRight(w);
                }
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft(node->parent);
                node = root;
            }
        } else{
            Node<T> * w = node->parent->left;
            if(w->color == RED){
                w->color = BLACK;
                node->parent->color = RED;
                rotateRight(node->parent);
                w = node->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                node = node->parent;
            } else {
                if (w->left->color == BLACK){
                w->right->color = BLACK;
                w->color = RED;
                rotateLeft(w);
                }
                w->color = node->parent->color;
                node->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight(node->parent);
                node = root;
            }
        }
    }
}

template <class T>
void Tree_RB<T>::del(Node<T> * node){
    if (node == NIL<T>)
        return;
    Node<T> * y;
    if (node->left == NIL<T> || node->right == NIL<T>)
        y = node;
    else
        y = this->tree_succ(node);
    Node<T> * x;
    if (y->left != NIL<T>)
        x = y->left;
    else
        x = y->right;
    x->parent = y->parent;
    if (y->parent == NIL<T>)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    if (y != node)
        node->data = y->data;
    if (y->color == BLACK)
        del_balance(x);
    delete node;
    --size_;
}

template <class T>
void Tree_RB<T>::remove(T const & x){
    del(find(x));
}

template <class T>
void Tree_RB<T>::insert_tree(Node<T> * node){
    Node<T> * y = NIL<T>;
    Node<T> * x = root;
    while(x != NIL<T>){
        y = x;
        if (/*node->data < x->data*/compare(node->data, x->data))
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if (y == NIL<T>)
        root = node;
    else if (/*node->data < y->data*/ compare(node->data, y->data))
        y->left = node;
    else
        y->right = node;
    node->left = NIL<T>;
    node->right = NIL<T>;
    node->color = RED;
    insert_balanse(node);
}

template <class T>
void Tree_RB<T>::insert_balanse(Node<T> * node){
    while(node->parent != NIL<T> && node->parent->color == RED){
        if(node->parent == node->parent->parent->left){
            Node<T> * y = node->parent->parent->right;
            if (y->color == RED){
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else if (node == node->parent->right){
                node = node->parent;
                rotateLeft(node);
            } else{
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        } else{
            Node<T> * y = node->parent->parent->left;
            if (y->color == RED){
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else if (node == node->parent->left){
                node = node->parent;
                rotateRight(node);
            } else{
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

template <class T>
void Tree_RB<T>::insert(T & data){
    Node<T> * x = new Node<T>;
    x->data = data;
    insert_tree(x);
    ++size_;
}

template <class T>
size_t Tree_RB<T>::size() const{
    return size_;
}

template <class T>
bool Tree_RB<T>::isEmpty(){
    return size_ > 0 ? false : true;
}

#endif // TREE_RB_H
