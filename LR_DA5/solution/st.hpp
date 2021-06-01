#pragma once

#include <vector>
#include <map>
#include <string>
#include <algorithm>

class TSuffArr;

class TNode
{
public:
    TNode(std::string::iterator, std::string::iterator);
    ~TNode() {};
    std::map<char, TNode*> v;
    std::string::iterator start;
    std::string::iterator end;
    TNode* suff_link;
};

class TSuffTree
{
public:
    TSuffTree(std::string const&);
    ~TSuffTree();
    friend TSuffArr;
private:
    std::string text;
    TNode* root;
    TNode* curr_suff_link;
    TNode* activ_node;
    int remainder;
    int activ_length;
    std::string::iterator activ_edge;
    void Destroy(TNode*);
    void SuffLinkAdd(TNode*);
    void DFS(TNode*, std::vector<int>&, int const&);
    void Create(std::string::iterator);
    bool GoDown(std::string::iterator, TNode*);
};

class TSuffArr
{
public:
    TSuffArr(TSuffTree* tree);
    ~TSuffArr() {};
    std::vector<int> Find(std::string const&);
private:
    int FindLeft(std::string const&);
    int FindRight(std::string const&);
    std::string text;
    std::vector<int> arr;
};
