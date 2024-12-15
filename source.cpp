#include "header.h"

// Stack
Stack createStack() {
// Mengembalikan stack yang berisi S.top = 0
    Stack S;
    S.top = 0;

    return S;
}

bool isEmpty(Stack S) {
// Mengembalikan nilai true jika nilai S.top == 0, dan false jika S.top != 0
    return S.top == 0;
}

bool isFull(Stack S) {
// Mengembalikan nilai true jika nilai S.top == MAXSIZE, dan false jika S.top != MAXSIZE
    return S.top == MAXSIZE;
}

void push(Stack &S, infoUndoRedo x) {
/*
I.S: Stack S berisi nilai untuk operasi undo/redo (bisa tidak berisi), dan infoUndoRedo i yang berisi nilai untuk dimasukkan ke Stack S
F.S: Stack S berisi nilai baru
*/
    if (!isFull(S)) {
        S.top++;
        S.info[S.top-1] = x;
    }
}

void pop(Stack &S, infoUndoRedo &x) {
/*
I.S: Stack S berisi nilai untuk operasi undo/redo (bisa tidak berisi), dan infoUndoRedo i yang akan diisi nilai dari Stack S
F.S: infoUndoRedo i berisi nilai dari Stack S
*/
    if (!isEmpty(S)) {
        x = S.info[S.top-1];
        S.top--;
    }
}

infoUndoRedo peek(Stack S) {
// Mengembalikan nilai infoUndoRedo i dari S.top Stack S
    infoUndoRedo i;

    if (!isEmpty(S)) {
        i = S.info[S.top-1];
    }

    return i;
}

// DLL
void createList(List &L, adr &Cursor) {
/*


*/
    L.first = Nil;
    L.last = Nil;
    Cursor = L.first;
}

adr createElmList(infotype value) {
    adr P = new elmList;
    P->prev = Nil;
    P->next = Nil;
    P->info = value;

    return P;
}

void insertFirst(List &L, adr &P){
    if (L.first == Nil) { // list kosong
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}

void insertAfter(List &L, adr &P, adr Prec){
    if (Prec == Nil) {
        insertFirst(L, P);
    } else if (Prec == L.last) {
        P->prev = Prec;
        Prec->next = P;
        L.last = P;
    } else { // 2 elemen setelah Prec
        P->next = Prec->next;
        P->prev = Prec;
        Prec->next->prev = P;
        Prec->next = P;
    }
}

void insertBefore(List &L, adr &P, adr Pred){
    if (Pred == Nil) { // tidak ada elemen sebelum Pred
        insertFirst(L, P);
    } else if (Pred == L.first) {
        P->next = Pred;
        Pred->prev = P;
        L.first = P;
    } else { // 2 elemen sebelum Pred
        P->prev = Pred->prev;
        P->next = Pred;
        Pred->prev->next = P;
        Pred->prev = P;
    }
}

void insertLast(List &L, adr &P){
    if (L.last == Nil) { // list kosong
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

void deleteFirst(List &L, adr &P) {
    P = L.first;
    if (L.first == L.last) { // hanya 1 elemen
        L.first = Nil;
        L.last = Nil;
    } else {
        L.first = P->next;
        L.first->prev = Nil;
        P->next = Nil;
    }
}

void deleteAfter(List &L, adr &P, adr Pred){
    P = Pred->next;
    if (Pred->next == L.last) {
        deleteLast(L, P);
    } else if (Pred->next->next != Nil) { // 2 elemen setelah Pred
        P = Pred->next;
        Pred->next = P->next;
        (P->next)->prev = Pred;
        P->next = Nil;
        P->prev = Nil;
    }
}

void deleteBefore(List &L, adr &P, adr Pred) {
    P = Pred->prev;
    if (Pred->prev == L.first) {
        deleteFirst(L, P);
    } else if (Pred->prev->prev != Nil) { // 2 elemen setelah Pred
        P = Pred->prev;
        Pred->prev = P->prev;
        P->prev->next = Pred;
        P->next = Nil;
        P->prev = Nil;
    }
}

void deleteLast(List &L, adr &P) { // hanya 1 elemen
    P = L.last;
    if (L.first == L.last){
        L.first = Nil;
        L.last = Nil;
    } else {
        L.last = P->prev;
        P->prev = Nil;
        L.last->next = Nil;
    }
}

void printText(List L) {
    adr P = L.first;
    while (P != Nil) {
        if (P->info == '_') {
            cout << " ";
        } else {
            cout << P->info;
        }
        P = P->next;
    }
    cout << endl;
}

void printTextWithCursor(List L, adr C) {
    adr P = L.first;
    while (P != Nil) {
        if (P == C) {
            cout << "[" << P->info << "]"; // Penanda kursor
        } else if (P->info == '_') {
            cout << " ";
        } else {
            cout << P->info;
        }
        P = P->next;
    }
    cout << endl;
}

void addText(List &L, adr &C, Stack &U) {
    adr P;
    infotype v;
    do {
        cin >> v;
        if (v != ';') {
            P = createElmList(v);
            push(U, {"Input", P});
            insertAfter(L, P, C);
            C = P;
        }
    } while (v != ';');
}

void moveCursorLeft(List &L, adr &C) {
    if (C != L.first) { // kursor tidak di first
        C = C->prev;
    }
}

void moveCursorRight(List &L, adr &C) {
    if (C != L.last) { // kursor tidak di last
        C = C->next;
    }
}

void DeleteOnCursor(List &L, adr &C, adr &P, string &Act){
    adr tempP;
    if (L.first != Nil && C != Nil) {
        if (L.first == L.last) {
            deleteFirst(L, P);
            C = L.first;
            Act = "Delete First";
        } else if (C == L.first) {
            moveCursorRight(L, C);
            deleteFirst(L, P);
            Act = "Delete First";
        } else if (C == L.last) {
            moveCursorLeft(L, C);
            deleteLast(L, P);
            Act = "Delete Last";
        } else {
            moveCursorLeft(L, C);
            deleteAfter(L, P, C);
            Act = "Delete Between";
        }
    }
}

// Menu
void input_text(List &L, adr &C, Stack &U) {
/*
I.S: terdefisini list L menyimpan elemen char, adr C menyimpan posisi cursor saat ini, dan stack U untuk menyimpan info undo
F.S: list L berisi nilai setelah memanggil prosedur addText
*/
    cout << "Text: " << endl; printTextWithCursor(L, C);
    cout << "Ketik text yang ingin dimasukkan: " << endl;
    addText(L, C, U);

    cout << "Text: " << endl; printText(L); cout << endl;
}

void print_text(List L) {
/*
I.S: terdefinisi list L menyimpan elemen char
F.S: menampilkan text jika list L berisi elemen
*/
    if (L.first == Nil) { // list L kosong
        cout << "Text tidak tersedia." << endl;
    } else { // list L tidak kosong
        cout << "Text: " << endl; printText(L); cout << endl;
    }
}

void pindahkan_kursor_atau_hapus_teks(List &L, adr &C, Stack &U) {
/*
I.S: terdefisini list L menyimpan elemen char, adr C menyimpan posisi cursor saat ini, dan stack U untuk menyimpan info undo
F.S: memindahkan kursor atau men-delete pada posisi kursor berdasarkan pilihan user
*/
    int pilih;
    adr tempP, P;
    string aksi;

    if (L.first != Nil) { // list L tidak kosong
        do {
            printTextWithCursor(L, C);
            cout << "(1)Kiri (2)Kanan (3)Delete (0)Keluar" << endl;
            cin >> pilih;

            if (pilih == 1) { // memilih move cursor left
                moveCursorLeft(L, C);
                push(U, {"Kursor Kiri", Nil});
            } else if (pilih == 2) { // memilih move cursor right
                moveCursorRight(L, C);
                push(U, {"Kursor Kanan", Nil});
            } else if (pilih == 3) { // memilih delete char pada posisi cursor
                tempP = P;
                DeleteOnCursor(L, C, P, aksi);
                if (tempP != P) {
                    push(U, {aksi, P});
                }
            }
        } while (pilih != 0); // keluar menu
    } else { // list L kosong
        cout << "Teks tidak tersedia." << endl;
    }
}

void cari_kata(List L) {
/*
I.S: terdefinisi list L menyimpan elemen char
F.S: menampilkan text dengan kata yang dicari diapit dengan kurung siku ([])
*/
    bool status = false;
    adr first = Nil, last = Nil;
    adr P, R;
    string X, kata;
    int countKata = 0;

    if (L.first != Nil) { // list L tidak kosong
        cout << "Kata yang ingin dicari: ";
        cin >> X; // menginput kata yang ingin dicari

        P = L.first;
        while (P != Nil) { // pencarian berjalan ketika pointer P tidak Nil
            kata = "";
            first = P;
            while (P != Nil && P->info != '_') { // kumpulkan karakter sampai karakter "_" (spasi)
                kata += P->info;
                last = P;
                P = P->next;
            }
            R = first;
            if (kata == X) { // membandingkan penjumlahan elemen diatas dengan X (kata yang ingin dicari
                countKata++;
                while (R != last->next) { // jika sesuai, maka menampikan text dilayar dimana kata yang dicari diapit oleh kurung siku ([])
                    if (R == first) {
                        cout << "[" << R->info;
                    } else if (R == last) {
                        cout << R->info << "]";
                    } else {
                        cout << R->info;
                    }
                    R = R->next;
                }
            } else { // jika kata tidak sesuai, tampilkan kata itu
                while (R != last->next) {
                    cout << R->info;
                    R = R->next;
                }
            }
            if (P != Nil && P->info == '_') {
                cout << " ";
                P = P->next; // Lanjutkan pencarian setelah karakter '_'
            }
        }

        if (countKata > 0) { // menampilkan kata sudah ditemukan berapa kali
            cout << endl << "Menemukan kata " << X << " sebanyak " << countKata << " kali." << endl;
        } else { // jika countKata = 0
            cout << endl << "Kata tidak ditemukan." << endl;
        }
    } else { // list L kosong
        cout << "Teks tidak tersedia." << endl;
    }
}

// undo redo
void doUndo(List &L, Stack &U, Stack &R, adr &C) {
/*
I.S: terdefinisi list L menyimpan elemen char, stack U dan R yang menyimpan history aksi, dan adr C yang menyimpan posisi cursor
F.S: list L dan adr C ter-Undo sampai bertemu aksi input atau delete dan menyimpan aksi di stack R
*/
    infoUndoRedo x;
    adr P;
    string tempString;
    bool status = false;
    if (isEmpty(U)) { // stack U kosong
        cout << "Tidak ada aksi undo." << endl;
        return;
    }
    while (!isEmpty(U) && !status) { // stack U tidak kosong
        pop(U, x); // pop stack undo
        if (x.aksi == "Kursor Kiri") {
            moveCursorRight(L, C);
        } else if (x.aksi == "Kursor Kanan") {
            moveCursorLeft(L, C);
        } else if (x.aksi == "Input") {
            DeleteOnCursor(L, C, P, tempString);
            status = true;
        } else if (x.aksi == "Delete First") {
            insertFirst(L, x.address);
            status = true;
        } else if (x.aksi == "Delete Last") {
            insertLast(L, x.address);
            status = true;
        } else if (x.aksi == "Delete Between") {
            insertAfter(L, x.address, C);
            status = true;
        }
        push(R, x); // push stack redo
    }
}

void doRedo(List &L, Stack &R, Stack &U, adr &C) {
/*
I.S: terdefinisi list L menyimpan elemen char, stack U dan R yang menyimpan history aksi, dan adr C yang menyimpan posisi cursor
F.S: list L dan adr C ter-Redo sampai bertemu aksi input atau delete dan menyimpan aksi di stack U
*/
    infoUndoRedo x;
    adr P;
    string tempString;
    bool status = false;
    if (isEmpty(R)) { // stack U kosong
        cout << "Tidak ada aksi redo." << endl;
        return;
    }
    while (!isEmpty(R) && !status) { // stack U tidak kosong
        pop(R, x); // pop stack redo
        if (x.aksi == "Kursor Kiri") {
            moveCursorLeft(L, C);
        } else if (x.aksi == "Kursor Kanan") {
            moveCursorRight(L, C);
        } else if (x.aksi == "Input" && x.address != Nil) {
            insertAfter(L, x.address, C);
            C = x.address;
            status = true;
        } else if (x.aksi == "Delete First") {
            DeleteOnCursor(L, C, P, tempString);
            status = true;
        } else if (x.aksi == "Delete Last") {
            DeleteOnCursor(L, C, P, tempString);
            status = true;
        } else if (x.aksi == "Delete Between") {
            DeleteOnCursor(L, C, P, tempString);
            status = true;
        }
        push(U, x); // push stack undo
    }
}

void undo_redo(List &L, Stack &U, Stack &R, adr &C) {
/*
I.S: terdefinisi list L menyimpan elemen char, stack U dan R yang menyimpan history aksi, dan adr C yang menyimpan posisi cursor
F.S: list L, Stack U, Stack R, dan adr C berubah berdasarkan pilihan yang dipilih user
*/
    int pilih;

    if (L.first != Nil) {
        do {
            printTextWithCursor(L, C);
            cout << "(1)Undo (2)Redo (0)Keluar" << endl;
            cin >> pilih;

            if (pilih == 1) {
                doUndo(L, U, R, C);
            } else if (pilih == 2) {
                doRedo(L, R, U, C);
            }
        } while (pilih != 0);
    } else {
        cout << "Teks tidak tersedia." << endl;
    }
}
