//
// Created by Hamidou Wara Ballo on 5/20/20.
//

#ifndef TREE_LAST_AVLTREE_H
#define TREE_LAST_AVLTREE_H
#include <stack>
#include <queue>
using namespace std;
//This structure creates Binary Node for the Binary Tree
template <class T>
struct Node
{

    T info;            //Data of a node on the  tree
    Node<T> *left;     //Pointer Points to the left node of the tree
    Node<T> *right;    //Pointer points to the right node of the tree
    int count = 0;     //Counter count the number of duplicate inf from the tree
    int balance = 0;   //Holds the balance factor of the tree

};

template <class T>
class AVLTree
{
private:
    Node<T> *root;                  //the tree root
    Node<T>* Copy_Tree(Node<T>*);
    void Delete_Whole_Tree(Node<T>*&);
    void Print_Inorder(Node<T>*);
    void Populate_Inorder(Node<T>*, queue<T>&);
    int Count_Node(Node<T>*);
    void Insert_Item(Node<T>*&, T);
    void Delete_Item(Node<T> *&, T);
    bool Search_Item(Node<T>*&, T);
    bool Is_Balanced(Node<T>*);
    int Get_Balance(Node<T>*);
    int AVL_Tree_Height(Node<T>*);
    int Balance_Factor(Node<T>*);
    void Fix_Height(Node<T>*&);
    void Right_Rotation(Node<T>*&);
    void Left_Rotation(Node<T>*&);
    void Balance_Tree(Node<T>*&);
    void Delete_Node(Node<T> *&p);
    T Get_Info(Node<T>*);
    int Get_Count(Node<T>*, T);
public:
    AVLTree();
    AVLTree(const AVLTree<T>&);
    AVLTree& operator=(const AVLTree<T>&);
    bool Is_Empty();
    int Count_Node();
    void Populate_Inorder(queue<T>&);
    void Delete_Item(T);
    bool Search_Item(T);
    void Insert_Item(T);
    bool Is_Balanced();
    int Get_Count(T item);
    void Statistics();
    ~AVLTree();
};
#endif //TREE_LAST_AVLTREE_H
