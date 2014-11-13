#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;

template<typename Type> class AVLTree
{
private:
    struct Node
    {

    };
};

#endif // AVLTREE_H


class AVLNode
{
    int element;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode (int theElem, AVLNode* l, AVLNode* r, int h = 0): element(theElem), left(l), right(r), height(h){}

    friend class AVLTree;
};

class AVLTree
{
    private:
        AVLNode* root;
        void insert (int val, AVLNode&* t){}
        int height(AVLNode* t)
        {
            return (t == nullptr? -1 : t->height);
        }

    public:
        void insert(int);
};

//begin private insert method
void AVLTree::insert(int val, AVLNode*& t)
{
    if (t == nullptr)
        t = new AVLNode(val, nullptr, nullptr);
    //element is smaller than current element
    else if (val < t->element)
    {
        insert(val, t->left);
        //if this is true it is either case 1 or case 2
        if (height(t->left)-height(t->right) == 2)
        {
            //check for case 1
            if(val < t->left->element)
                rotateWithLeftChild(t);
            //otherwise is case 2
            else
                doubleWithLeftChild(t);
        }
    }
    //element is bigger than current element
    else if (t->element < val)
    {
        insert(val, t->right);
        //if true is either case 3 or case 4
        if(height(t->right) - height(t->left) == 2)
        {
            //check for case 4
            if(val > t->right->element)
                rotateWithRightChild(t);
            //otherwise is case 3
            else
                doubleWithRightChild(t);
        }
    }

    t->height = max(height(t->left), height(t->right) + 1);

}
//end private insert method

void AVLTree::rotateWithLeftChild(AVLNode*& k1) //k1 is a reference variable for the pointer to the parent of alpha. k1 is alpha, k2 is the child?
{
    AVLNode* k2 = k1->left; //bad line of code
    k1->left = k2->right;	//bad line of code
    k2->right = k1;
    k1->height = max(height(k1->left), height(k1->right) + 1);
    k2->height = max(height(k2->left), height(k2->right) + 1);
    k1 = k2;
}

void AVLTree::rotateWithRightChild(AVLNode*& k2)
{
    //same but opposite of left
}

void AVLTree::doubleWithLeftChild(AVLNode*& k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void AVLTree::doubleWithRightChild(AVLNode*& k2)
{
    rotateWithLeftChild(k2->left);
    rotateWithRightChild(k2);
}
