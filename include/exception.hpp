#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class InputOutputException : public std::exception {
private:
    std::string errorMessage;

public:
    InputOutputException() : errorMessage("Terjadi kesalahan dalam proses baca tulis"){}
    InputOutputException(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

class InventoryEror : public std::exception {
    private:
        std::string errorMessage;
    
    public:
        InventoryEror() : errorMessage("Terjadi kesalahan dalam penambahan atau pengurangan item"){}
        InventoryEror(const std::string& message) : errorMessage(message) {}
    
        const char* what() const noexcept override {
            return errorMessage.c_str();
        }
    };
    

#endif