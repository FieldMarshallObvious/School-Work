
var myVar:String = "hello"
myVar += " world!"

print(myVar)

var myInt:Int = 100
print("My Int, ", myInt)

let constInt:Int = 200

print("My Const Int, ", constInt)

var mySum:Int = 0

// Note you call a function when it is defined later in the function
// Also you must indiciate which item you are passing in
print("My Func value, ", myFunc(a:myInt, b:constInt))

mySum = myFunc(a:myInt, b:constInt)
print("My Sum, ", mySum)

// Return statement is created after -> statement
// Can specify defualt value for variable in the function definiton

func myFunc(a:Int, b:Int = 0 ) -> Int { return a+b }
