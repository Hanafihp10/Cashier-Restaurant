#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

const int Max = 5; // Ubah Max menjadi 5 karena ada penambahan menu
const int Max_Pesanan = 20;

struct MenuItem {
    string Nama;
    int Harga;
    bool Tersedia;
};

struct Order {
    string N_item;
    int Banyaknya;
};

MenuItem Menu[Max];
Order* Psn;  // Menggunakan pointer untuk alokasi dinamis

int head, tail;

void begin() {
    head = tail = -1;
}

bool isEmpty() {
    return tail == -1;
}

bool isFull() {
    return tail == Max_Pesanan - 1;
}

void initializeMenu() {
    Menu[0].Nama = "1.Combo Spicy Hot Chicken lvl 5";
    Menu[0].Harga = 35000;
    Menu[0].Tersedia = true;

    Menu[1].Nama = "2.Double chess Burger";
    Menu[1].Harga = 25000;
    Menu[1].Tersedia = true;

    Menu[2].Nama = "3.Beef HOT Plate";
    Menu[2].Harga = 43000;
    Menu[2].Tersedia = true;

    Menu[3].Nama = "4.Hezaulnet Ice";
    Menu[3].Harga = 13000;
    Menu[3].Tersedia = true;

    Menu[4].Nama = "5.Matcha latte";
    Menu[4].Harga = 12000;
    Menu[4].Tersedia = true;
}

bool isItemAvailable(string Namaitem) {
    for (int i = 0; i < Max; ++i) {
        if (Menu[i].Nama == Namaitem && Menu[i].Tersedia) {
            return true;
        }
    }
    return false;
}

void Tampilkan_Menu() {
    initializeMenu();
    cout << "====================================================================================\n";
    cout << "                                    MENU CHICKEN RIZAL                              \n";
    cout << "====================================================================================\n";
    cout << setw(40) << left << "Menu" << setw(25) << left << "Harga" << setw(5) << left << "Ketersediaan" << endl;
    cout << "====================================================================================\n";
    for (int i = 0; i < Max; ++i) {
        cout << setw(40) << left << Menu[i].Nama;
        cout << setw(25) << left << Menu[i].Harga;
        cout << setw(30) << left << (Menu[i].Tersedia ? "Tersedia" : "Tidak Tersedia") << endl;
    }
    cout << "====================================================================================\n";
}

void Pesan_Menu() {
    do {
        Tampilkan_Menu();
        int IndexMenu;  // Variable untuk Memilih Menu
        int J_Pesan;

        cout << "Silahkan Masukan Nomor Pesanan\t: ";
        cin >> IndexMenu;

        if (IndexMenu < 1 || IndexMenu > Max) {
            cout << "Nomor Pesanan Tidak Valid !\n";
            break; // Keluar dari loop jika nomor pesanan tidak valid
        }

        // Mengambil INDEX sesuai Input Nomor Menu
        int index = IndexMenu - 1;

        if (!Menu[index].Tersedia) {
            cout << "Menu tidak tersedia Atau Habis\n";
            break; // Keluar dari loop jika menu tidak tersedia
        }

        cout << "Masukan Jumlah Pesanan\t\t: ";
        cin >> J_Pesan;

        // Memasukan Pesanan ke dalam antrian
        if (isEmpty()) {
            head = tail = 0;
            Psn[tail].N_item = Menu[index].Nama;
            Psn[tail].Banyaknya = J_Pesan;
            cout << "Pesanan Berhasil Dimasukan ke dalam antrian" << endl;
            cout << "====================================================================================\n";
        } else if (!isFull()) {
            tail++;
            Psn[tail].N_item = Menu[index].Nama;
            Psn[tail].Banyaknya = J_Pesan;
            cout << "Pesanan Berhasil Dimasukan ke dalam antrian" << endl;
            cout << "====================================================================================\n";
        } else {
            cout << "Pesanan OVERLOAD\n";
            break; // Keluar dari loop jika antrian penuh
        }

        // Menanyakan apakah ingin memesan lagi
        cout << "Apakah Anda ingin memesan lagi? (1: Ya, 0: Tidak): ";
        int pesanLagi;
        cin >> pesanLagi;

        if (pesanLagi != 1) {
            break; // Keluar dari loop jika tidak ingin memesan lagi
        }

    } while (true);
}
void Tampilkan_Pesanan() {
    if (isEmpty()) {
        cout << "Antrian Kosong\n";
    } else {
        double totalHarga = 0;
        cout << "=============================================\n";
        cout << setw(20) << left << "Nama Item" << setw(20) << left << "Banyaknya" << setw(20) << left << "Harga" << endl;
        cout << "=============================================\n";
        for (int i = head; i <= tail; ++i) {
            int indexMenu = -1; // Tandai jika tidak ditemukan
            for (int j = 0; j < Max; ++j) {
                if (Menu[j].Nama == Psn[i].N_item) {
                    indexMenu = j;
                    break;
                }
            }

            if (indexMenu != -1) { // Hanya jika item ditemukan
                int hargaPesanan = Psn[i].Banyaknya * Menu[indexMenu].Harga;

                cout << setw(20) << left << Psn[i].N_item;
                cout << setw(20) << left << Psn[i].Banyaknya;
                cout << setw(20) << left << hargaPesanan << endl;

                totalHarga += hargaPesanan;
            }
        }
        cout << "=============================================\n";
        cout << "Total Harga: " << totalHarga << endl;
    }
}
void selectionSort(Order arr[], int n) {
    int i, j, minIndex;
    Order temp;
    for (i = 0; i < n - 1; ++i) {
        minIndex = i;
        for (j = i + 1; j < n; ++j) {
            // Perbandingan berdasarkan nama item
            if (arr[j].N_item < arr[minIndex].N_item) {
                minIndex = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
void Tampilkan_Riwayat() {
    if (isEmpty()) {
        cout << "Antrian Kosong\n";
    } else {
        // Salin pesanan ke array sementara untuk sorting
        Order pesananSorted[Max_Pesanan];
        for (int i = head; i <= tail; ++i) {
            pesananSorted[i] = Psn[i];
        }

        // Sorting pesanan berdasarkan nama item menggunakan selection sort
        selectionSort(pesananSorted, tail - head + 1);

        cout << "===================================================\n";
        cout << setw(20) << left << "Nama Item" << setw(20) << left << "Banyaknya" << setw(20) << left << "Harga" << endl;
        cout << "===================================================\n";
        for (int i = head; i <= tail; ++i) {
            int indexMenu = -1; // Tandai jika tidak ditemukan
            for (int j = 0; j < Max; ++j) {
                if (Menu[j].Nama == pesananSorted[i].N_item) {
                    indexMenu = j;
                    break;
                }
            }

            if (indexMenu != -1) { // Hanya jika item ditemukan
                int hargaPesanan = pesananSorted[i].Banyaknya * Menu[indexMenu].Harga;

                cout << setw(20) << left << pesananSorted[i].N_item;
                cout << setw(20) << left << pesananSorted[i].Banyaknya;
                cout << setw(20) << left << hargaPesanan << endl;
            }
        }
        cout << "===================================================\n";
    }
}
void Proses_Pesanan() {
    if (isEmpty()) {
        cout << "Antrian Kosong\n";
    } else {
        double totalHarga = 0;
        cout << "===========================================================\n";
        cout << "Pesanan berhasil diproses:\n";
        for (int i = head; i <= tail; ++i) {
            int indexMenu = -1; // Tandai jika tidak ditemukan
            for (int j = 0; j < Max; ++j) {
                if (Menu[j].Nama == Psn[i].N_item) {
                    indexMenu = j;
                    break;
                }
            }

            if (indexMenu != -1) // Hanya jika item ditemukan
            {
                int hargaPesanan = Psn[i].Banyaknya * Menu[indexMenu].Harga;

                cout << Psn[i].N_item << endl;
                cout << "Banyaknya: " << Psn[i].Banyaknya << endl;
                cout << "Harga: " << hargaPesanan << endl;
                cout << "===========================================================\n";

                totalHarga += hargaPesanan;
            }
        }
        cout << "Total Harga: " << totalHarga << endl;
    }

    // Kosongkan antrian setelah diproses
    head = tail = -1;
}

int main() {
    Psn = new Order[Max_Pesanan];  // Alokasikan memori untuk array pesanan

    int choice;
    do {
        cout << "===============================\n";
        cout << "       CHICKEN KATSU RIZAL     \n";
        cout << "===============================\n";
        cout << "           Menu kasir          \n";
        cout << "===============================\n";
        cout << "1. Tampilkan Menu              \n";
        cout << "2. Pesan Menu                  \n";
        cout << "3. Tampilkan Pesanan           \n";
        cout << "4. Riwayat Pesanan             \n";
        cout << "5. Proses Pesanan              \n";
        cout << "6. Keluar                      \n";
        cout << "===============================\n";
        cout << "pilih : ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Bersihkan layar sesuai sistem operasi
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            Tampilkan_Menu();
            break;
        case 2:
            // Bersihkan layar sesuai sistem operasi
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            Pesan_Menu();
            break;
        case 3:
            // Bersihkan layar sesuai sistem operasi
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            Tampilkan_Pesanan();
            break;
        case 4:
            // Bersihkan layar sesuai sistem operasi
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            Tampilkan_Riwayat();
            break;
        case 5:
            // Bersihkan layar sesuai sistem operasi
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            Proses_Pesanan();
            break;
        case 6:
            cout << "Terima kasih! Sampai jumpa lagi." << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 6);

    delete[] Psn;  // Hindari kebocoran memori

    return 0;
}
