import Foundation

enum PlayerType {
    case human, computer
}

class Player {
    var symbol: String
    var type: PlayerType

    init(symbol: String, type: PlayerType) {
        self.symbol = symbol
        self.type = type
    }
}

class TicTacToe {
    var board: [[String]]
    let size: Int
    var currentPlayer: Player
    var player1: Player
    var player2: Player
    var aiLevel: String

    init(size: Int = 3, aiLevel: String = "easy") {
        self.size = size
        self.board = Array(repeating: Array(repeating: " ", count: size), count: size)
        self.player1 = Player(symbol: "X", type: .human)
        self.player2 = Player(symbol: "O", type: .computer)
        self.currentPlayer = player1
        self.aiLevel = aiLevel
    }

    func drawBoard() {
        print("\n")
        for row in 0..<size {
            print(board[row].map { $0 == " " ? "_" : $0 }.joined(separator: " | "))
        }
        print("\n")
    }

    func makeMove(row: Int, col: Int) -> Bool {
        if row >= 0 && row < size && col >= 0 && col < size {
            if board[row][col] == " " {
                board[row][col] = currentPlayer.symbol
                return true
            }
        }
        return false
    }

    func switchPlayer() {
        currentPlayer = (currentPlayer.symbol == player1.symbol) ? player2 : player1
    }

    func checkWinner() -> String? {
        let lines = board + transpose(board) + diagonals(board)
        for line in lines {
            if Set(line).count == 1, line[0] != " " {
                return line[0]
            }
        }
        return board.flatMap { $0 }.contains(" ") ? nil : "Draw"
    }

    func transpose(_ board: [[String]]) -> [[String]] {
        return (0..<size).map { i in board.map { $0[i] } }
    }

    func diagonals(_ board: [[String]]) -> [[String]] {
        let d1 = (0..<size).map { board[$0][$0] }
        let d2 = (0..<size).map { board[$0][size - $0 - 1] }
        return [d1, d2]
    }

    func getComputerMove() -> (Int, Int) {
        if aiLevel == "hard" {
            for r in 0..<size {
                for c in 0..<size {
                    if board[r][c] == " " {
                        board[r][c] = currentPlayer.symbol
                        if checkWinner() == currentPlayer.symbol {
                            board[r][c] = " "
                            return (r, c)
                        }
                        board[r][c] = " "
                    }
                }
            }

            let opponentSymbol = (currentPlayer.symbol == player1.symbol) ? player2.symbol : player1.symbol
            for r in 0..<size {
                for c in 0..<size {
                    if board[r][c] == " " {
                        board[r][c] = opponentSymbol
                        if checkWinner() == opponentSymbol {
                            board[r][c] = " "
                            return (r, c)
                        }
                        board[r][c] = " "
                    }
                }
            }
        }

        var available: [(Int, Int)] = []
        for r in 0..<size {
            for c in 0..<size {
                if board[r][c] == " " {
                    available.append((r, c))
                }
            }
        }
        return available.randomElement() ?? (0, 0)
    }

    func runGame() {
        drawBoard()
        while true {
            print("Current player: \(currentPlayer.symbol)")
            var moveMade = false
            if currentPlayer.type == .human {
                print("Enter your move (row[0,1,2] and column[0,1,2]) in format: row,column")
                if let input = readLine(), input.contains(",") {
                    let parts = input.split(separator: ",")
                    if let r = Int(parts[0]), let c = Int(parts[1]) {
                        moveMade = makeMove(row: r, col: c)
                    }
                }
            } else {
                let (r, c) = getComputerMove()
                moveMade = makeMove(row: r, col: c)
                print("Computer moves: \(r),\(c)")
            }

            if moveMade {
                drawBoard()
                if let result = checkWinner() {
                    if result == "Draw" {
                        print("Draw!")
                    } else {
                        print("Winner is \(result)!")
                    }
                    break
                }
                switchPlayer()
            } else {
                print("Invalid move. Try again.")
            }
        }
    }
}

print("Welcome to Kolko i Krzyzyk!")
print("Choose difficulty (easy or hard):")
let level = readLine()?.lowercased() ?? "easy"

let game = TicTacToe(aiLevel: level)
game.runGame()
