#include "header.h"

int main() {
    List Text;
    Stack Undo, Redo;
    adr Cursor;
    adr temp;
    int pilih;

    createList(Text, Cursor);
    Undo = createStack();
    Redo = createStack();

    printf("- Text Editor Kelompok 11 -\n");
    do {
        printf(" 1. Input Text             \n");
        printf(" 2. Print Text             \n");
        printf(" 3. Pindahkan Kursor/Hapus \n");
        printf(" 4. Cari Kata              \n");
        printf(" 5. Undo/Redo              \n");
        printf(" 0. Exit Program           \n");
        printf("---------------------------\n");

        cout << "Pilih menu: ";
        cin >> pilih;

        if (pilih == 1) {
            input_text(Text, Cursor, Undo);
        } else if (pilih == 2) {
            print_text(Text);
        } else if (pilih == 3) {
            pindahkan_kursor_atau_hapus_teks(Text, Cursor, Undo);
        } else if (pilih == 4) {
            cari_kata(Text);
        } else if (pilih == 5) {
            undo_redo(Text, Undo, Redo, Cursor);
        }
    } while (pilih != 0);

    return 0;
}
