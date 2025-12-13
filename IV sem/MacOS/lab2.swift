
// Online Swift compiler to run Swift program online
// Online Swift compiler to run Swift program online
// Print "Try programiz.pro" message

//1
func minValue(_ a: Int, _ b: Int) -> Int {
return min(a, b)
}

print(minValue(2, 20))
print(minValue(30, 19))
print(minValue(-4, -10))
print(minValue(7, 7))

//2
func lastDigit(_ number: Int) -> Int {
return number % 10
}


print(lastDigit(123))
print(lastDigit(3214))
print(lastDigit(5))
print(lastDigit(0))

//3

func divides(_ a: Int, _ b: Int) -> Bool {
return a % b == 0
}

func countDivisors(_ number: Int) -> Int {
var count = 0
for i in 1...number {
if divides(number, i) {
count += 1
}
}
return count
}

func isPrime(_ number: Int) -> Bool {
return countDivisors(number) == 2
}


print(divides(7, 3))
print(divides(8, 4))

print(countDivisors(1))
print(countDivisors(10))
print(countDivisors(12))

print(isPrime(3))
print(isPrime(4))
print(isPrime(7))


// 4

func smartBart(n: Int, closure: () -> Void) {
for _ in 1...n {
closure()
}
}

smartBart(n: 3) {
print("I will pass this course with best mark, because Swift is great!")
}

// 5

let numbers = [10, 16, 18, 30, 38, 40, 44, 50]

let multiplesOfFour = numbers.filter { $0 % 4 == 0 }

print(multiplesOfFour)

// 6


let largestNumber = numbers.reduce(Int.min) { max($0, $1) }

print(largestNumber)

//7

var strings = ["Gdansk", "University", "of", "Technology"]

let result2 = strings.reduce("") { $0.isEmpty ? $1 : $0 + " " + $1 }

print(result2)

// 8

let numbers2 = [1, 2, 3, 4, 5, 6]

let sumOfSquares = numbers2
.filter { $0 % 2 != 0 }
.map { $0 * $0 }
.reduce(0, +)

print(sumOfSquares)


//9

func minmax(_ a: Int, _ b: Int) -> (min: Int, max: Int) {
return (min(a, b), max(a, b))
}


let result = minmax(10, 5)
print(result)

// 10

var stringsArray = ["gdansk", "university", "gdansk", "university", "university", "of", "technology", "technology", "gdansk", "gdansk"]

let countedStrings = Dictionary(grouping: stringsArray, by: { $0 })
.map { ($0.key, $0.value.count) }


print(countedStrings)

// 11

enum Day: Int {
case monday = 1, tuesday, wednesday, thursday, friday, saturday, sunday

func emoji() -> String {
switch self {
case .monday: return "😴 Monday Blues"
case .tuesday: return "💪 Productivity Tuesday"
case .wednesday: return "🐪 Hump Day"
case .thursday: return "🔥 Almost There!"
case .friday: return "🎉 Weekend Vibes"
case .saturday: return "🌞 Relax & Enjoy"
case .sunday: return "🛌 Lazy Sunday"
}
}
}


let today = Day.wednesday
print("Day \(today.rawValue): \(today.emoji())")
