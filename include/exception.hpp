#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <exception>
#include <string>

class InputOutputException : public std::exception {
   private:
    std::string errorMessage;

   public:
    InputOutputException()
        : errorMessage("Terjadi kesalahan dalam proses baca tulis") {}
    InputOutputException(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class InventoryEror : public std::exception {
   private:
    std::string errorMessage;

   public:
    InventoryEror()
        : errorMessage(
              "Terjadi kesalahan dalam penambahan atau pengurangan item") {}
    InventoryEror(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class InventoryFull : public std::exception {
   private:
    std::string errorMessage;

   public:
    InventoryFull() : errorMessage("Inventory sudah penuh") {}
    InventoryFull(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class CharactersError : public std::exception {
   private:
    std::string errorMessage;

   public:
    CharactersError()
        : errorMessage(
              "Terjadi kesalahan dalam penambahan atau pengurangan character") {
    }
    CharactersError(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class ItemNotFound : public std::exception {
   private:
    std::string errorMessage;

   public:
    ItemNotFound() : errorMessage("Item tidak ditemukan") {}
    ItemNotFound(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class InvalidCommand : public std::exception {
   private:
    std::string errorMessage;

   public:
    InvalidCommand() : errorMessage("Perintah tidak valid") {}
    InvalidCommand(const std::string& message) : errorMessage(message) {}
    const char* what() const noexcept override { return errorMessage.c_str(); }
};
class StockError : public std::exception {
   private:
    std::string errorMessage;

   public:
    StockError() : errorMessage("Stok tidak mencukupi") {}
    StockError(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class GoldNotEnough : public std::exception {
   private:
    std::string errorMessage;

   public:
    GoldNotEnough() : errorMessage("Jumlah gold tidak cukup") {}
    GoldNotEnough(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

class InvalidValue : public std::exception {
   private:
    std::string errorMessage;

   public:
    InvalidValue() : errorMessage("Nilai tidak valid") {}
    InvalidValue(const std::string& message) : errorMessage(message) {}

    const char* what() const noexcept override { return errorMessage.c_str(); }
};

#endif