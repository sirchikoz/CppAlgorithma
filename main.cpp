/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: echiliboyi
 *
 * Created on June 29, 2018, 11:34 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

/*
 * 
 */
struct node{
    int key=0;
    node* parent=nullptr;
    node* left=nullptr;
    node* right=nullptr;
};
void print(node* n);
node minimum(node* tr);
node maximum(node* tr);
node* search(node* tree, int key);
void buildtree(node *tree, node& n);
void transplant(node* u, node* v);
void deletenode(node* n);
int main(int argc, char** argv) {
    node nm,*tree;
    nm.key=50;  
    tree = &nm;
    node one, two, three, four, five, six, seven,eight, nine;
    one.key=90;
    two.key=100;
    three.key=6;
    four.key=20;
    five.key=1000;
    six.key=28;
    seven.key=35;
    eight.key=8;
    nine.key=12;
    node nodes[]{one, two, three,four,five,six,seven,eight};

    for(int i=0; i<9; i++)
    buildtree(tree, nodes[i]);
    print(tree);
    deletenode(&nodes[4]);
    cout<<"\n";
    print(tree);
    node* result = search(tree,100);
    if(result)
        cout<<"\nResult: "<<result->key;
    
     cout<<"\nMinimum: "<<minimum(tree).key<<" Maximum: "<<maximum(tree).key;
    return 0;
}
void print(node* n){
    if(n!=nullptr){
       print(n->left);
       cout<<n->key<<" ";
        print(n->right);
    }
}
    node minimum(node* tr){
        node* t = tr->left;
        node* x = tr->left;
        while(t){
            x=t;
            t = t->left;
        }
        return *x;
    }
    node maximum(node* tr){
        node* t = tr->right;
        node* x = tr->right;
        
        while(t){
            x=t;
            t = t->right;
        }
        return *x;
    }
    void buildtree(node *tree, node& n){
       node* temp = tree;
       node* x = tree;
       node* arg=&n;
       while(temp && x->key != arg->key)
        {   x = temp;
            if(temp->key > arg->key)
            {              
                temp = temp->left;
            }else if(temp->key < arg->key)
            {
                temp = temp->right;
            }
        }
        node* y=nullptr;
        if(x->key >= arg->key){
           y = x->left;
            arg->parent = x;
            arg->left = y;
           if(y!=nullptr)
              y->parent = arg;
           x->left=arg;
        }else
        {
            y = x->right;
            arg->parent = x;
            arg->right = y;
           if(y!=nullptr)
              y->parent = arg;
           x->right=arg;
        }
    }
    void transplant(node* u, node* v){
        node* unode = u;
        node* vnode = v;
        node* up = unode->parent;
        if(unode == up->left){
           up->left = vnode;
        }
        else{
            up->right=vnode;
        }
        if(vnode)
            vnode->parent=up;
    }
    void deletenode(node* n){
        node* temp = n;       
        if(temp->left==nullptr){
                   transplant(temp, temp->right);
        }
        else if(temp->right==nullptr){
            transplant(temp, temp->left);
        }else{
            node x = minimum(temp->right);
            node* y = &x;
            if(y->parent!=nullptr){
                transplant(y, y->right);
                y->right=temp->right;
                y->right->parent=y;
            }
            transplant(temp,y);
            y->left=temp->left;
            y->left->parent=y;
        }
        temp->parent = nullptr;
    }
    node* search(node* tree, int key){
        if(tree==nullptr || key == tree->key ){
            return tree;
        }
        if(key < tree->key)
            return search(tree->left, key);
        else
            return search(tree->right, key);
    }