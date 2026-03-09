#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ========================
//       USER CLASS
// ========================
class User {
private:
    string username;
    string password;
    string phoneNumber;
    string status;
    string lastSeen;

    string getCurrentTimestamp() {
        time_t now = time(nullptr);
        return string(ctime(&now));
    }

public:
    User() {
        username = "";
        password = "";
        phoneNumber = "";
        status = "";
        lastSeen = getCurrentTimestamp();
    }

    User(string uname, string pwd, string phone) {
        username = uname;
        password = pwd;
        phoneNumber = phone;
        status = "Online";
        lastSeen = getCurrentTimestamp();
    }

    string getUsername() const {
        return username;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getStatus() const {
        return status;
    }

    string getLastSeen() const {
        return lastSeen;
    }

    void setStatus(string newStatus) {
        status = newStatus;
    }

    void setPhoneNumber(string phone) {
        phoneNumber = phone;
    }

    void updateLastSeen() {
        lastSeen = getCurrentTimestamp();
    }

    bool checkPassword(string pwd) const {
        return password == pwd;
    }

    void changePassword(string newPwd) {
        if (newPwd.length() >= 6){
            password = newPwd;
        }
        else {
            cout << "Password must be at least 6 characters long. \n";
        }
    }
};

// ========================
//      MESSAGE CLASS
// ========================
class Message {
private:
    string sender;
    string content;
    string timestamp;
    string status;
    Message* replyTo;

public:
    Message() {
        // TODO: Implement default constructor
            sender = "";
            content = "";
            status = "sent";
            replyTo = nullptr;
            updateTimestamp();
    }

    Message(string sndr, string cntnt) {
        // TODO: Implement parameterized constructor
        sender=sndr;
        content=cntnt;
        status="sent";
        replyTo=nullptr;
        updateTimestamp();
    }

    string getContent() const {
        // TODO: Implement getter
        return content;
    }

    string getSender() const {
        // TODO: Implement getter
        return sender;
    }

    string getTimestamp() const {
        // TODO: Implement getter
        return timestamp;
    }

    string getStatus() const {
        // TODO: Implement getter
        return status;
    }

    Message* getReplyTo() const {
        // TODO: Implement getter
        return replyTo;
    }

    void setStatus(string newStatus) {
        // TODO: Implement setter
        status=newStatus;

    }

    void setReplyTo(Message* msg) {
        // TODO: Implement setter
        replyTo=msg;
    }

    void updateTimestamp() {
        // TODO: Implement timestamp update
        time_t currentTime = time(0);
        timestamp=ctime(&currentTime);
    }

    void display() const {
        // TODO: Implement message display
            cout << "From: " << sender << endl;
            cout << "Time: " << timestamp;
            cout << "Status: " << status << endl;
            cout << "Message: " << content << endl;
            if (replyTo != nullptr) {
               cout << "In reply to: " << replyTo->getContent() << endl;
            }
    }

    void addEmoji(string emojiCode) {
        // TODO: Implement emoji support
            if(emojiCode== ":)"){
                 cout << "😊";
            }
            else if (emojiCode== ":("){
                cout << "😣";
            }
            else if (emojiCode == ":D"){
                cout << "😀";
            }
            else if (emojiCode == "<3"){
                cout << "❤";
            }
            else if (emojiCode == ":thumbsup:"){
                 cout << "👍";
            }
            else{
                cout << "Emoji can't be translated";
            }

    }

};

// ========================
//       CHAT CLASS (BASE)
// ========================
class Chat {
protected:
    vector<string> participants;
    vector<Message> messages;
    string chatName;

public:
    Chat() {
        // TODO: Implement default constructor;
        chatName="";

    }

    Chat(vector<string> users, string name) {
        // TODO: Implement parameterized constructor
        participants=users;
        chatName=name;
    }

    void addMessage(const Message& msg) {
        // TODO: Implement message addition
        messages.push_back(msg);
    }

    bool deleteMessage(int index, const string& username) {
        // TODO: Implement message deletion
        if( index>= 0 && index<messages.size() && messages[index].getSender()==username){
            messages.erase(messages.begin()+index);
            return true;
        }
        return false;
    }

    virtual void displayChat() const {
        // TODO: Implement chat display
        for (int i = 0; i < messages.size(); i++)
        {
            messages[i].display();
        }

    }

    vector<Message> searchMessages(string keyword) const {
        // TODO: Implement message search
        vector<Message> result={};
        for (int i = 0; i < messages.size(); i++)
        {
            if (messages[i].getContent().find(keyword)!= string::npos)
            {
                result.push_back(messages[i]);
            }

        }

        return result;
    }

    void exportToFile(const string& filename) const {
        // TODO: Implement export to file
    }
};

// ========================
//     PRIVATE CHAT CLASS
// ========================
class PrivateChat : public Chat {
private:
    string user1;
    string user2;

public:
    PrivateChat(string u1, string u2): Chat({u1, u2}, "Private Chat Between " + u1 + " & " + u2) {
        // TODO: Implement constructor
        user1 = u1;
        user2 = u2;
    }

    void displayChat() const override {
        // TODO: Implement private chat display
        cout << "Private Chat Between " << user1 << " & " << user2 << endl;
        Chat::displayChat();
    }

    void showTypingIndicator(const string& username) const {
        // TODO: Implement typing indicator
        cout << "[" << username << "is typing..." << endl;
    }
};

// ========================
//      GROUP CHAT CLASS
// ========================
class GroupChat : public Chat {
private:
    vector<string> admins;
    string description;
    vector<string> joinRequests;

public:
    GroupChat(vector<string> users, string name, string creator) {
        // TODO: Implement constructor
        bool isCreatorHere = false;
        for(int i = 0; i < users.size(); i++){
            if(users[i] == creator){
                isCreatorHere = true;
                break;
            }
        }
        if(!isCreatorHere){
            users.push_back(creator);
        }

        Chat(users, name);
        admins.push_back(creator);
        description = "";
    }

    void addAdmin(string newAdmin) {
        // TODO: Implement add admin
        if(isAdmin(newAdmin)){
            admins.push_back(newAdmin);
        }
    }

    bool removeParticipant(const string& admin, const string& userToRemove) {
        // TODO: Implement remove participant
        if(isAdmin(admin) && isParticipant(userToRemove)){
            for(int i = 0; i < Chat::participants.size(); i++){
                if (Chat::participants[i] == userToRemove){
                    Chat::participants.erase(Chat::participants.begin() + i);
                    cout << userToRemove << " is Removed." << endl;
                    return true;
                }
            }
        }
        else if(!isAdmin(admin)){
            cout << "You are NOT an Admin!" << endl;
            return false;
        }
        else{
            cout << "You are NOT a Participant!" << endl;
            return false;
        }
    }

    bool isAdmin(string username) const {
        // TODO: Implement admin check
        for(int i = 0; i < admins.size(); i++){
            if(admins[i] == username){
                return true;
            }
        }
        return false;
    }

    bool isParticipant(string username) const {
        // TODO: Implement participant check
        for(int i = 0; i < Chat::participants.size(); i++){
            if(Chat::participants[i] == username){
                return true;
            }
        }
        return false;
    }

    void setDescription(string desc) {
        // TODO: Implement set description
        description = desc;
    }

    void displayChat() const override {
        // TODO: Implement group chat display
        cout << "Group: " << chatName << endl;
        cout << "Description: " << description << endl;
        cout << "Admins: ";
        for(int i = 0; i < admins.size(); i++){
            cout << admins[i] << " ";
        }
        cout << endl << "Participants: ";
        for(int i = 0; i < Chat::participants.size(); i++){
            cout << Chat::participants[i] << " ";
        }
        Chat::displayChat();
    }

    void sendJoinRequest(const string& username) {
        // TODO: Implement join request
        joinRequests.push_back(username);
        cout << username << "Requested to join the group." << endl;
    }
};

// ========================
//    WHATSAPP APP CLASS
// ========================
class WhatsApp {
private:
    vector<User> users;
    vector<Chat*> chats;
    int currentUserIndex;

    int findUserIndex(string username) const {
        // TODO: Implement user search:done
        for (int i =0; i < users.size(); i++){
            if(users[i].getUsername() == username){
                return i;
            }
        }
        return -1;
    }

    bool isLoggedIn() const {
        // TODO: Implement login check:done
        return currentUserIndex != -1;

        return false;
    }

    string getCurrentUsername() const {
        // TODO: Implement get current user:done
        if (isLoggedIn()) return users[currentUserIndex].getUsername();
        return "";
    }

public:
    WhatsApp() : currentUserIndex(-1) {}

    void signUp() {
        // TODO: Implement user registration:done
        string username, password, phone;
        cout << "Enter username: ";
        cin >> username;
        if (findUserIndex(username) != -1){
            cout << "Username already exists. Please choose another one." << endl;
            return;
        }
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter phone number: ";
        cin >> phone;
        users.push_back(User(username, password, phone));
        cout << "Account created successfully." << endl;
    }

    void login() {
        // TODO: Implement user login:done
        string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    int userIndex = findUserIndex(username);

    if (userIndex == -1){
        cout << "Username not found. Please sign up first." << endl;
        return;
    }

    if (users[userIndex].checkPassword(password)) {
        currentUserIndex = userIndex;
        cout << "Login successful\n";
    }
    else {
        cout << "Incorrect password\n";
    }
}
    

    

    void startPrivateChat() {
        // TODO: Implement private chat creation:done
        string otherUsername;
        cout << "Enter the username of the person you want to chat with: ";
        cin >> otherUsername;
        if(findUserIndex(otherUsername) == -1){
            cout << "User not found." << endl;
            return;
        }
        string currentUsername = getCurrentUsername();
        Chat* chat = new PrivateChat(currentUsername, otherUsername);
        chats.push_back(chat);
        cout << "Private chat started with " << otherUsername << endl;
    }

    void createGroup() {
        // TODO: Implement group creation:done
        string groupName;
        int n;
        cout << "Enter group name: ";
        cin >> groupName;
        cout << "Enter number of participants: ";
        cin >> n;
        vector<string> members;
        for (int i = 0; i < n; i++) {
            string user;
            cout << "Enter username of participant " << (i + 1) << ": ";
            cin >> user;
            if (findUserIndex(user) == -1) members.push_back(user);

            else {
                cout << "User not found.\n "; 
            }
        }
        Chat* groupChat = new GroupChat(members, groupName, getCurrentUsername());
        chats.push_back(groupChat);
        cout << "Group '" << groupName << "' created successfully." << endl;
    }

    void viewChats() const {
        // TODO: Implement chat viewing:done
        if(chats.empty()){
            cout << "No chats available." << endl;
            return;
        }
        for (int i = 0; i < chats.size(); i++) {
            cout <<"\nChat " << (i + 1) << ":\n ";
            chats[i]->displayChat();
        }
    }

    void logout() {
        // TODO: Implement logout
        currentUserIndex = -1;
        cout << "Logged out successfully.\n";

     }

    void run() {
        while (true) {
            if (!isLoggedIn()) {
                cout << "\n1. Login\n2. Sign Up\n3. Exit\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) login();
                else if (choice == 2) signUp();
                else if (choice == 3) break;
            }
            else {
                cout << "\n1. Start Private Chat\n2. Create Group\n3. View Chats\n4. Logout\nChoice: ";
                int choice;
                cin >> choice;

                if (choice == 1) startPrivateChat();
                else if (choice == 2) createGroup();
                else if (choice == 3) viewChats();
                else if (choice == 4) logout();
            }
        }
    }
};

// ========================
//          MAIN
// ========================
int main() {
    WhatsApp whatsapp;
    whatsapp.run();
    return 0;
}
