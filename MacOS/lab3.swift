import Foundation

struct Location {
    let id: Int
    let type: String
    let name: String
    let rating: Int
}

struct City {
    let id: Int
    let name: String
    let description: String
    let latitude: Double
    let longitude: Double
    let tags: [String]
    let locations: [Location]
}

let cities: [City] = [
    City(id: 1, name: "Warszawa", description: "Stolica Polski, najwieksze miasto w kraju", latitude: 52.2298, longitude: 21.0122, tags: ["stolica", "kultura", "historia"], locations: [
        Location(id: 1, type: "restaurant", name: "Restauracja Polska", rating: 5),
        Location(id: 2, type: "museum", name: "Muzeum Narodowe", rating: 4)
    ]),
    City(id: 2, name: "Krakow", description: "Miasto krolow z pieknym Starym Miastem", latitude: 50.0647, longitude: 19.9450, tags: ["historia", "kultura", "turystyka"], locations: [
        Location(id: 3, type: "pub", name: "Pub Krakowski", rating: 4),
        Location(id: 4, type: "monument", name: "Pomnik Adama Mickiewicza", rating: 5)
    ]),
    City(id: 3, name: "Gdansk", description: "Portowe miasto nad Morzem Baltyckim", latitude: 54.3520, longitude: 18.6466, tags: ["seaside", "historia", "turystyka"], locations: [
        Location(id: 5, type: "restaurant", name: "Restauracja Gdanska", rating: 5),
        Location(id: 6, type: "museum", name: "Muzeum II Wojny Swiatowej", rating: 5)
    ]),
    City(id: 4, name: "Wroclaw", description: "Miasto stu mostow nad Odra", latitude: 51.1079, longitude: 17.0385, tags: ["kultura", "historia", "turystyka"], locations: [
        Location(id: 7, type: "pub", name: "Pub Wroclawski", rating: 4),
        Location(id: 8, type: "monument", name: "Pomnik Wroclawski", rating: 4)
    ]),
    City(id: 5, name: "Poznan", description: "Miasto koziołkow i slynnych rogali", latitude: 52.4064, longitude: 16.9252, tags: ["kultura", "historia", "jedzenie"], locations: [
        Location(id: 9, type: "restaurant", name: "Restauracja Poznanska", rating: 5),
        Location(id: 10, type: "museum", name: "Muzeum Rogali", rating: 4)
    ]),
    City(id: 6, name: "Lodz", description: "Miasto fabryk i nowoczesnych inwestycji", latitude: 51.7592, longitude: 19.4560, tags: ["przemysl", "sztuka", "rewitalizacja"], locations: [
        Location(id: 11, type: "restaurant", name: "Restauracja Lodzka", rating: 4),
        Location(id: 12, type: "museum", name: "Muzeum Sztuki", rating: 5)
    ]),
    City(id: 7, name: "Szczecin", description: "Miasto nad Odra z piekna architektura", latitude: 53.4285, longitude: 14.5528, tags: ["port", "przyroda", "kultura"], locations: [
        Location(id: 13, type: "pub", name: "Pub Szczecinski", rating: 4),
        Location(id: 14, type: "monument", name: "Pomnik Szczecinski", rating: 4)
    ]),
    City(id: 8, name: "Lublin", description: "Miasto z urokliwym Starym Miastem", latitude: 51.2465, longitude: 22.5684, tags: ["historia", "kultura", "uniwersytety"], locations: [
        Location(id: 15, type: "restaurant", name: "Restauracja Lubelska", rating: 5),
        Location(id: 16, type: "museum", name: "Muzeum Lubelskie", rating: 4)
    ]),
    City(id: 9, name: "Katowice", description: "Serce Slaska, dynamicznie rozwijajace sie miasto", latitude: 50.2700, longitude: 19.0390, tags: ["przemysl", "muzyka", "rewitalizacja"], locations: [
        Location(id: 17, type: "pub", name: "Pub Katowicki", rating: 4),
        Location(id: 18, type: "monument", name: "Pomnik Powstancow Slaskich", rating: 5)
    ]),
    City(id: 10, name: "Bydgoszcz", description: "Miasto kanalow i muzyki", latitude: 53.1235, longitude: 18.0084, tags: ["muzyka", "przyroda", "turystyka"], locations: [
        Location(id: 19, type: "restaurant", name: "Restauracja Bydgoska", rating: 5),
        Location(id: 20, type: "museum", name: "Muzeum Muzyki", rating: 4)
    ]),
    City(id: 11, name: "Bialystok", description: "Miasto na wschodzie z piekna przyroda", latitude: 53.1325, longitude: 23.1688, tags: ["przyroda", "historia", "turystyka"], locations: [
        Location(id: 21, type: "pub", name: "Pub Bialostocki", rating: 4),
        Location(id: 22, type: "monument", name: "Pomnik Bialostocki", rating: 4)
    ]),
    City(id: 12, name: "Gdynia", description: "Nowoczesne miasto portowe nad Baltykiem", latitude: 54.5189, longitude: 18.5305, tags: ["seaside", "przemysl", "turystyka"], locations: [
        Location(id: 23, type: "restaurant", name: "Restauracja Gdynska", rating: 5),
        Location(id: 24, type: "museum", name: "Muzeum Emigracji", rating: 5)
    ]),
    City(id: 13, name: "Torun", description: "Miasto Mikołaja Kopernika i piernikow", latitude: 53.0138, longitude: 18.5984, tags: ["historia", "jedzenie", "turystyka"], locations: [
        Location(id: 25, type: "pub", name: "Pub Torunski", rating: 4),
        Location(id: 26, type: "monument", name: "Pomnik Kopernika", rating: 5)
    ]),
    City(id: 14, name: "Olsztyn", description: "Miasto jezior i zamkow", latitude: 53.7784, longitude: 20.4801, tags: ["przyroda", "historia", "turystyka"], locations: [
        Location(id: 27, type: "restaurant", name: "Restauracja Olsztynska", rating: 5),
        Location(id: 28, type: "museum", name: "Muzeum Warmii i Mazur", rating: 4)
    ]),
    City(id: 15, name: "Rzeszow", description: "Stolica Podkarpacia, rozwijajace sie miasto", latitude: 50.0412, longitude: 21.9991, tags: ["przemysl", "kultura", "technologia"], locations: [
        Location(id: 29, type: "pub", name: "Pub Rzeszowski", rating: 4),
        Location(id: 30, type: "monument", name: "Pomnik Rzeszowski", rating: 4)
    ]),
    City(id: 16, name: "Kielce", description: "Miasto targow i rezerwatu geologicznego", latitude: 50.8661, longitude: 20.6286, tags: ["przyroda", "historia", "przemysl"], locations: [
        Location(id: 31, type: "restaurant", name: "Restauracja Kielecka", rating: 5),
        Location(id: 32, type: "museum", name: "Muzeum Geologiczne", rating: 4)
    ]),
    City(id: 17, name: "Zielona Gora", description: "Miasto wina i festiwali", latitude: 51.9356, longitude: 15.5062, tags: ["wino", "kultura", "przyroda"], locations: [
        Location(id: 33, type: "pub", name: "Pub Zielonogorski", rating: 4),
        Location(id: 34, type: "monument", name: "Pomnik Zielonogorski", rating: 4)
    ]),
    City(id: 18, name: "Opole", description: "Miasto polskiej piosenki", latitude: 50.6664, longitude: 17.9280, tags: ["muzyka", "kultura", "historia"], locations: [
        Location(id: 35, type: "restaurant", name: "Restauracja Opolska", rating: 5),
        Location(id: 36, type: "museum", name: "Muzeum Polskiej Piosenki", rating: 5)
    ]),
    City(id: 19, name: "Czestochowa", description: "Religijne centrum Polski", latitude: 50.8122, longitude: 19.1192, tags: ["religia", "historia", "kultura"], locations: [
        Location(id: 37, type: "pub", name: "Pub Czestochowski", rating: 4),
        Location(id: 38, type: "monument", name: "Pomnik Jasna Gora", rating: 5)
    ]),
    City(id: 20, name: "Sopot", description: "Nadmorski kurort z molo", latitude: 54.4418, longitude: 18.5601, tags: ["seaside", "turystyka", "muzyka"], locations: [
        Location(id: 39, type: "restaurant", name: "Restauracja Sopocka", rating: 5),
        Location(id: 40, type: "museum", name: "Muzeum Sopotu", rating: 4)
    ])
]

func searchCity(byName name: String) -> [City] {
    return cities.filter { $0.name.lowercased() == name.lowercased() }
}

func searchCity(byKeyword keyword: String) -> [City] {
    return cities.filter { $0.tags.contains { $0.lowercased() == keyword.lowercased() } }
}

func calculateDistance(lat1: Double, lon1: Double, lat2: Double, lon2: Double) -> Double {
    let R = 6371.0 
    let dLat = (lat2 - lat1) * .pi / 180.0
    let dLon = (lon2 - lon1) * .pi / 180.0
    
    let a = sin(dLat/2) * sin(dLat/2) +
            cos(lat1 * .pi / 180.0) * cos(lat2 * .pi / 180.0) *
            sin(dLon/2) * sin(dLon/2)
    let c = 2 * atan2(sqrt(a), sqrt(1-a))
    
    return R * c
}

func findClosestAndFarthestCity(userLat: Double, userLon: Double) {
    guard let firstCity = cities.first else { return }
    
    var closestCity = firstCity
    var farthestCity = firstCity
    var minDistance = calculateDistance(lat1: userLat, lon1: userLon, lat2: firstCity.latitude, lon2: firstCity.longitude)
    var maxDistance = minDistance

    for city in cities {
        let distance = calculateDistance(lat1: userLat, lon1: userLon, lat2: city.latitude, lon2: city.longitude)
        
        if distance < minDistance {
            minDistance = distance
            closestCity = city
        }
        
        if distance > maxDistance {
            maxDistance = distance
            farthestCity = city
        }
    }
    
    print("Closest city: \(closestCity.name) (\(String(format: "%.2f", minDistance)) km)")
    print("Farthest city: \(farthestCity.name) (\(String(format: "%.2f", maxDistance)) km)")
}

func findTwoFarthestCities() {
    var maxDistance = 0.0
    var city1: City?
    var city2: City?

    for i in 0..<cities.count {
        for j in i+1..<cities.count {
            let distance = calculateDistance(
                lat1: cities[i].latitude, lon1: cities[i].longitude,
                lat2: cities[j].latitude, lon2: cities[j].longitude
            )
            
            if distance > maxDistance {
                maxDistance = distance
                city1 = cities[i]
                city2 = cities[j]
            }
        }
    }
    
    if let city1 = city1, let city2 = city2 {
        print("Two farthest cities: \(city1.name) - \(city2.name) (\(String(format: "%.2f", maxDistance)) km)")
    }
}

func displayCitiesWithFiveStarRestaurants() {
    for city in cities {
        let fiveStarRestaurants = city.locations.filter { $0.type == "restaurant" && $0.rating == 5 }
        if !fiveStarRestaurants.isEmpty {
            print("City: \(city.name)")
            for restaurant in fiveStarRestaurants {
                print("  - \(restaurant.name) (\(restaurant.rating) stars)")
            }
        }
    }
}

func getLocationsSortedByRating(for city: City) -> [Location] {
    return city.locations.sorted { $0.rating > $1.rating }
}

func displayCitiesWithFiveStarLocations() {
    for city in cities {
        let fiveStarLocations = city.locations.filter { $0.rating == 5 }
        if !fiveStarLocations.isEmpty {
            print("City: \(city.name) has \(fiveStarLocations.count) locations with 5-star rating:")
            for location in fiveStarLocations {
                print("  - \(location.name) (\(location.type))")
            }
        }
    }
}

let citiesNamedGdansk = searchCity(byName: "Gdansk")
print("Cities named 'Gdansk':")
for city in citiesNamedGdansk {
    print("  - \(city.name)")
}
print("\n")

let citiesWithKeywordTurystyka = searchCity(byKeyword: "turystyka")
print("Cities with keyword 'turystyka':")
for city in citiesWithKeywordTurystyka {
    print("  - \(city.name)")
}
print("\n")

if let cityA = cities.first, let cityB = cities.last {
    let distance = calculateDistance(
        lat1: cityA.latitude, lon1: cityA.longitude,
        lat2: cityB.latitude, lon2: cityB.longitude
    )
    print("Distance between \(cityA.name) and \(cityB.name): \(String(format: "%.2f", distance)) km")
}
print("\n")

findClosestAndFarthestCity(userLat: 52.0, userLon: 19.0)
print("\n")

findTwoFarthestCities()
print("\n")

displayCitiesWithFiveStarRestaurants()
print("\n")

if let city = cities.first {
    let sortedLocations = getLocationsSortedByRating(for: city)
    print("Locations in \(city.name) sorted by rating:")
    for location in sortedLocations {
        print("  - \(location.name) (\(location.rating) stars)")
    }
}
print("\n")

displayCitiesWithFiveStarLocations()
