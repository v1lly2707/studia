// Online Swift compiler to run Swift program online
// Print "Try programiz.pro" message
//print("Try programiz.pro")

 // exercise 1
 
var number1 = 2
var number2 = 57

print("\(number1) + \(number2) = \(number1 + number2)")


// exercise 2

var a = "Gdansk University of Technology"
var newString = ""

for character in a {
    if character == "n" {
        newString.append("⭐️")  
    } else {
        newString.append(character)
    }
}

print(newString)

//exercise 3

var name = "Filip Świniarski"

let reversedName = String(name.reversed())

print(reversedName)

//exercise 4

for i in 1...11
{
    print("I will pass this course with best mark, because Swift is great!")
}

// exercise 5

for i in 1...5
{
    print(i*i)
}

//exercise 6

for i in 1...5
{
    for j in 1...5
    {
        print("@", terminator: "")
    }
    print ()
    
}

//exercise 7

var numbers = [5, 10, 20, 15, 80, 13]

if let maxNumber = numbers.max() {
    print("Maximum value: \(maxNumber)")
}

//exercise 8

let reversedNumbers = numbers.reversed()
print(reversedNumbers.map { String($0) }.joined(separator: ", "))

//exercise 9

var allNumbers = [10, 20, 10, 11, 13, 20, 10, 30]

var uniqueNumbers = Array(Set(allNumbers))

print("unique =", uniqueNumbers)

//exercise 10

let number = 10
var divisors: Set<Int> = []

for i in 1...number {
    if number % i == 0 {
        divisors.insert(i)
    }
}

let sortedDivisors = divisors.sorted()
print("divisors =", sortedDivisors)

//exercise 11

var flights: [[String: String]] = [
    ["flightNumber": "AA8025", "destination": "Copenhagen"],
    ["flightNumber": "BA1442", "destination": "New York"],
    ["flightNumber": "BD6741", "destination": "Barcelona"]
]

let flightNumbers = flights.compactMap { $0["flightNumber"] }
print("flightNumbers =", flightNumbers)

//exercise 12
var names = ["Hommer", "Lisa", "Bart"]
let fullName = names.map { ["lastName": "Simpson", "firstName": $0] }

print("fullName =", fullName)

