struct ChatView {
    // Properties
    var message:String = ""
    
    var messageWithPrefix:String {
        return "Noah says: " + message
    }
    
    // View Code for this screen
    
    // Methods
    func sendChat() {
        // Variables

        // Code to send chat messages here
        print(messageWithPrefix + message)
    }
    
    func deleteChat() {
        print(message)
    }
}

