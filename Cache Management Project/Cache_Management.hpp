//
//  Cache_Management.hpp
//  
//
//  Created by Anthony Gurovski on 12/6/19.
//

#ifndef Cache_Management_hpp
#define Cache_Management_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
/*
 PTE CLASS
 Has a VPN, dirty bit protected bit, valid bit, present bit, etc. Making it all public just so it's easy.
 */


class PTE
{
    public:
    int VPN;
    //int FN; Sounds like this is a maybe
    int PFN;
    bool dirtyBit;
    bool protectedBit;
    bool validBit;
    bool presentBit;
    PTE();
    PTE(int V, int P, bool dB, bool pB, bool vB, bool prsntB);
    string printPTE(); // Prints out a page table entry to help with debugging
};

// GENERIC CONSTRUCTOR FOR MAKING ARRAYS
PTE::PTE(){}

PTE::PTE(int V, int P, bool dB, bool pB, bool vB, bool prsntB)
{
    VPN = V;
    PFN = P;
    dirtyBit = dB;
    protectedBit = pB;
    validBit = vB;
    presentBit = prsntB;
}
string PTE::printPTE()
{
    return "VPN = " + to_string(VPN)
            + " PFN = " + to_string(PFN)
            + " DB = " + to_string(dirtyBit)
            + " PB = " + to_string(protectedBit)
            + " VB = " + to_string(validBit)
            + " PRSNTB = " + to_string(presentBit);
}

/*
 CACHE CLASS
 This has a size, access time, and an array of page table entries. All is public again to make accessing it easy.
 Constructor just takes a size and an access time
 
 */

class Cache
{
    public:
    int size;
    int atime;
    PTE* Entries; // Made this a pointer like this so I can make it different sizes.
    
    Cache(int s, int at);
    PTE insertPTE(PTE pte, int e); // PTE is the table entry, e is which spot
    int isInCache(int VPN);
    void Push(PTE pte);
};

Cache::Cache(int s, int at)
{
    size = s;
    atime = at;
    Entries = new PTE[size];
}

// Inserts a PTE into the entries array in spot e
PTE Cache::insertPTE(PTE pte, int e)
{
    Entries[e] = pte;
    return Entries[e];
}

// Returns a 1 if the VPN is in the CACHE, 0 if it isn't
int Cache::isInCache(int VPN)
{
    for(int i = 0; i < size; i++)
    {
        if (VPN == Entries[i].VPN)
        {
            return 1;
        }
    }
    return 0;
}
// Pushes a PTE into the cache as if it's a stack
void Cache::Push(PTE pte)
{
    for(int i = size-2; i >= 0; i--)
    {
        Entries[i+1] = Entries[i];
    }
    Entries[0] = pte;
}

#endif /* Cache_Management_hpp */
