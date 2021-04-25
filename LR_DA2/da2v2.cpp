#pragma once
 
#include <cstdio>
 
#include "stack.hpp"
 
namespace NRB {
 
    template <class T>
    struct TNode {
        T Value;
        bool Black;
        TNode<T> *Left;
        TNode<T> *Right;
        TNode<T> *Parent;
 
        TNode(const T &value, bool black, TNode<T> *parent) : Value{value}, Black{black}, Left(nullptr), Right(nullptr), Parent{parent} {}
        TNode(const T &value, bool black) : Value{value}, Black{black}, Left(nullptr), Right(nullptr), Parent(nullptr) {}
        TNode(const TNode<T> &n) : TNode(n.Value, n.Black) {}
        TNode() : TNode(T(), true) {}
        ~TNode() {
            delete Left;
            delete Right;
        }
 
        TNode<T>* LeftRotation();
        TNode<T>* RightRotation();
        void Save(FILE *);
    };
 
    template <class T>
    class TTree {
    private:
        TNode<T> *Root;
 
    public:
        TTree() : Root{nullptr} {}
        ~TTree() {
            delete Root;
        }
 
        TNode<T>* Find(const T&);
        bool Insert(const T&);
        bool Erase(const T&);
        void Save(FILE *);
        void Load(FILE *);
    };
 
}
 
template <class T>
NRB::TNode<T>* NRB::TNode<T>::RightRotation() {
    if (Left == nullptr) {
        return nullptr;
    }
 
    NRB::TNode<T> *Root = Left;
 
    if (Parent != nullptr) {
        if (Parent->Left == this) {
            Parent->Left = Root;
        } else {
            Parent->Right = Root;
        }
    }
 
    Left = Root->Right;
    if (Left != nullptr) {
        Left->Parent = this;
    }
 
    Root->Right = this;
    Root->Parent = Parent;
    Parent = Root;
    return Root;
}
 
template <class T>
NRB::TNode<T>* NRB::TNode<T>::LeftRotation() {
    if (Right == nullptr) {
        return nullptr;
    }
 
    NRB::TNode<T> *Root = Right;
 
    if (Parent != nullptr) {
        if (Parent->Left == this) {
            Parent->Left = Root;
        } else {
            Parent->Right = Root;
        }
    }
 
    Right = Root->Left;
    if (Right != nullptr) {
        Right->Parent = this;
    }
 
    Root->Left = this;
    Root->Parent = Parent;
    Parent = Root;
    return Root;
}
 
template <class T>
NRB::TNode<T>* NRB::TTree<T>::Find(const T &value) {
    NRB::TNode<T> *iter = Root;
 
    while (iter != nullptr) {
        if (value > iter->Value) {
            iter = iter->Right;
        } else if (value < iter->Value) {
            iter = iter->Left;
        } else {
            break;
        }
    }
 
    return iter;
}
 
template <class T>
bool NRB::TTree<T>::Insert(const T &value) {
    NRB::TNode<T> *iter = Root;
 
    while (iter != nullptr) {
        if (value > iter->Value && iter->Right != nullptr) {
            iter = iter->Right;
        } else if (value < iter->Value && iter->Left != nullptr) {
            iter = iter->Left;
        } else {
            break;
        }
    }
 
    if (iter == nullptr) {
        Root = new NRB::TNode<T>(value, true);
        return true;
    }
 
    if (value > iter->Value) {
        iter->Right = new NRB::TNode<T>(value, false, iter);
        iter = iter->Right;
    } else if (value < iter->Value) {
        iter->Left = new NRB::TNode<T>(value, false, iter);
        iter = iter->Left;
    } else {
        return false;
    }
 
 
    while (iter->Parent != nullptr && iter->Parent->Parent != nullptr) {
        if (!iter->Black && !iter->Parent->Black) {
            if (iter->Parent == iter->Parent->Parent->Left) {
                if (iter->Parent->Parent->Right == nullptr || iter->Parent->Parent->Right->Black) {
                    if (iter == iter->Parent->Right) {
                        iter = iter->Parent;
                        iter->LeftRotation();
                    }
 
                    iter->Parent->Parent->Black = false;
                    iter->Parent->Black = true;
                    iter = iter->Parent->Parent->RightRotation();
                    if (iter->Right == Root) {
                        Root = iter;
                    }                
 
                } else {
                    iter->Parent->Black = true;
                    iter->Parent->Parent->Right->Black = true;
                    iter->Parent->Parent->Black = false;
                    iter = iter->Parent->Parent;
                }
            } else {
                if (iter->Parent->Parent->Left == nullptr || iter->Parent->Parent->Left->Black) {
                    if (iter == iter->Parent->Left) {
                        iter = iter->Parent;
                        iter->RightRotation();
                    }
 
                    iter->Parent->Parent->Black = false;
                    iter->Parent->Black = true;
                    iter = iter->Parent->Parent->LeftRotation();
                    if (iter->Left == Root) {
                        Root = iter;
                    }                
 
                } else {
                    iter->Parent->Black = true;
                    iter->Parent->Parent->Left->Black = true;
                    iter->Parent->Parent->Black = false;
                    iter = iter->Parent->Parent;
                }
            }
        } else {
            break;
        }
    }
 
    Root->Black = true;
    return true;
}
 
template <class T>
bool NRB::TTree<T>::Erase(const T &value) {
    NRB::TNode<T> *iter = Find(value);
 
    if (iter == nullptr) {
        return false;
    }
 
    if (iter->Left != nullptr && iter->Right != nullptr) {
        NRB::TNode<T> *old = iter;
        iter = iter->Right;
        while (iter->Left != nullptr) {
            iter = iter->Left;
        }
        old->Value = iter->Value;
    }
 
    NRB::TNode<T> *Parent = iter->Parent;
    bool Black = iter->Black;
 
    if (iter->Right != nullptr) {
        iter->Right->Parent = iter->Parent;
        if (Parent != nullptr) {
            if (iter == Parent->Left) {
                Parent->Left = iter->Right;
                iter->Right = nullptr;
                delete iter;
                iter = Parent->Left;
            } else {
                Parent->Right = iter->Right;
                iter->Right = nullptr;
                delete iter;
                iter = Parent->Right;
            }
        } else {
            Root = iter->Right;
            iter->Right = nullptr;
            delete iter;
            iter = Root;
        }
    } else if (iter->Left != nullptr) {
        iter->Left->Parent = iter->Parent;
        if (Parent != nullptr) {
            if (iter == Parent->Left) {
                Parent->Left = iter->Left;
                iter->Left = nullptr;
                delete iter;
                iter = Parent->Left;
            } else {
                Parent->Right = iter->Left;
                iter->Left = nullptr;
                delete iter;
                iter = Parent->Right;
            }
        } else {
            Root = iter->Left;
            iter->Left = nullptr;
            delete iter;
            iter = Root;
        }
    } else {
        if (Parent != nullptr) {
            if (iter == Parent->Left) {
                Parent->Left = nullptr;
            } else {
                Parent->Right = nullptr;
            }
        } else {
            Root = nullptr;
            delete iter;
            return true;
        }
        delete iter;
        iter = nullptr;
        if (Parent->Left == nullptr && Parent->Right == nullptr) {
            return true;
        }
    }
 
    if (!Black) {
        return true;
    }
 
    while (Parent != nullptr) {
        // 2
        if (iter == nullptr || iter->Black) {
            NRB::TNode<T> *brother;
            if (iter == Parent->Left) {
                brother = Parent->Right;
            } else {
                brother = Parent->Left;
            }
 
            // 2.1
            if (!brother->Black) {
                brother->Black = true;
                Parent->Black = false;
                if (brother == Parent->Left) {
                    NRB::TNode<T> *node = Parent->RightRotation();
                    if (node->Parent == nullptr) {
                        Root = node;
                    }
                } else {
                    NRB::TNode<T> *node = Parent->LeftRotation();
                    if (node->Parent == nullptr) {
                        Root = node;
                    }
                }
                continue;
            }
 
            // 2.2.1
            if ((brother->Left == nullptr || brother->Left->Black) && (brother->Right == nullptr || brother->Right->Black)) {
                brother->Black = false;
                iter = Parent;
                Parent = Parent->Parent;
                continue;
            }
 
            // 2.2.2
            if (brother == Parent->Right && (brother->Left != nullptr && !brother->Left->Black) && (brother->Right == nullptr || brother->Right->Black)) {
                brother->Black = false;
                brother->Left->Black = true;
                brother->RightRotation();
                continue;
            } else if (brother == Parent->Left && (brother->Right != nullptr && !brother->Right->Black) && (brother->Left == nullptr || brother->Left->Black)) {
                brother->Black = false;
                brother->Right->Black = true;
                brother->LeftRotation();
                continue;
            }
 
            // 2.2.3-4
            if (brother == Parent->Right && (brother->Right != nullptr && !brother->Right->Black)) {
                brother->Right->Black = true;
                brother->Black = Parent->Black;
                Parent->Black = true;
                NRB::TNode<T> *node = Parent->LeftRotation();
                if (node->Parent == nullptr) {
                    Root = node;
                }
                break;
            } else if (brother == Parent->Left && (brother->Left != nullptr && !brother->Left->Black)) {
                brother->Left->Black = true;
                brother->Black = Parent->Black;
                Parent->Black = true;
                NRB::TNode<T> *node = Parent->RightRotation();
                if (node->Parent == nullptr) {
                    Root = node;
                }
                break;
            }
 
        // 1
        } else {
            iter->Black = true;
            break;
        }
    }
    return true;
}
 
template <class T>
void NRB::TTree<T>::Save(FILE *out) {
    if (Root == nullptr) {
        return;
    }
    Root->Save(out);
}
 
template <class T>
size_t Serialize(const T& value, FILE *out) {
    return fwrite(&value, sizeof(T), 1, out);
}
 
template <class T>
size_t Deserialize(T& value, FILE *in) {
    return fread(&value, sizeof(T), 1, in);
}
 
template <class T>
void NRB::TNode<T>::Save(FILE *out) {
    Serialize(Value, out);
    fwrite(&Black, sizeof(bool), 1, out);
    if (Left != nullptr) {
        Left->Save(out);
    }
    if (Right != nullptr) {
        Right->Save(out);
    }
}
 
template <class T>
void NRB::TTree<T>::Load(FILE *in) {
    delete Root;
    bool lblack;
    T lvalue;
    if (Deserialize(lvalue, in) > 0 && fread(&lblack, sizeof(bool), 1, in) > 0) {
        Root = new NRB::TNode<T>(lvalue, lblack);
    } else {
        Root = nullptr;
        return;
    }
 
    TStack<NRB::TNode<T>*> stack;
    stack.Push(Root);
    NRB::TNode<T> *iter = nullptr;
    while (Deserialize(lvalue, in) > 0 && fread(&lblack, sizeof(bool), 1, in) > 0) {
        if (lvalue < stack.Top()->Value) {
            iter = stack.Top();
            iter->Left = new NRB::TNode<T>(lvalue, lblack);
            iter->Left->Parent = iter;
            stack.Push(iter->Left);
        } else {
            while (!stack.Empty() && lvalue > stack.Top()->Value) {
                iter = stack.Top();
                stack.Pop();
            }
            iter->Right = new NRB::TNode<T>(lvalue, lblack);
            iter->Right->Parent = iter;
            stack.Push(iter->Right);
        }
    }
}