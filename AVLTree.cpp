//
// Created by Hamidou Wara Ballo on 5/20/20.
//

#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <string>
//Insert an item in the tree
template <class T>
void AVLTree<T>::Insert_Item(T item)
{
    Insert_Item(this->root, item);
}

//Insert item in the AVL Tree
template <class T>
void AVLTree<T>::Insert_Item(Node<T> *&p, T item)
{

    if(p == nullptr)
    {
        p=new Node<T>;
        p->info = item;
        p->left = nullptr;
        p->right = nullptr;
        p->count = 1;
    }
    if (p->info==item)
    {
        p->count++;
        return;
    }

    else if (p->info > item)
        Insert_Item(p->left, item);
    else
        Insert_Item(p->right, item);

    Balance_Tree(p);

}

//Delete item from the Tree
template <class T>
void AVLTree<T>::Delete_Item(T item)
{
    Delete_Item(this->root, item);
}

//Delete item from the tree
template <class T>
void AVLTree<T>::Delete_Item(Node<T> *&p, T item)
{
    if(p == nullptr)
    {
        std::cout<<"Item is not found"<<std::endl;
        return;
    }
    else
    {
        if(p->info==item)
            Delete_Node(p);
        else if (p->info > item)
            Delete_Item(p->left, item);
        else
            Delete_Item(p->right, item);
    }
}

// Delete Node from tree
template <class T>
void AVLTree<T>::Delete_Node(Node<T> *&p)
{
    Node<T>*q = p;

    if(p->left== nullptr)
    {
        p = p->right;
        delete q;
    }
    else if(p->right == nullptr)
    {
        p = p->left;
        delete q;
    }
    else{
        T item = Get_Info(p->left);
        p->info = item;
        Balance_Tree(p);
        Delete_Item(p->left, item);
    }
}

//Get the node info
template <class T>
T AVLTree<T>::Get_Info(Node<T> *p)
{
    while(p->right != nullptr)
        p = p->right;
    return p->info;
}

//search item in the tree
template <class T>
bool AVLTree<T>::Search_Item(T item)
{
    return Search_Item(this->root, item);
}

//Search item in the tree
template <class T>
bool AVLTree<T>::Search_Item(Node<T> *& p, T item)
{
    if(p== nullptr)
        return false;
    else
    {
        if(p->info==item)
            return true;
        else if(p->info>item)
            return Search_Item(p->left, item);
        else
            return Search_Item(p->right, item);
    }

}

//Return the tree height
template <class T>
int AVLTree<T>::AVL_Tree_Height(Node<T> *p)
{
    if(p == nullptr)
        return 0;
    else
        return p->balance;
}

//Returns the tree balance factor
template <class T>
int AVLTree<T>::Balance_Factor(Node<T> *p)
{
    return AVL_Tree_Height(p->right) - AVL_Tree_Height(p->left);
}

//Makes sure the tree height is good
template <class T>
void AVLTree<T>::Fix_Height(Node<T> *&p)
{
    int Left_Height= AVL_Tree_Height(p->left);
    int Right_Height= AVL_Tree_Height(p->right);

    if(Left_Height > Right_Height)
        p->balance= Left_Height + 1;
    else
        p->balance= Right_Height + 1;
}

//right rotation of tree nodes
template <class T>
void AVLTree<T>::Right_Rotation(Node<T> *&p)
{
    Node<T> *q = p->left;
    p->left = q->right;
    q->right = p;
    Fix_Height(p);
    Fix_Height(q);
    p = q;
}

//left rotation of tree nodes
template <class T>
void AVLTree<T>::Left_Rotation(Node<T> *&p)
{
    Node<T>* q = p->right;
    p->right = q->left;
    q->left=p;
    Fix_Height(p);
    Fix_Height(q);
    p = q;

}

//Receive the node that should be balanced
template <class T>
void AVLTree<T>::Balance_Tree(Node<T> *&p)
{
    Fix_Height(p);
    if(Balance_Factor(p) == 2)
    {
        if(Balance_Factor(p->right) < 0)
            Right_Rotation(p->right);
        Left_Rotation(p);
    }
    if(Balance_Factor(p) == -2)
    {
        if(Balance_Factor(p->left) > 0)
            Left_Rotation(p->left);
        Right_Rotation(p);
    }

}

//Checks if the tree is balanced
template <class T>
bool AVLTree<T>::Is_Balanced(Node<T> *p)
{
    int result = Get_Balance(p);
    return result > 0;

}

//Checks if the tree is balanced
template <class T>
bool AVLTree<T>::Is_Balanced()
{
    return Is_Balanced(this->root);
}

//Returns balance tree
template <class T>
int AVLTree<T>::Get_Balance(Node<T> *p)
{
    if(p== nullptr)
        return 0;
    int Left_Height = Get_Balance(p->left);
    if(Left_Height == -1)
        return -1;

    int Right_Height = Get_Balance(p->right);
    if(Right_Height == -1)
    {
        return -1;
    }
    int difference = Left_Height - Right_Height;
    if(difference>1||difference<-1)
        return -1;

    if(Left_Height > Right_Height)
        return 1 + Left_Height;
    else
        return 1 + Right_Height;
}


//Returns duplicates in the tree
template <class T>
int AVLTree<T>::Get_Count(T item)
{
    return Get_Count(this->root, item);
}
template <class T>
int AVLTree<T>::Get_Count(Node<T> *p, T item)
{
    if(p == nullptr)
        return 0;
    else
    {
        if(p->info>item)
            return Get_Count(p->left, item);
        else if (p->info<item)
            return Get_Count(p->right, item);
        else
            return p->count;

    }

}


//constructor with parameters
template <class T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
}

//destructor
template <class T>
AVLTree<T>::~AVLTree()
{
    Delete_Whole_Tree(root);
}

//Coy function copies the tree
template <class T>
Node<T>* AVLTree<T>::Copy_Tree(Node<T> *copyNode)
{
    if(copyNode == nullptr)
        return NULL;

    Node<T> *temp = new Node<T>;
    temp->info = copyNode->info;
    temp->count = copyNode->count;
    temp->left = Copy_Tree(copyNode->left);
    temp->right = Copy_Tree(copyNode->right);


}

//copy constructor
template <class T>
AVLTree<T>::AVLTree(const AVLTree<T> & other)
{
    if(other.root == nullptr)
        root = nullptr;
    else
        root= Copy_Tree(other.root);
}

//the function deletes the tree
template <class T>
void AVLTree<T>::Delete_Whole_Tree(Node<T> *&deleteNode)
{
    if(deleteNode!= nullptr)
    {
        Delete_Whole_Tree(deleteNode->left);
        Delete_Whole_Tree(deleteNode->right);
        delete deleteNode;
        deleteNode = nullptr;
    }
}

//overloaded operator
template <class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T> & other)
{
    if (this!=&other)
    {
        if (root != nullptr)
            Delete_Whole_Tree(root);
        if(other.root== nullptr)
            root = nullptr;
        else
            root = Copy_Tree(other.root);
    }
    return *this;
}
//Populates tree with queu values inorder
template <class T>
void AVLTree<T>::Populate_Inorder(queue<T> &st)
{

    Populate_Inorder(root, st);
}

//Populates tree with queu values inorder
template <class T>
void AVLTree<T>::Populate_Inorder(Node<T> *p, queue<T> &st)
{
    if(p!= nullptr){
        Populate_Inorder(p->left, st);
        st.push(p->info);
        Populate_Inorder(p->right, st);
    }

}

//Prints the tree nodes inorder
template <class T>
void AVLTree<T>::Print_Inorder(Node<T> *p)
{
    if(p!= nullptr)
    {
        Print_Inorder(p->left);
        cout<<p->info<<"\n";
        Print_Inorder(p->right);
    }
}

// Checks if the tree is empty
template <class T>
bool AVLTree<T> ::Is_Empty()
{
    return (root == NULL);
}

//Returns the number of nodes in the binary tree
template <class T>
int AVLTree<T>::Count_Node()
{
    return Count_Node(root);
}

//Return the number of nodes in the tree
template <class T>
int AVLTree<T>::Count_Node(Node<T>* p)
{
    if(p == nullptr)
        return 0;
    else
    {
        if(p->left== nullptr&&p->right== nullptr)
            return 1;
        else
            return 1 + Count_Node(p->left) + Count_Node(p->right);
    }

}

//Performe the statistical analysis
template <class T>
void AVLTree<T>::Statistics()
{
    int Num_Of_Words = 0 ;                  //counts the total number of words on the text
    int Num_Of_Unique_Words = 0;            //counts the total number of unique words on the text
    int Num_Of_Unique_Words_3 = 0;          //counts the unique words with up to tree letters
    int Average_Word_Length = 0;            //count for average words length
    int Average_Sentence_length = 0 ;       //count average sentence length
    int Total_Num_Of_Sentence = 0;          //count the total number of sentences
    string Word;                            //string variable for Word
    stack<string> upToTree;                 //Contains unique words with up to tree letters
    int Letter_Count = 0;                   //Count the number of letters in the Word
    queue<string> Tree_Queue;                  //Contains all the info in the tree
    AVLTree<string> tree;                   //object of the AVLTree class
    string str,text;

    cout << "ENTER THE FILE NAME: "<< endl;
    cin >> text;
    //Open file inputed by the user
    ifstream myfile(text);

    if(myfile.is_open())
    {
        while (myfile >> Word)
        {
            transform(Word.begin(), Word.end(), Word.begin(), ::tolower);

            Letter_Count+=Word.size();

            if (Word.back() == '!' || Word.back() == '?' || Word.back() == '.')
                Total_Num_Of_Sentence++;

            while (ispunct(Word.back()))
                Word.pop_back();

            while(ispunct(Word.front()))
                Word.erase(0, 1);

            Num_Of_Words++;
            tree.Insert_Item(Word);

        }
        myfile.close();

    }
    else cout << "FILE NOT FOUND"<<"\n";

    Average_Sentence_length = (Num_Of_Words / Total_Num_Of_Sentence);
    Average_Word_Length = (Letter_Count / Num_Of_Words);
    Num_Of_Unique_Words = tree.Count_Node();

    tree.Populate_Inorder(Tree_Queue);

    while(!Tree_Queue.empty())
    {
        if(Tree_Queue.front().size() > 3)
        {
            Num_Of_Unique_Words_3++;
            str = Tree_Queue.front();
            upToTree.push(str);
        }
        Tree_Queue.pop();
    }

    ofstream output;
    cout<<"\t\t\t\tSTATISTICAL SUMMARY"<<"\n\n";

    cout << "\nTOTAL NUMBER OF SENTENCES " << Total_Num_Of_Sentence;
    cout << "\nTOTAL NUMBER OF WORDS: " << Num_Of_Words;
    cout << "\nTOTAL NUMBER OF UNIQUE WORDS: " << Num_Of_Unique_Words;
    cout << "\nTOTAL NUMBER OF UNIQUE WORDS OF MORE THAN THREE LETTERS: " << Num_Of_Unique_Words_3;
    cout << "\nAVERAGE SENTENCE LENGTH: " << Average_Sentence_length << " words";
    cout << "\nAVERAGE WORD LENGTH: " << Average_Word_Length << " characters ";
    cout<<endl<<endl;

    cout<<"\t\t\t\tSTYLE WARNINGS\n\n";
    cout<<"WORDS USED TOO OFTEN: "
          "(WORDS OF MORE THAN 3 LETTERS THAT ARE USED MORE THAN 5% "
          "OF THE TOTAL NUMBER OF WORDS OF MORE THAN 3 LETTERS )\n\n";

    short count = 1;    //counter to display the order of too often used words

    while(!upToTree.empty())
    {
        if(tree.Get_Count(upToTree.top()) * Num_Of_Unique_Words_3 / 100 > 5)
            cout<<"\t"<<count++<<") "<<upToTree.top()<<"\n";
        upToTree.pop();
    }

    cout<<endl;
    if(Average_Sentence_length > 10)
        cout << "AVERAGE SENTENCE LENGTH TOO LONG - " << Average_Sentence_length << " words\n";
    if(Average_Word_Length > 5)
        cout << "AVERAGE WORD LENGTH TOO LONG - " << Average_Word_Length << " characters\n";

    char ch = 'A';      //character variable to hold fist character of the Word
    tree.Populate_Inorder(Tree_Queue);

    while(!Tree_Queue.empty())
    {
        str = Tree_Queue.front();

        if(ch!=str.at(0))
        {
            ch = str.at(0);
            cout<<"\n "<<(char)::toupper(str.at(0))<<"\n";
            cout<<"--------"<<"\n";
        }
        cout << Tree_Queue.front() << "\n";
        Tree_Queue.pop();
    }

}