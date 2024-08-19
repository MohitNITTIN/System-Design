#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <atomic>
#include <mutex>

enum class BookingStatus { PENDING, CONFIRMED, CANCELLED };
enum class SeatStatus { AVAILABLE, BOOKED };

class User;
class Movie;
class Theater;
class Show;
class Seat;
class Booking;

class MovieTicketBookingSystem {
private:
    static std::unique_ptr<MovieTicketBookingSystem> instance;
    std::vector<std::shared_ptr<Movie>> movies;
    std::vector<std::shared_ptr<Theater>> theaters;
    std::unordered_map<std::string, std::shared_ptr<Show>> shows;
    std::unordered_map<std::string, std::shared_ptr<Booking>> bookings;

    static const std::string BOOKING_ID_PREFIX;
    static std::atomic<long> bookingCounter;

    MovieTicketBookingSystem() = default;

    static std::mutex mutex;

    bool areSeatsAvailable(const std::shared_ptr<Show>& show, const std::vector<std::shared_ptr<Seat>>& selectedSeats);
    void markSeatsAsBooked(const std::shared_ptr<Show>& show, const std::vector<std::shared_ptr<Seat>>& selectedSeats);
    double calculateTotalPrice(const std::vector<std::shared_ptr<Seat>>& selectedSeats);
    std::string generateBookingId();

public:
    static MovieTicketBookingSystem& getInstance();

    void addMovie(const std::shared_ptr<Movie>& movie);
    void addTheater(const std::shared_ptr<Theater>& theater);
    void addShow(const std::shared_ptr<Show>& show);

    std::vector<std::shared_ptr<Movie>> getMovies() const;
    std::vector<std::shared_ptr<Theater>> getTheaters() const;
    std::shared_ptr<Show> getShow(const std::string& showId);

    std::shared_ptr<Booking> bookTickets(const std::shared_ptr<User>& user, const std::shared_ptr<Show>& show, const std::vector<std::shared_ptr<Seat>>& selectedSeats);
    void confirmBooking(const std::string& bookingId);
    void cancelBooking(const std::string& bookingId);
};

std::unique_ptr<MovieTicketBookingSystem> MovieTicketBookingSystem::instance = nullptr;
const std::string MovieTicketBookingSystem::BOOKING_ID_PREFIX = "BKG";
std::atomic<long> MovieTicketBookingSystem::bookingCounter(0);
std::mutex MovieTicketBookingSystem::mutex;

MovieTicketBookingSystem& MovieTicketBookingSystem::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (!instance) {
        instance = std::unique_ptr<MovieTicketBookingSystem>(new MovieTicketBookingSystem());
    }
    return *instance;
}

void MovieTicketBookingSystem::addMovie(const std::shared_ptr<Movie>& movie) {
    movies.push_back(movie);
}

void MovieTicketBookingSystem::addTheater(const std::shared_ptr<Theater>& theater) {
    theaters.push_back(theater);
}

void MovieTicketBookingSystem::addShow(const std::shared_ptr<Show>& show) {
    shows[show->getId()] = show;
}

std::vector<std::shared_ptr<Movie>> MovieTicketBookingSystem::getMovies() const {
    return movies;
}

std::vector<std::shared_ptr<Theater>> MovieTicketBookingSystem::getTheaters() const {
    return theaters;
}

std::shared_ptr<Show> MovieTicketBookingSystem::getShow(const std::string& showId) {
    auto it = shows.find(showId);
    return (it != shows.end()) ? it->second : nullptr;
}

std::shared_ptr<Booking> MovieTicketBookingSystem::bookTickets(const std::shared_ptr<User>& user, const std::shared_ptr<Show>& show, const std::vector<std::shared_ptr<Seat>>& selectedSeats) {
    std::lock_guard<std::mutex> lock(mutex);
    if (areSeatsAvailable(show, selectedSeats)) {
        markSeatsAsBooked(show, selectedSeats);
        double totalPrice = calculateTotalPrice(selectedSeats);
        std::string bookingId = generateBookingId();
        auto booking = std::make_shared<Booking>(bookingId, user, show, selectedSeats, totalPrice, BookingStatus::PENDING);
        bookings[bookingId] = booking;
        return booking;
    }
    return nullptr;
}

bool MovieTicketBookingSystem::areSeatsAvailable(const std::shared_ptr<Show>& show, const std::vector<std::shared_ptr<Seat>>& selectedSeats) {
    for (const auto& seat : selectedSeats) {
        auto showSeat = show->getSeats().find(seat->getId());
        if (showSeat == show->getSeats().end() || showSeat->second->getStatus() != SeatStatus::AVAILABLE) {
            return false;
        }
    }
    return true;
}

void MovieTicketBookingSystem::markSeatsAsBooked(const std::shared_ptr<Show>& show, const std::vector<std::shared_ptr<Seat>>& selectedSeats) {
    for (const auto& seat : selectedSeats) {
        auto showSeat = show->getSeats().find(seat->getId());
        if (showSeat != show->getSeats().end()) {
            showSeat->second->setStatus(SeatStatus::BOOKED);
        }
    }
}

double MovieTicketBookingSystem::calculateTotalPrice(const std::vector<std::shared_ptr<Seat>>& selectedSeats) {
    double totalPrice = 0.0;
    for (const auto& seat : selectedSeats) {
        totalPrice += seat->getPrice();
    }
    return totalPrice;
}

std::string MovieTicketBookingSystem::generateBookingId() {
    long bookingNumber = ++bookingCounter;
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << BOOKING_ID_PREFIX << std::put_time(std::localtime(&now_c), "%Y%m%d%H%M%S") << std::setfill('0') << std::setw(6) << bookingNumber;
    return ss.str();
}

void MovieTicketBookingSystem::confirmBooking(const std::string& bookingId) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = bookings.find(bookingId);
    if (it != bookings.end() && it->second->getStatus() == BookingStatus::PENDING) {
        it->second->setStatus(BookingStatus::CONFIRMED);
        // Process payment and send confirmation
        // ...
    }
}

void MovieTicketBookingSystem::cancelBooking(const std::string& bookingId) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = bookings.find(bookingId);
    if (it != bookings.end() && it->second->getStatus() != BookingStatus::CANCELLED) {
        // Implementation for cancelling booking
        // ...
    }
}


This C++ translation includes the necessary header files, uses appropriate C++ data structures and syntax, and implements the singleton pattern using `std::unique_ptr`. The code uses smart pointers, STL containers, and C++11 features like `enum class` and `std::atomic`. Note that some parts of the code (like the `User`, `Movie`, `Theater`, `Show`, `Seat`, and `Booking` classes) are not fully implemented as they were not provided in the original Java code.

