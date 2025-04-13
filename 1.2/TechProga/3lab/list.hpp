#include <iostream>

using namespace std;

const int BLOCK_SIZE = 2;
const int INDEX_TABLE_SIZE = 8;

struct Element {
    char a;
    int b[2], c[2];
    char d;

    void input(){
        cout << "Введите букву: ";
        cin >> a;
        cout << "Введите два числа: ";
        cin >> b[0] >> b[1];
        cout << "Введите два числа: ";
        cin >> c[0] >> c[1];
        cout << "Введите букву: ";
        cin >> d;
    }

    void print(){
        cout << a << " " << b[0] << " " << b[1] << " " << c[0] << " " << c[1] << " " << d << '\n';
    }
};

struct Block {
    Element elements[BLOCK_SIZE];
    Block *next;
    Block *previous;
    int size;

    Block(): elements{}, previous{nullptr}, next{nullptr}, size{0} {}
};

struct IndexTableRow {
    Block *block;
    int Element_index;
    int Block_index;

    void clear(){
        block = nullptr;
        Element_index = -1;
        Block_index = -1;
    }

    IndexTableRow(): block{nullptr}, Element_index{-1}, Block_index{-1} {}
};

struct BlockList {
    IndexTableRow table[INDEX_TABLE_SIZE];
    Block *head;
    Block *tail;
    int BlocksNumber;
    int Size;

    BlockList(): table{}, head{nullptr}, tail{nullptr}, BlocksNumber{0}, Size{0} {}

    void updateIndexTable(){
        for (int i = 0; i < 8; i++) table[i].clear();
        int step = max(1, BlocksNumber / INDEX_TABLE_SIZE);
        Block *current = head;
        int count = 0;
        int index = 0;
        for (int i = 0; i < INDEX_TABLE_SIZE && current != nullptr; i++){
            while (current != nullptr && count % step != 0){
                index += current->size;
                count++;
                current = current->next;
            }
            if (current != nullptr) {
                table[i].block = current;
                table[i].Block_index = count;
                table[i].Element_index = index;
                index += current->size;
                count++;
                current = current->next;
            }
        }
    }

    pair<Block*, int> Search(int index){
        index--;
        int i = 0;
        for (; i < INDEX_TABLE_SIZE && table[i].block != nullptr && table[i].Element_index <= index; i++) {}
        i--;
        Block* current = table[i].block;
        int cur_ind = table[i].Element_index;
        while (current != nullptr){
            if (cur_ind <= index && index <= cur_ind + current->size) break;
            cur_ind += current->size;
            current = current->next;
        }
        return {current, cur_ind};
    }

    void push_back(Element el){
        if (tail == nullptr){
            Block *newBlock = new Block;
            newBlock->elements[0] = el;
            newBlock->size++;
            tail = newBlock;
            head = newBlock;
            Size++;
            BlocksNumber++;
        }
        else if (tail->size == BLOCK_SIZE){
            Block *newBlock = new Block;
            newBlock->elements[0] = el;
            newBlock->size++;
            tail->next = newBlock;
            newBlock->previous = tail;
            if (BlocksNumber == 1) head = tail;
            tail = newBlock;
            if (BlocksNumber == 1) head->next = tail, tail->previous = head;
            Size++;
            BlocksNumber++;
        }
        else{
            tail->elements[tail->size] = el;
            tail->size++;
            Size++;
        }
        updateIndexTable();
        cout << "Элемент добавлен!\n";
    }

    void push_front(Element el){
        if (head == nullptr){
            Block *newBlock = new Block;
            newBlock->elements[0] = el;
            newBlock->size++;
            head = newBlock;
            tail = newBlock;
            Size++;
            BlocksNumber++;
        }
        else if (head->size == BLOCK_SIZE){
            Block *newBlock = new Block;
            newBlock->elements[0] = el;
            newBlock->size++;
            newBlock->next = head;
            head->previous = newBlock;
            if (BlocksNumber == 1) tail = head;
            head = newBlock;
            if (BlocksNumber == 1) head->next = tail, tail->previous = head;
            Size++;
            BlocksNumber++;
        }
        else{
            for (int i = head->size; i > 0; i--) head->elements[i] = head->elements[i - 1];
            head->elements[0] = el;
            head->size++;
            Size++;
        }
        updateIndexTable();
        cout << "Элемент добавлен!\n";
    }

    void InsertAt(Element el, int index){
        pair<Block*, int> par = Search(index);
        Block* block = par.first;
        int ind = par.second;
        index -= ind;
        index--;
        if (block->size != BLOCK_SIZE) {
            for (int i = block->size; i > index; i--){
                block->elements[i] = block->elements[i - 1];
            }
            block->elements[index] = el;
            block->size++;
        }
        else {
            Block* newBlock = new Block;
            if (block->next != nullptr){
                block->next->previous = newBlock;
                newBlock->next = block->next;
                block->next = newBlock;
                newBlock->previous = block;
            }
            else {
                block->next = newBlock;
                newBlock->previous = block;
            }
            newBlock->elements[0] = block->elements[block->size - 1];
            newBlock->size++;
            for (int i = block->size - 1; i > index; i--){
                block->elements[i] = block->elements[i - 1];
            }
            block->elements[index] = el;
            BlocksNumber++;
        }
        Size++;
        updateIndexTable();
    }

    void DeleteAt(int index){
        pair<Block*, int> par = Search(index);
        Block* block = par.first;
        int ind = par.second;
        index -= ind;
        index--;
        if (block->size == 1){
            if (block->previous != nullptr && block->next != nullptr){
                block->previous->next = block->next;
                block->next->previous = block->previous;
                delete block;
            }
            else if (block->previous != nullptr){
                block->previous->next = nullptr;
                tail = block->previous;
                delete block;
            }
            else if (block->next != nullptr){
                block->next->previous = nullptr;
                head = block->next;
                delete block;
            }
            else {
                delete block;
                head = nullptr;
                tail = nullptr;
            }
            BlocksNumber--;
        }
        else {
            for (int i = index; i < block->size - 1; i++){
                block->elements[i] = block->elements[i + 1];
            }
            block->size--;
        }
        Size--;
        updateIndexTable();
    }

    void UpdateAt(Element el, int index){
        pair<Block*, int> par = Search(index);
        Block* block = par.first;
        int ind = par.second;
        index -= ind;
        index--;
        block->elements[index] = el;
        cout << "Элемент обновлен!\n";
    }

    void GetByIndex(int index){
        pair<Block*, int> par = Search(index);
        Block* block = par.first;
        int ind = par.second;
        index -= ind;
        index--;
        block->elements[index].print();
    }

    void Clear(){
        Block *current = head;
        while (current != nullptr){
            Block *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        Size = 0;
        BlocksNumber = 0;
        for (int i = 0; i < 8; i++) table[i].clear();
    }

    void PrintData(){
        cout << '\n';
        Block *current = head;
        int curBlock = 1;
        int ind = 1;
        while (current != nullptr) {
            cout << "[" << curBlock << "] блок\n";
            for (int i = 0; i < current->size; i++) {
                cout << "    [" << ind++ << "] элемент: ";
                current->elements[i].print();
            }
            curBlock++;
            current = current->next;
        }
        cout << '\n';
    }

    void PrintExtraInfo(){
        cout << '\n';
        cout << "Всего элементов: " << Size << '\n';
        cout << "Кол-во блоков: " << BlocksNumber << '\n';
        cout << "Индексная таблица:\n";
        for (int i = 0; i < INDEX_TABLE_SIZE; i++){
            if (table[i].block != nullptr){
                cout << table[i].Element_index + 1 << " " << table[i].Block_index + 1 << " " << table[i].block << '\n';
            }
        }
    }
};