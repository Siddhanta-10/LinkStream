#include<iostream>
#include<string>

struct SongNode
{
    std::string title;
    int duration; // in seconds

    SongNode* next;

    SongNode(std::string title, int duration) : title(title), duration(duration), next(nullptr)
    {

    }
};

class LinkStream
{
    private:
        SongNode* head; // Points to the first song
        SongNode* tail; // Points to the last song

    public:
        // Constructor initializes an empty playlist
        LinkStream(){
            head = nullptr;
            tail = nullptr;
        }

        void addSong(std::string title, int duration){
            // 1. Create the new song in memory
            SongNode* newSong = new SongNode(title, duration);

            // 2. Scenario A: The playlist is completely empty
            if(head == nullptr){
                // Wire up head and tail for the very first song
                head = newSong;
                tail = newSong;
            }
            // 3. Scenario B: The playlist has already songs in it
            else{
                // We need to add this new song to the end of the line.
                tail->next = newSong; // The old last song now points to the new song
                tail = newSong;       // Update the tail pointer to the new end of the line
            }
            std::cout<< "Added: "<< title << " to the queue"<< std::endl;
        }

        void removeSong(std::string targetTitle){
            if(head == nullptr) // Empty playlist
                return;

            // 1. Setup two pointers
            SongNode* current = head;
            SongNode* previous = nullptr;

            // 2. Loop to find the song
            while(current != nullptr && current->title != targetTitle){
                // Move both pointers forward.
                // move 'previous' to where 'current' is,
                // and then move 'current' to the next song
                previous = current;
                current = current->next;
            }

            if(current == nullptr){
                std::cout<< "Song not found." << std::endl;
                return;
            }

            // 4. We found it! Now we disconnect it.
            // There are a few scenarios here (What if it's the head? What if it's the tail?)
            // if(previous == nullptr){
            //     head = current->next;
            // }
            // else if(current->next == nullptr){
            //     tail = previous;
            //     tail->next = nullptr;
            // }
            // else{
            //     previous->next = current->next;
            // }
            // 3. Edge Case: Deleting the Head
            if(current == head){
                head = head->next;
                // What if it was the ONLY song? Head is now nullptr. Tail must be too.
                if(head == nullptr){
                    tail = nullptr;
                }
            }
            // 4. Middle or Tail deletion
            else{
                previous->next = current->next;

                // Edge Case: Deleting the Tail
                if(current == tail){
                    tail = previous;
                }
            }

            // 5. Actually destroy the song in memory
            delete current;
            std::cout<< "Removed: "<< targetTitle << std::endl;
        }

        void printQueue(){
            if(head == nullptr){
                std::cout<<"The queue is empty."<<std::endl;
                return;
            }

            std::cout<<"--- Current queue ---"<<std::endl;

            // 1. Create a temporary pointer and start it at the beginning
            SongNode* current = head;

            // 2. Loop until we fall off the end of the list
            while(current != nullptr){
                std::cout<<"- "<< current->title << " ("<< current->duration << "s)"<< std::endl;
                // 3. The Jump
                current = current->next;
            }

        }
};

int main()
{
    std::cout<<"Nexus Engine Initialized...\n"<<std::endl;

    LinkStream streamer;

    // Add some songs
    streamer.addSong("Bohemian Rhapsody", 354);
    streamer.addSong("Staiway to Heaven", 482);
    streamer.addSong("Hotel California", 390);

    // Print out the list
    streamer.printQueue();

    return 0;
}