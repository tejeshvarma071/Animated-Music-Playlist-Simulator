#include <iostream>
#include <string>
#include <unistd.h>   // for sleep(), usleep()
#include <stdlib.h>   // for system("cls/clear")
using namespace std;

// ========== ANIMATION FUNCTIONS ==========

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void slowPrint(const string &text, int delay = 20000) {
    for (char c : text) {
        cout << c << flush;
        usleep(delay);
    }
}

void loading(const string &msg) {
    slowPrint(msg, 15000);
    for (int i = 0; i < 5; i++) {
        cout << "." << flush;
        usleep(300000);
    }
    cout << "\n";
}

// ========== SONG STRUCTURE ==========

struct Song {
    string title, artist;
    int duration;

    Song() {}
    Song(string t, string a, int d) : title(t), artist(a), duration(d) {}
};

// ========== DOUBLY CIRCULAR LINKED LIST NODE ==========

struct Node {
    Song data;
    Node *next, *prev;
    Node(const Song &s) : data(s), next(nullptr), prev(nullptr) {}
};

// ========== PLAYLIST CLASS ==========

class MusicPlaylist {
private:
    Node *head, *current;

public:
    MusicPlaylist() : head(nullptr), current(nullptr) {}
    ~MusicPlaylist() { clear(); }

    bool isEmpty() const { return head == nullptr; }

    int length() const {
        if (isEmpty()) return 0;
        int count = 1;
        Node *temp = head->next;
        while (temp != head) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void addSongEnd(const Song &s) {
        loading("Adding song");
        Node *newNode = new Node(s);

        if (isEmpty()) {
            head = current = newNode;
            head->next = head->prev = head;
        } else {
            Node *tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
        }
        slowPrint("Song added!\n");
        sleep(1);
    }

    void addSongFront(const Song &s) {
        loading("Adding song at front");
        Node *newNode = new Node(s);

        if (isEmpty()) {
            head = current = newNode;
            head->next = head->prev = head;
        } else {
            Node *tail = head->prev;
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
        slowPrint("Song added at beginning!\n");
        sleep(1);
    }

    void playCurrent() const {
        if (isEmpty()) {
            slowPrint("Playlist empty.\n");
            return;
        }

        clearScreen();
        loading("Loading song");

        slowPrint("\n🎵 Now Playing 🎵\n", 15000);
        slowPrint("Title   : " + current->data.title + "\n");
        slowPrint("Artist  : " + current->data.artist + "\n");
        slowPrint("Duration: " + to_string(current->data.duration) + " seconds\n");
        sleep(2);
    }

    void nextSong() {
        if (isEmpty()) {
            slowPrint("Playlist empty.\n");
            return;
        }
        current = current->next;
        playCurrent();
    }

    void previousSong() {
        if (isEmpty()) {
            slowPrint("Playlist empty.\n");
            return;
        }
        current = current->prev;
        playCurrent();
    }

    bool deleteSongByTitle(const string &title) {
        if (isEmpty()) return false;

        Node *temp = head;
        do {
            if (temp->data.title == title) {
                loading("Deleting");

                if (temp->next == temp) {
                    delete temp;
                    head = current = nullptr;
                } else {
                    Node *p = temp->prev;
                    Node *n = temp->next;
                    p->next = n;
                    n->prev = p;

                    if (temp == head) head = n;
                    if (temp == current) current = n;

                    delete temp;
                }
                slowPrint("Song deleted.\n");
                sleep(1);
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    bool deleteCurrent() {
        if (isEmpty()) return false;
        return deleteSongByTitle(current->data.title);
    }

    bool setCurrentByTitle(const string &title) {
        if (isEmpty()) return false;

        Node *temp = head;
        do {
            if (temp->data.title == title) {
                current = temp;
                slowPrint("Current song updated.\n");
                sleep(1);
                return true;
            }
            temp = temp->next;
        } while (temp != head);

        return false;
    }

    void displayPlaylistForward() const {
        clearScreen();
        slowPrint("🎧 Playlist (Forward) 🎧\n", 15000);

        if (isEmpty()) {
            slowPrint("Playlist empty.\n");
            return;
        }

        Node *temp = head;
        int i = 1;
        do {
            cout << i++ << ". " << temp->data.title
                 << " | " << temp->data.artist
                 << " | " << temp->data.duration << "s";
            if (temp == current) cout << "  <-- CURRENT";
            cout << "\n";
            temp = temp->next;
            usleep(50000);
        } while (temp != head);

        sleep(1);
    }

    void displayPlaylistBackward() const {
        clearScreen();
        slowPrint("🎧 Playlist (Backward) 🎧\n", 15000);

        if (isEmpty()) {
            slowPrint("Playlist empty.\n");
            return;
        }

        Node *temp = head->prev;
        int i = length();
        do {
            cout << i-- << ". " << temp->data.title
                 << " | " << temp->data.artist
                 << " | " << temp->data.duration << "s";
            if (temp == current) cout << "  <-- CURRENT";
            cout << "\n";
            temp = temp->prev;
            usleep(50000);
        } while (temp != head->prev);

        sleep(1);
    }

    void clear() {
        if (isEmpty()) return;

        loading("Clearing playlist");

        Node *temp = head->next;
        while (temp != head) {
            Node *del = temp;
            temp = temp->next;
            delete del;
        }
        delete head;

        head = current = nullptr;

        slowPrint("Playlist cleared.\n");
        sleep(1);
    }
};

// ========== INPUT HELPERS ==========

Song inputSong() {
    cin.ignore();
    string t, a;
    int d;

    slowPrint("Enter title: ");
    getline(cin, t);

    slowPrint("Enter artist: ");
    getline(cin, a);

    slowPrint("Duration (sec): ");
    cin >> d;

    return Song(t, a, d);
}

void printMenu() {
    slowPrint("===== MUSIC PLAYLIST =====\n", 10000);
    cout << "1. Add song at end\n";
    cout << "2. Add song at beginning\n";
    cout << "3. Play current song\n";
    cout << "4. Next song\n";
    cout << "5. Previous song\n";
    cout << "6. Delete by title\n";
    cout << "7. Delete current\n";
    cout << "8. Set current by title\n";
    cout << "9. Show playlist forward\n";
    cout << "10. Show playlist backward\n";
    cout << "11. Playlist size\n";
    cout << "12. Clear playlist\n";
    cout << "0. Exit\n";
    slowPrint("Choose: ");
}

// ========== MAIN PROGRAM ==========

int main() {
    MusicPlaylist playlist;
    int choice;

    while (true) {
        clearScreen();
        printMenu();
        cin >> choice;

        clearScreen();

        switch (choice) {
            case 1: playlist.addSongEnd(inputSong()); break;
            case 2: playlist.addSongFront(inputSong()); break;
            case 3: playlist.playCurrent(); break;
            case 4: playlist.nextSong(); break;
            case 5: playlist.previousSong(); break;
            case 6: {
                cin.ignore();
                slowPrint("Enter title to delete: ");
                string t; getline(cin, t);
                if (!playlist.deleteSongByTitle(t))
                    slowPrint("Song not found.\n");
                sleep(1);
            } break;
            case 7:
                if (!playlist.deleteCurrent())
                    slowPrint("Nothing to delete.\n");
                sleep(1);
                break;
            case 8: {
                cin.ignore();
                slowPrint("Enter title: ");
                string t; getline(cin, t);
                if (!playlist.setCurrentByTitle(t))
                    slowPrint("Song not found.\n");
                sleep(1);
            } break;
            case 9: playlist.displayPlaylistForward(); break;
            case 10: playlist.displayPlaylistBackward(); break;
            case 11:
                slowPrint("Playlist size: " + to_string(playlist.length()) + "\n");
                sleep(2);
                break;
            case 12: playlist.clear(); break;
            case 0:
                slowPrint("Exiting...\n");
                sleep(1);
                return 0;
            default:
                slowPrint("Invalid choice!\n");
                sleep(1);
        }
    }
}
