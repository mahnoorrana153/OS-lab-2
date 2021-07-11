// LAB NO 6


#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "vmtypes.h"



//creating a new page table

vm_addr_tlb* tlb;
vm_addr_tlb* page;
int** mem;
char rep_str;
int next_page = 0; 
int next_frame = 0; 
int page-no;
int offset_num;
int virtual_addr;
vm_addr_tlb* create-TBL(int length)
{
    vm_addr_TLB* new_table = malloc(sizeof(vm_adder_TLB));
    table->entry_age = malloc(sizeof(int) * length);
    table->length = length;
    table->page = malloc(sizeof(int) * length);
    table->frame = malloc(sizeof(int) * length);
    table->TLB_hit = 0;
    table->page_fault = 0;
    
    for (int i = 0; i < length; i++) {
        table->page[i] = 0;
    }

    if(table == NULL ) {
        print("error making new page table...");
        exit(-1);
    }
    return table;
}

//creating a backing store

#define BACKING_STORAGE_FILE "BACKING_STORE.bin"


void tbl_free(vm_adder_tlb** table)
{
    if ((*table)->page != NULL) {
        free((*table)->page);
    }
    if ((*table)->frame != NULL) {
        free((*table)->frame);
    }
    if ((*table)->entry_age != NULL) {
        free((*table)->entry_age);
    }
    free(*table);
}

int** mem_alloc(int frameCount, int blockSize)
{
    int** temp;
    temp = malloc(frameCount * sizeof(int*));
    for(int i = 0; i < frameCount; i++) {
        temp[i] = (int*)malloc(sizeof(int) * blockSize);
        for(int j = 0; j < blockSize; j++) {
            temp[i][j] = 0;
        }
    }
    return temp;
}

void free_mem(int*** dblPtrArr, int frameCount)
{
  for (int i = 0; i < frameCount; i++) {
      if ((*dblPtrArr)[i] != NULL) {
          free((*dblPtrArr)[i]);
      }
  }
  free(*dblPtrArr);
}

void backup(int page_no)
{
    char backup_buff[PAGE_SIZE];
    
    //READ a page from the backing store made previously
    FILE* backup_file;
    backup_file = fopen("BACKING_STORE.bin", "rb");
    fseek(backup_file, page_no * PAGE_SIZE, SEEK_SET) != 0
    fread(backup_buff, sizeof(signed char), PAGE_SIZE, backup_file) == 0

    // store the page frame
    for (int i = 0; i < PAGE_SIZE; i++) {
        mem[next_frame][i] = backup_buff[i];
    }
    
    page table 
    page->page[next_page] = page_no;
    page->frame[next_page] = next_frame;
    next_frame++;
    next_page++;
    //page table update in memory

    fclose(backup_file);

}


    // If the index is not equal to the number of entries
    else{

        for(i = i; i < total_indexes - 1; i++){ 
            tlb->page[i] = tlb->page[i + 1];
            tlb->frame[i] = tlb->frame[i + 1];
            // iterate through  entries
        }
        if(total_indexes < TLB_SIZE){  
            tlb->page[total_indexes] = page_no;
            tlb->frame[total_indexes] = frame_no;  // Insert the page and frame on the end

        }
        else{  
            tlb->page[total_indexes - 1] = page_no;
            tlb->frame[total_indexes - 1] = frame_no;
        }
        //put pge and frame numbers otherwise
    }
    if(total_indexes < TLB_SIZE) { 
        total_indexes++; // incrementing the Entry no
    }
}

//using LRU replacement method to enter page and frame numbers
void LRUreplace(int page_no, int frame_no)
{

    bool is_free = false;
    int index = -1;

    for (int i = 0; i < TLB_SIZE; i++)
    {
       
        if (tlb->page[i] == page_no)
        {
            tlb->entry_age[i] = 0;
            return;
            //if entry is in tlb
            
        }
        else if (tlb->page[i] != page_no)
        {
            if (tlb->page[i] == 0)
            {
                index = i;
                is_free = true;
            }
            //if entry not in tlb
            else if (tlb->page[i] != 0)
            {
                current->entryAge++;
            }
        }

        current = current->next;
    }

    if (is_free) { 
        //if any free space available, insert entry.
        tlb->page[index] = page_no;    
        tlb->frame[index] = frame_no;
        tlb->entry_age[index] = 0;
    }
    else { // If no empty space. replace some entry
        index = lru_entry(TLB_SIZE);
        tlb->page[index] = page_no;   
        // again taking oldest entry index to replace
        tlb->frame[index] = frame_no;
        tlb->entry_age[index] = 0;
    }
}


int LRUentry(int tlbSize) {
  int i, max, index;

  max = tlb->entry_age[0];
  index = 0;

  for (i = 1; i < tlbSize; i++) {
    if (tlb->entry_age[i] > max) {
       index = i;
       max = tlb->entry_age[i];
        //getting index of oldest entry in tlb to be replaced
    }
  }
  return index;
}

int main(int argc, char *argv[])
{
    tlb = tbl_create(TLB_SIZE);
    page = tbl_create(PAGE_ENTRIES);
    mem = mem_alloc(TOTAL_FRAME, FRAME_SIZE);
    int count = 0;
    char addr_buffer[10];
    FILE* address_file;

    address_file = fopen(argv[1], "r");

    if (address_file == NULL) {
        fprintf(stderr, "Error cant ope file...");
        return -1;
    }

    
        }

        if (!frame_found) {
            for(int i = 0; i < next_page; i++){
                if(page->page[i] == page_num){
                    frame_number = page->frame[i];
                    break;
                }
            }
            
            if(!frame_found) {
            page->page_fault++;
                backup(page_num);
                frame_number = next_frame - 1;
             }
        }

      
       
{LRUreplace(page_num, frame_number); //calling LRU replacement function
        
        trans_value = mem[frame_number][offset_num];
        printf("\nVirtual address: %d\t\tPhysical address: %d\t\tValue: %d", virtual_addr, (frame_number << SHIFT) | offset_num, trans_value);
        count++;
    }

    fclose(address_file);
   
    
    return 0;
}
