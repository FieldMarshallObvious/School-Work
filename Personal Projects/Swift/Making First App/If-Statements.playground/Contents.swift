let f = true
let g = false
let e = true

// Statement containing one bool value
if f {
    print("Hello World")
}

// Statement containing the result of a bool operation
if f && g {
    print("Hello World")
}

// Statement containing the result of a chained bool operation
if f && g || e {
    print("Hello World")
}

// Statement containing the result of a chained bool operation
if (f && g) || e {
    print("Hello World")
}

else if e {
    print("e!")
}

else {
    print("failed all branches")
}
