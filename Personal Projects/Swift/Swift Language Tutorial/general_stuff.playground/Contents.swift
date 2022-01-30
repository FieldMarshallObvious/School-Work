import UIKit

var greeting = "Hello, playground"

print(greeting)

for index in 1...5 {
    print(index)
}

for index in stride(from: 5, to: 1, by: -1) {
    print(index)
}

for _ in 1...5 {
    print("hello")
}

var counter = 5

while counter > 0 {
    print("hello")
    counter -= 1
}

repeat {
    print("hello")
    counter -= 1
} while counter > 0
