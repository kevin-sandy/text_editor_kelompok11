#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#define Nil NULL

#include <iostream>

using namespace std;

// DLL
typedef struct elmList *adr;
typedef char infotype;
struct elmList {
    infotype info;
    adr prev, next;
};
struct List {
    adr first, last;
};

// Stack
const int MAXSIZE = 999;
struct infoUndoRedo {
    string aksi;
    adr address;
};
typedef int index;
struct Stack {
    infoUndoRedo info[MAXSIZE];
    index top;
};

Stack createStack();

bool isEmpty(Stack S);

bool isFull(Stack S);

void push(Stack &S, infoUndoRedo x);

void pop(Stack &S, infoUndoRedo &x);

infoUndoRedo peek(Stack S);

// DLL

void createList(List &L, adr &C);

adr createElmList(infotype value);

void insertFirst(List &L, adr &P);

void insertAfter(List &L, adr &P, adr prec);

void insertLast(List &L, adr &P);

void deleteFirst(List &L, adr &P);

void deleteAfter(List &L, adr &P, adr Prec);

void deleteBefore(List &L, adr &P, adr Pred);

void deleteLast(List &L, adr &P);

void printText(List L);

void printTextWithCursor(List L, adr C);

void addText(List &L, adr &C);

adr setCursor(List &L);

void moveCursorLeft(List &L, adr &C);

void moveCursorRight(List &L, adr &C);

void DeleteOnCursor(List &L, adr &C, adr &P);

// Menu
void input_text(List &L, adr &C, Stack &U);

void print_text(List L);

void pindahkan_kursor_atau_hapus_teks(List &L, adr &C, Stack &U);

void cari_kata(List L);

void ubah_huruf(List &L, adr &C, Stack &U);

void doUndo(List &L, Stack &U, Stack &R, adr &C);

void doRedo(List &L, Stack &R, Stack &U, adr &C);

void undo_redo(List &L, Stack &U, Stack &R, adr &C);

#endif // HEADER_H_INCLUDED
