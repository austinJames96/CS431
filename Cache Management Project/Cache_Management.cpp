//
//  Cache_Management.cpp
//  
//
//  Created by Anthony Gurovski on 12/6/19.
//

#include "Cache_Management.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>


using namespace std;

int EffectiveAccessTime(int memoryAccessTime, int TLBAccessTime, int hit_ratio){
    int TLB_hit_time = TLBAccessTime + memoryAccessTime;
    int TLB_miss_time = TLBAccessTime + 2*memoryAccessTime;
    int EAT = TLB_miss_time * (1-hit_ratio) + TLB_hit_time * hit_ratio;
}

int randomAccess(){
    
}

int main()
{
    srand (time(NULL));
    Cache pageTable = Cache(256, 500); // Page table size 256 access time 500
    Cache TLB = Cache(4, 20); // TLB size of 4 access time 20
    unsigned char Memory[65536];
    for(int i = 0; i < 65536; i++) // Make an Array of memory of random uchar
        Memory[i] = rand() % 256;
    
    // Fill in page table with blank entries
    for(int i = 0; i < pageTable.size; i++)
    {    pageTable.insertPTE(PTE(i,(i+4)%256,(bool)(rand()%2),(bool)(rand()%2),(bool)(rand()%2), (bool)(rand()%2)), i);
    }
    
    // CACHE, TLB, AND MEMORY ARE ALL FILLED
    // 16 BIT VIRTUAL ADDRESSES
    
    TLB.Push(pageTable.Entries[4]);
    TLB.Push(pageTable.Entries[5]);
    TLB.Push(pageTable.Entries[6]);
    TLB.Push(pageTable.Entries[7]);
    TLB.Push(pageTable.Entries[8]);
    for (int i = 0; i < 4; i++)
    {
        cout << TLB.Entries[i].printPTE() << endl;
    }

    int numberofHits;
    int numberofAccesses;
    int memoryAccessTime = 500;
    int TLBAccessTime = 20;
    int hit_ratio = numberofHits / numberofAccesses;

    EffectiveAccessTime(memoryAccessTime, TLBAccessTime, hit_ratio);

    return 0;
}

