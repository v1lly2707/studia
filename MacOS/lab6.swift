// Online Swift compiler to run Swift program online
// Print "Try programiz.pro" message
import Foundation

enum CreatureType: String {
    case friendly = "Friendly"
    case curious = "Curious"
    case mysterious = "Mysterious"
}

struct Item {
    let name: String
    let effect: () -> Void
}

struct Creature {
    let name: String
    let type: CreatureType
    var mood: Int
    var patience: Int
    
    var isCalm: Bool {
        return patience <= 0
    }
    
    static func randomEncounter() -> Creature {
        let creatures = [
            ("The Groke", CreatureType.mysterious),
            ("Hattifattener", CreatureType.curious),
            ("Stinky", CreatureType.friendly)
        ]
        let random = creatures.randomElement()!
        return Creature(
            name: random.0,
            type: random.1,
            mood: Int.random(in: 1...3),
            patience: Int.random(in: 10...20)
        )
    }
}

struct MoominCharacter {
    let name: String
    var health: Int
    var friendship: Int
    var level: Int
    
    var isHealthy: Bool {
        return health > 0
    }
    
    mutating func levelUp() {
        level += 1
        health += 10
        friendship += 5
        print("\(name) leveled up to level \(level)! Health and friendship increased!")
    }
    
    func printStats() {
        print("""
         Health: \(health)
         Friendship: \(friendship)
         Level: \(level)
        """)
    }
}

var journal: [String] = []
var dayTurn = true

func handleEncounter(character: inout MoominCharacter) {
    var creature = Creature.randomEncounter()
    print("\n It's \(dayTurn ? "Day" : "Night") in Moominvalley...\n")
    print("You encounter a \(creature.type.rawValue) creature: \(creature.name)")
    print("Mood: \(creature.mood) | Patience: \(creature.patience)\n")
    
    while !creature.isCalm && character.isHealthy {
        print("What will you do?")
        print("1 - Talk")
        print("2 - Run away")
        guard let choice = readLine() else { continue }
        
        if choice == "1" {
            talkToCreature(character: &character, creature: &creature)
        } else if choice == "2" {
            let escaped = runAway(character: &character)
            if escaped { return }
        } else {
            print("Invalid choice.")
        }
    }
    
    if creature.isCalm {
        journal.append("You calmed \(creature.name) the \(creature.type.rawValue) creature.")
        character.levelUp()
    } else if !character.isHealthy {
        print("\(character.name) is too exhausted... Game Over.")
        journal.append("Game ended after encounter with \(creature.name).")
    }
}

func talkToCreature(character: inout MoominCharacter, creature: inout Creature) {
    creature.patience -= character.friendship
    print("You try to talk to \(creature.name)...")
    
    if creature.isCalm {
        print("\(creature.name) has calmed down.")
    } else {
        let damage = creature.mood * 2
        character.health -= damage
        print("\(creature.name) is still agitated and hurts you for \(damage) damage!")
    }
}

func runAway(character: inout MoominCharacter) -> Bool {
    print("You try to run away...")
    if Bool.random() {
        print("You successfully escaped!")
        journal.append("Escaped from an encounter.")
        return true
    } else {
        let spookDamage = Int.random(in: 1...5)
        character.health -= spookDamage
        print("You failed to escape and got spooked for \(spookDamage) damage!")
        return false
    }
}


var player = MoominCharacter(name: "MACmoomin", health: 40, friendship: 15, level: 1)

print("Welcome to Moominvalley RPG!")


while player.isHealthy {
    player.printStats()
    handleEncounter(character: &player)
    dayTurn.toggle()
    
    print("\n Journal so far:")
    for entry in journal {
        print("• \(entry)")
    }
    
    print("\nContinue your journey? (y/n)")
    if let answer = readLine(), answer.lowercased() == "n" {
        print("Thanks for playing! See you!")
        break
    }
}
