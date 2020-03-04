//
// Created by Yusuf Pisan on 4/26/18.
// Created by Jonathan Young on 11/10/19
// A skiplist data structure demonstration.
//

#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

// output formatter to read skiplist contents
ostream &operator<<(ostream &Out, const SkipList &SkipL) {
    SkipList::SNode *Curr = nullptr;
    for (int I = SkipL.Depth - 1; I >= 0; I--) {
        Curr = SkipL.FrontGuards[I];
        Out << "Level: " << I << " -- " << Curr->Data;
        while (Curr->Next != nullptr) {
            Out << ", " << Curr->Next->Data;
            Curr = Curr->Next;
        }
        Out << " \n";
    }
    return Out;
}

// Snode struct constructor initializing all pointers to nullptr
SkipList::SNode::SNode(int Data) : Data(Data), Next(nullptr), Prev(nullptr),
                                   UpLevel(nullptr), DownLevel(nullptr) {}

// Constructor- initilizes front and rear guards based on depth
SkipList::SkipList(int Depth) : Depth(Depth) {
    FrontGuards = new SNode *[Depth];
    RearGuards = new SNode *[Depth];
    for (int I = 0; I < Depth; I++) {
        FrontGuards[I] = new SNode(INT_MIN);
        RearGuards[I] = new SNode(INT_MAX);
        FrontGuards[I]->Next = RearGuards[I];
        RearGuards[I]->Prev = FrontGuards[I];
        if (I > 0) {
            FrontGuards[I]->DownLevel = FrontGuards[I - 1];
            FrontGuards[I - 1]->UpLevel = FrontGuards[I];
            RearGuards[I]->DownLevel = RearGuards[I - 1];
            RearGuards[I - 1]->UpLevel = RearGuards[I];
        }
    }
}

// boolean function to determine if skiplist should progress up a level
bool SkipList::alsoHigher() const {
    if ((rand() % 2) == 1) {
        return true;
    }
    return false;
}

// return true if added, false if duplicate found.
bool SkipList::add(int Data) {
    bool NextLevel = true;
    int I = 0;
    SNode *Curr = FrontGuards[0];
    while (Data > Curr->Next->Data) {
        Curr = Curr->Next;
        if (Data == Curr->Next->Data) {
            return false;
        }
    }
    SNode *NewNode = new SNode(Data);
    addBefore(NewNode, Curr->Next);
    do {
        I++;
        if (I == Depth || !alsoHigher()) {
            NextLevel = false;
        } else {
            SNode *NewUpper = new SNode(Data);
            NewUpper->DownLevel = NewNode;
            NewNode->UpLevel = NewUpper;
            Curr = FrontGuards[I];
            while (Data > Curr->Next->Data) {
                Curr = Curr->Next;
            }
            addBefore(NewUpper, Curr->Next);
        }
    } while (NextLevel);

    return true;
}

// reassigns pointers for value that is to be added before next node
void SkipList::addBefore(SNode *NewNode, SNode *NextNode) {
    NextNode->Prev->Next = NewNode;
    NewNode->Prev = NextNode->Prev;
    NewNode->Next = NextNode;
    NextNode->Prev = NewNode;
}

// deconstructor
SkipList::~SkipList() {
    // need to delete individual nodes
    SNode *Curr;
    SNode *Temp;
    for (int I = Depth - 1; I >= 0; I--) {
        Curr = FrontGuards[I];
        while (Curr != nullptr) {
            Temp = Curr;
            Curr = Curr->Next;
            delete Temp;
        }
        delete Curr;
    }
    delete[] FrontGuards;
    delete[] RearGuards;
}

// remove function that reassigns and moves up skiplist chain reassigning all
// values
bool SkipList::remove(int Data) {
    SNode *Curr = FrontGuards[Depth - 1];
    while (Curr != nullptr) {
        if (Curr->Next->Data == Data) {
            Curr = Curr->Next;
            while (Curr->UpLevel != nullptr) {
                Curr = Curr->UpLevel;
                while (Curr->DownLevel != nullptr) {
                    Curr->Prev = Curr->Next;
                    Curr->Next->Prev = Curr->Prev;
                    Curr->Next = nullptr;
                    Curr->Prev = nullptr;
                    Curr = Curr->DownLevel;
                    Curr->UpLevel->DownLevel = nullptr;
                    Curr->UpLevel = nullptr;
                }

            }
            return true;
        }
        while (Curr->Next->Data < Data) {
            Curr = Curr->Next;
            if (Curr->Next->Data == Data) {
                return true;
            }
        }
        Curr = Curr->DownLevel;
    }
    return false;
}

// boolean function that returns true if value is found, false otherwise
bool SkipList::contains(int Data) {
    SNode *Curr = FrontGuards[Depth - 1];
    while (Curr != nullptr) {
        if (Curr->Next->Data == Data) {
            return true;
        }
        while (Curr->Next->Data < Data) {
            Curr = Curr->Next;
            if (Curr->Next->Data == Data) {
                return true;
            }
        }
        Curr = Curr->DownLevel;
    }
    return false;
}
