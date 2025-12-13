import Foundation

class WordChallenge {
    let wordGroups = [
        "countries": ["france", "spain", "canada", "brazil"],
        "animals": ["elephant", "giraffe", "dolphin", "penguin"],
        "sports": ["football", "tennis", "cycling", "swimming"]
    ]
    
    var chosenGroup: String = ""
    var hiddenWord: String = ""
    var discoveredLetters: Set<Character> = []
    var remainingAttempts: Int = 0
    
    func initializeGame() {
        print("Pick a category: Countries, Animals, Sports")
        if let group = readLine()?.lowercased(), wordGroups.keys.contains(group) {
            chosenGroup = group
            hiddenWord = wordGroups[group]?.randomElement() ?? ""
            selectDifficulty()
            playGame()
        } else {
            print("Invalid category. Please try again.")
            initializeGame()
        }
    }
    
    func selectDifficulty() {
        print("Choose difficulty: Easy, Medium, Hard")
        if let difficulty = readLine()?.lowercased() {
            switch difficulty {
            case "easy": remainingAttempts = hiddenWord.count + 5
            case "medium": remainingAttempts = hiddenWord.count
            case "hard": remainingAttempts = hiddenWord.count - 2
            default:
                print("Invalid choice. Defaulting to Medium.")
                remainingAttempts = hiddenWord.count
            }
        }
    }
    
    func showCurrentProgress() {
        var display = ""
        for character in hiddenWord {
            if discoveredLetters.contains(character) {
                display.append(character)
            } else if character == " " {
                display.append(" ")
            } else {
                display.append("_")
            }
        }
        print("Word: \(display)")
    }
    
    func playGame() {
        while remainingAttempts > 0 {
            showCurrentProgress()
            print("Remaining attempts: \(remainingAttempts). Enter a letter:")
            
            if let input = readLine()?.lowercased(), let letter = input.first {
                if hiddenWord.contains(letter) {
                    discoveredLetters.insert(letter)
                    if hiddenWord.allSatisfy({ $0 == " " || discoveredLetters.contains($0) }) {
                        print("Congratulations! You guessed the word: \(hiddenWord)")
                        return
                    }
                } else {
                    remainingAttempts -= 1
                    print("Incorrect guess!")
                }
            }
        }
        print("GAME OVER! The correct word was: \(hiddenWord)")
    }
}

let challenge = WordChallenge()
challenge.initializeGame()
