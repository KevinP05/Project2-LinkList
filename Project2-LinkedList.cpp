// Kevin Perez
// CWID: 885000125
#include<iostream>
#include<memory>
#include<vector>
#include<string>

template<typename T>
class Tab {
public: 
    std::string url;
    std::string name;
    T memory;
    Tab<T>* next;
    Tab<T>* prev;

    Tab(std::string url, std::string name, T memory)
        : url(url), name(name), memory(memory), next(nullptr), prev(nullptr) {}
};

template<typename T>
class Browser {
private: 
    Tab<T>* head;
    Tab<T>* tail;
    Tab<T>* current;
    std::vector<std::pair<std::string, std::string>> bookmarks;
public: 
    Browser() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addNewTab(const std::string& url, const std::string& name, T memory) {
        Tab<T>* newTab = new Tab<T>(url, name, memory);
        if (!head) {
            head = tail = current = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            current = newTab;

    }
}
void switchToPrevTab() {
        if (!current || !current->prev) {
            std::cout << "No previous tab" << std::endl;
            return;
        }
        current = current->prev;
        std::cout << "Switched to Previous Tab: " << current->name << " (" << current->url << ") Memory: " << current->memory << "MB" << std::endl;
    }

    void switchToNextTab() {
        if (!current || !current->next) {
            std::cout << "No next tab" << std::endl;
            return;
        }
        current = current->next;
        std::cout << "Switched to Next Tab: " << current->name << " (" << current->url << ") Memory: " << current->memory << "MB" << std::endl;
    }

    void closeCurrentTab() {
        if (!current) {
            std::cout << "No current tab to close" << std::endl;
            return;
        }
        Tab<T>* temp = current;
        if (current == head) {
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
            current = head;
        } else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            current = tail;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
        }

        std::cout << "Closed Tab: " << temp->name << " Now the current tab = " << (current ? current->name : "None") << std::endl;
        delete temp;
    }

    void bookmarkCurrent() {
        if (!current) return;
        for (const auto& b : bookmarks) {
            if (b.first == current->name) {
                std::cout << "The bookmark is already added!!" << std::endl;
                return;
            }
        }
        bookmarks.push_back({current->name, current->url});
    }

    void showBookmarkTab() {
        std::cout << "Bookmarks:" << std::endl;
        for (const auto& b : bookmarks) {
            std::cout << b.first << "(" << b.second << ")" << std::endl;
        }
    }

    void moveCurrentToFirst() {
        if (!current || current == head) return;
        if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        current->next = head;
        head->prev = current;
        current->prev = nullptr;
        head = current;
    }

    T total_memory() {
        T total = 0;
        Tab<T>* temp = head;
        while (temp) {
            total += temp->memory;
            temp = temp->next;
        }
        return total;
    }

    void deleteTab() {
        if (!head) return;
        Tab<T>* toDelete = head;
        Tab<T>* iter = head->next;
        while (iter) {
            if (iter->memory > toDelete->memory) {
                toDelete = iter;
            }
            iter = iter->next;
        }
        if (toDelete == head) {
            head = head->next;
            if (head) {
                head->prev = nullptr;
            }
        } else if (toDelete == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }
        if (current == toDelete) {
            current = toDelete->next ? toDelete->next : toDelete->prev;
        }
        std::cout << "Deleted Tab: " << toDelete->name << " with memory " << toDelete->memory << "MB" << std::endl;
        delete toDelete;
    }

    void display(){
            auto curr = head;
            std::cout<<"Browser tab list = "<<std::endl;
            while(curr){
                std::cout<<"| "<<curr->name<<"  x|-->";
                curr = curr->next;
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
};
int main(){
    
    Browser<double> b1;
    b1.addNewTab("https://www.google.com","Google",23.45);
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to Next tab = "<<std::endl;
    b1.switchToNextTab();
    b1.addNewTab("https://www.youtube.com","YouTube",56);
    b1.bookmarkCurrent();
    b1.display();
    b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
    b1.bookmarkCurrent();
    b1.addNewTab("https://chat.openai.com","ChatGPT",129);
    b1.addNewTab("https://linkedin.com","LinkedIn",410);
    b1.bookmarkCurrent();
    b1.addNewTab("https://github.com","Github",110);
    b1.addNewTab("https://kaggle.com","Kaggle",310);
    b1.bookmarkCurrent();
    b1.display();
    std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
    b1.showBookmarkTab();
    b1.moveCurrentToFirst();
    b1.display();
    b1.deleteTab();
    b1.display();
    std::cout<<"Switch to next tab = "<<std::endl;
    b1.switchToNextTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    b1.showBookmarkTab();
    std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
    b1.deleteTab();
    b1.display();
    b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.bookmarkCurrent();
    b1.showBookmarkTab();
    b1.total_memory();
    b1.deleteTab();
    b1.display();
    return 0;
}
