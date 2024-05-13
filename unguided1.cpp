#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Mahasiswa
{
    string NIM;
    int nilai;
    Mahasiswa(string nim, int nilai) : NIM(nim), nilai(nilai) {}
};

class HashTable
{
private:
    static const int TABLE_SIZE = 10;
    vector<Mahasiswa *> table[TABLE_SIZE];

    int hashFunc(string key)
    {
        int hash_val = 0;
        for (char c : key)
        {
            hash_val += c;
        }
        return hash_val % TABLE_SIZE;
    }

public:
    void insert(string nim, int nilai)
    {
        int index = hashFunc(nim);
        table[index].push_back(new Mahasiswa(nim, nilai));
    }

    void remove(string nim)
    {
        int index = hashFunc(nim);
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if ((*it)->NIM == nim)
            {
                table[index].erase(it);
                return;
            }
        }
    }

    Mahasiswa *searchByNIM(string nim)
    {
        int index = hashFunc(nim);
        for (Mahasiswa *mhs : table[index])
        {
            if (mhs->NIM == nim)
            {
                return mhs;
            }
        }
        return nullptr;
    }

    vector<Mahasiswa *> searchByScoreRange(int minScore, int maxScore)
    {
        vector<Mahasiswa *> result;
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            for (Mahasiswa *mhs : table[i])
            {
                if (mhs->nilai >= minScore && mhs->nilai <= maxScore)
                {
                    result.push_back(mhs);
                }
            }
        }
        return result;
    }
};

int main()
{
    HashTable hashTable;
    int choice;
    string nim;
    int nilai;

    do
    {
        cout << "\nMenu:\n";
        cout << "1. Tambah data mahasiswa\n";
        cout << "2. Hapus data mahasiswa\n";
        cout << "3. Cari mahasiswa berdasarkan NIM\n";
        cout << "4. Cari mahasiswa berdasarkan rentang nilai (80 - 90)\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nMasukkan NIM mahasiswa: ";
            cin >> nim;
            cout << "Masukkan nilai mahasiswa: ";
            cin >> nilai;
            hashTable.insert(nim, nilai);
            cout << "Data mahasiswa berhasil ditambahkan.\n";
            break;

        case 2:
            cout << "\nMasukkan NIM mahasiswa yang ingin dihapus: ";
            cin >> nim;
            hashTable.remove(nim);
            cout << "Data mahasiswa dengan NIM " << nim << " berhasil dihapus.\n";
            break;

        case 3:
            cout << "\nMasukkan NIM mahasiswa yang ingin dicari: ";
            cin >> nim;
            {
                Mahasiswa *mhs = hashTable.searchByNIM(nim);
                if (mhs != nullptr)
                {
                    cout << "Mahasiswa dengan NIM " << nim << " ditemukan. Nilainya: " << mhs->nilai << endl;
                }
                else
                {
                    cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
                }
            }
            break;

        case 4:
        {
            int minScore = 80;
            int maxScore = 90;
            vector<Mahasiswa *> result = hashTable.searchByScoreRange(minScore, maxScore);
            if (!result.empty())
            {
                cout << "\nMahasiswa dengan nilai antara 80 - 90:\n";
                for (Mahasiswa *mhs : result)
                {
                    cout << "NIM: " << mhs->NIM << ", Nilai: " << mhs->nilai << endl;
                }
            }
            else
            {
                cout << "\nTidak ada mahasiswa dengan nilai antara 80 - 90.\n";
            }
        }
        break;

        case 5:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
            break;
        }
    } while (choice != 5);

    return 0;
}
