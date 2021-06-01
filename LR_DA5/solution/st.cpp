#include "st.hpp"

TSuffTree::TSuffTree(std::string const& string) : text(string), root(new TNode(text.end(), text.end())), remainder(0)
{
    activ_edge = text.begin();
    activ_node = root;
    root->suff_link = root;
    curr_suff_link = root;
    activ_length = 0;
    for(std::string::iterator suff = text.begin(); suff != text.end(); ++suff) { Create(suff); }
}

TNode::TNode(std::string::iterator start, std::string::iterator end) : start(start), end(end), suff_link(nullptr) {}

void TSuffTree::Destroy(TNode* node)
{
    for(std::map<char, TNode*>::iterator it = node->v.begin(); it != node->v.end(); ++it) { Destroy(it->second); }
    delete node;
}

TSuffTree::~TSuffTree() { Destroy(root); }

void TSuffTree::Create(std::string::iterator pos)
{
    curr_suff_link = root;
    ++remainder;
    while(remainder)
    {
        if(!activ_length) { activ_edge = pos; }
        std::map<char, TNode*>::iterator v = activ_node->v.find(*activ_edge);
        TNode* next;
        if(v == activ_node->v.end())
        {
            TNode* leaf = new TNode(pos, text.end());
            activ_node->v[*activ_edge] = leaf;
            SuffLinkAdd(activ_node);
        }
        else
        {
            next = v->second;
            if(GoDown(pos, next)) { continue; }
            if(*(next->start + activ_length) == *pos)
            {
                ++activ_length;
                SuffLinkAdd(activ_node);
                break;
            }
            TNode* split = new TNode(next->start, next->start + activ_length);
            TNode* leaf  = new TNode(pos, text.end());

            activ_node->v[*activ_edge] = split;
            split->v[*pos] = leaf;
            next->start += activ_length;
            split->v[*next->start] = next;
            SuffLinkAdd(split);
        }
        --remainder;
        if(activ_node == root && activ_length)
        {
            --activ_length;
            activ_edge = pos - remainder + 1;
        }
        else
        {
            activ_node = (activ_node->suff_link) ? activ_node->suff_link : root;
        }
    }
}

bool TSuffTree::GoDown(std::string::iterator pos, TNode* node)
{
    int length = 0;
    if(pos + 1 < node->end) { length = pos + 1 - node->start; }
    else { length = node->end - node->start; }
    if(activ_length  >= length)
    {
        activ_edge += length;
        activ_length -= length;
        activ_node = node;
        return true;
    }
    return false;
}

void TSuffTree::SuffLinkAdd(TNode* node)
{
    if(curr_suff_link != root) { curr_suff_link->suff_link = node; }
    curr_suff_link = node;
}

void TSuffTree::DFS(TNode* node, std::vector<int>& result, int const& deep)
{
    if(node->v.empty())
    {
        result.push_back(text.size() - deep);
        return;
    }
    for(std::map<char, TNode*>::iterator it = node->v.begin(); it != node->v.end(); ++it)
    {
        int tmp = deep;
        tmp += it->second->end - it->second->start;
        DFS(it->second, result, tmp);
    }
}

TSuffArr::TSuffArr(TSuffTree* tree) : text(tree->text), arr()
{
    tree->DFS(tree->root, arr, 0);
}


int TSuffArr::FindLeft(std::string const& pattern)
{
    int left = 0;
    int right = text.size() - 1;
    int length = pattern.size();
    while(left <= right)
    {
        int mid = (left + right) / 2;
        std::string tmp = text.substr(arr[mid], length);
        if(pattern > tmp) { left = mid + 1; }
        else { right = mid - 1; }
    }
    return left;
}

int TSuffArr::FindRight(std::string const& pattern)
{
    int left = 0;
    int right = text.size() - 1;
    int length = pattern.size();
    while(left <= right)
    {
        int mid = (left + right) / 2;
        std::string tmp = text.substr(arr[mid], length);
        if(pattern >= tmp) { left = mid + 1; }
        else { right = mid - 1; }
    }
    return left;
}

std::vector<int> TSuffArr::Find(std::string const& pattern)
{
    int left = FindLeft(pattern);
    int right = FindRight(pattern);
    std::vector<int> result;
    for(int i = left; i < right; ++i) { result.push_back(arr[i]); }
    std::sort(result.begin(), result.end());
    return result;
}
