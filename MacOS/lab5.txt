// Online Swift compiler to run Swift program online
// Print "Try programiz.pro" message
import Foundation

enum MediaType: String {
    case photo = "Photo"
    case video = "Video"
    case music = "Music"
}

struct UserProfile {
    let name: String
    let profilePictureURL: String
}

class FeedItem {
    let user: UserProfile
    let mediaType: MediaType
    let date: Date
    var likes: Int
    
    init(user: UserProfile, mediaType: MediaType, date: Date, likes: Int) {
        self.user = user
        self.mediaType = mediaType
        self.date = date
        self.likes = likes
    }
    
    func formattedLikes() -> String {
        if likes >= 1000 {
            return "\(likes / 1000)k"
        }
        return "\(likes)"
    }
    
    func formattedDate() -> String {
        let formatter = DateFormatter()
        formatter.dateFormat = "dd.MM.yyyy"
        return formatter.string(from: date)
    }
    
    func displayInfo() -> String {
        return "Profile name: \(user.name) | Media type: \(mediaType.rawValue) | Date: \(formattedDate()) | Number of likes: \(formattedLikes())"
    }
}

let user1 = UserProfile(name: "Apple", profilePictureURL: "https://apple.com/profile.jpg")
let user2 = UserProfile(name: "Spotify", profilePictureURL: "https://spotify.com/profile.jpg")

let dateFormatter = DateFormatter()
dateFormatter.dateFormat = "yyyy-MM-dd"

let feed1Date = dateFormatter.date(from: "2018-08-12") ?? Date()
let feed2Date = dateFormatter.date(from: "2021-02-01") ?? Date()

let feed1 = FeedItem(user: user1, mediaType: .video, date: feed1Date, likes: 413000)
let feed2 = FeedItem(user: user2, mediaType: .music, date: feed2Date, likes: 12000)

let feeds = [feed1, feed2]

for feed in feeds {
    print(feed.displayInfo())
}


    
    
