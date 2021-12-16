struct DatabaseManager {
    func saveData(data:String) -> Bool {
        return true
    }
}

struct MyStructure {
    var message = "Hello"
    var warnging = "Message Failed"
    
    func myFunction() {
        // Save chat message
        let db = DatabaseManager()
        let successful = db.saveData(data: message)
        
        // If successful send message
        if( successful == true )
        {
            print(message)
        }
        else
        {
            print(warnging)
        }
    }
}

var a:MyStructure = MyStructure()

a.message = "Hi"
a.myFunction()
