#include <iostream>
#include <string>
using namespace std;

// ================= NODE STRUCTURE (Circular Doubly Linked List) =================
struct Song {
    string title;
    string artist;
    int duration;
    Song* next;
    Song* prev;
};

Song* head = nullptr;

// ================= CREATE NEW SONG NODE =================
Song* createSong(string t, string a, int d) {
    Song* s = new Song;
    s->title = t;
    s->artist = a;
    s->duration = d;
    s->next = s->prev = nullptr;
    return s;
}

// ================= CHECK IF LIST EMPTY =================
bool isEmpty() {
    return head == nullptr;
}

// ================= INSERT AT BEGINNING =================
void insertAtBeginning() {
    cin.ignore();
    string t, a;
    int d;
    cout << "Enter song title: ";
    getline(cin, t);
    cout << "Enter artist: ";
    getline(cin, a);
    cout << "Enter duration: ";
    cin >> d;

    Song* newSong = createSong(t, a, d);

    if (isEmpty()) {
        head = newSong;
        newSong->next = newSong->prev = newSong;
    } else {
        Song* last = head->prev;

        newSong->next = head;
        newSong->prev = last;

        last->next = newSong;
        head->prev = newSong;

        head = newSong;
    }

    cout << "Inserted at beginning!\n";
}

// ================= INSERT AT END =================
void insertAtEnd() {
    cin.ignore();
    string t, a;
    int d;
    cout << "Enter song title: ";
    getline(cin, t);
    cout << "Enter artist: ";
    getline(cin, a);
    cout << "Enter duration: ";
    cin >> d;

    Song* newSong = createSong(t, a, d);

    if (isEmpty()) {
        head = newSong;
        newSong->next = newSong->prev = newSong;
    } else {
        Song* last = head->prev;

        newSong->next = head;
        newSong->prev = last;

        last->next = newSong;
        head->prev = newSong;
    }

    cout << "Inserted at end!\n";
}

// ================= INSERT AT ANY POSITION =================
void insertAtPosition() {
    if (isEmpty()) {
        cout << "List empty — inserting at beginning.\n";
        insertAtBeginning();
        return;
    }

    int pos;
    cout << "Enter position to insert: ";
    cin >> pos;

    if (pos <= 1) {
        insertAtBeginning();
        return;
    }

    cin.ignore();
    string t, a;
    int d;
    cout << "Enter song title: ";
    getline(cin, t);
    cout << "Enter artist: ";
    getline(cin, a);
    cout << "Enter duration: ";
    cin >> d;

    Song* newSong = createSong(t, a, d);

    Song* temp = head;
    int count = 1;

    // Move until position found or last element reached
    while (count < pos - 1 && temp->next != head) {
        temp = temp->next;
        count++;
    }

    Song* nextNode = temp->next;

    newSong->next = nextNode;
    newSong->prev = temp;
    temp->next = newSong;
    nextNode->prev = newSong;

    cout << "Inserted at position " << pos << "!\n";
}

// ================= DELETE AT BEGINNING =================
void deleteAtBeginning() {
    if (isEmpty()) {
        cout << "List empty.\n";
        return;
    }

    Song* temp = head;

    if (head->next == head) { // one node
        head = nullptr;
    } else {
        Song* last = head->prev;

        head = head->next;
        last->next = head;
        head->prev = last;
    }

    delete temp;
    cout << "Deleted first song.\n";
}

// ================= DELETE AT END =================
void deleteAtEnd() {
    if (isEmpty()) {
        cout << "List empty.\n";
        return;
    }

    Song* last = head->prev;

    if (last == head) { // only one node
        head = nullptr;
    } else {
        Song* secondLast = last->prev;
        secondLast->next = head;
        head->prev = secondLast;
    }

    delete last;
    cout << "Deleted last song.\n";
}

// ================= DELETE BY POSITION =================
void deleteAtPosition() {
    if (isEmpty()) {
        cout << "List empty.\n";
        return;
    }

    int pos;
    cout << "Enter position to delete: ";
    cin >> pos;

    if (pos <= 1) {
        deleteAtBeginning();
        return;
    }

    Song* temp = head;
    int count = 1;

    while (count < pos && temp->next != head) {
        temp = temp->next;
        count++;
    }

    if (count < pos) {
        cout << "Position out of range.\n";
        return;
    }

    Song* prevNode = temp->prev;
    Song* nextNode = temp->next;

    prevNode->next = nextNode;
    nextNode->prev = prevNode;

    if (temp == head)
        head = nextNode;

    delete temp;
    cout << "Deleted at position " << pos << "!\n";
}

// ================= SEARCH SONG BY TITLE =================
void searchSong() {
    if (isEmpty()) {
        cout << "Playlist empty.\n";
        return;
    }

    cin.ignore();
    string title;
    cout << "Enter title to search: ";
    getline(cin, title);

    Song* temp = head;
    int pos = 1;

    do {
        if (temp->title == title) {
            cout << "\nFound at position " << pos << "!\n";
            cout << "Artist: " << temp->artist << endl;
            cout << "Duration: " << temp->duration << " sec\n";
            return;
        }

        temp = temp->next;
        pos++;

    } while (temp != head);

    cout << "Song not found.\n";
}

// ================= DISPLAY FORWARD =================
void displayForward() {
    if (isEmpty()) {
        cout << "Playlist empty.\n";
        return;
    }

    cout << "\n--- Playlist (Forward) ---\n";
    Song* temp = head;
    int i = 1;

    do {
        cout << i++ << ". " << temp->title << " | " 
             << temp->artist << " | " << temp->duration << "s\n";
        temp = temp->next;
    } while (temp != head);
}

// ================= DISPLAY BACKWARD =================
void displayBackward() {
    if (isEmpty()) {
        cout << "Playlist empty.\n";
        return;
    }

    cout << "\n--- Playlist (Backward) ---\n";
    Song* temp = head->prev;
    int i = 1;

    do {
        cout << i++ << ". " << temp->title << " | "
             << temp->artist << " | " << temp->duration << "s\n";
        temp = temp->prev;
    } while (temp->next != head);
}

// ================= MAIN MENU =================
int main() {
    int choice;

    while (true) {
        cout << "\n==== MUSIC PLAYLIST MENU ====\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert at Position\n";
        cout << "4. Delete at Beginning\n";
        cout << "5. Delete at End\n";
        cout << "6. Delete at Position\n";
        cout << "7. Search Song\n";
        cout << "8. Display Forward\n";
        cout << "9. Display Backward\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: insertAtBeginning(); break;
            case 2: insertAtEnd(); break;
            case 3: insertAtPosition(); break;
            case 4: deleteAtBeginning(); break;
            case 5: deleteAtEnd(); break;
            case 6: deleteAtPosition(); break;
            case 7: searchSong(); break;
            case 8: displayForward(); break;
            case 9: displayBackward(); break;
            case 0: 
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
