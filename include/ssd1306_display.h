#pragma once

#include "driver/i2c_master.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <cstdint>
#include <string>

class SSD1306Display {
private:
    i2c_port_t _i2c_port;
    uint8_t _device_address;
    gpio_num_t _sda_pin;
    gpio_num_t _scl_pin;
    i2c_master_dev_handle_t _i2c_device_handle;
    i2c_master_bus_handle_t _i2c_bus_handle;
    SemaphoreHandle_t _i2c_mutex;
    bool _initialized;
    bool _owns_bus_handle;  // Track if we own the bus handle
    
    // Display dimensions and buffer
    uint8_t _width;
    uint8_t _height;
    uint8_t* _display_buffer;
    size_t _buffer_size;
    
    // I2C communication methods
    esp_err_t write_command(uint8_t command);
    esp_err_t write_data(const uint8_t* data, size_t len);
    
    void set_pixel(int16_t x, int16_t y, bool color);
    void draw_char(int16_t x, int16_t y, unsigned char c, bool color, uint8_t size = 1);

public:
    static constexpr uint8_t DEFAULT_ADDRESS = 0x3C;
    static constexpr uint8_t DEFAULT_WIDTH = 128;
    static constexpr uint8_t DEFAULT_HEIGHT = 32;
    
    // Constructor for creating own I2C bus (legacy)
    explicit SSD1306Display(gpio_num_t sda_pin, gpio_num_t scl_pin, 
                           uint8_t width = DEFAULT_WIDTH, 
                           uint8_t height = DEFAULT_HEIGHT,
                           i2c_port_t port = I2C_NUM_0, 
                           uint8_t address = DEFAULT_ADDRESS);
    
    // Constructor for using external I2C bus and mutex (recommended)
    explicit SSD1306Display(i2c_master_bus_handle_t bus_handle,
                           SemaphoreHandle_t i2c_mutex,
                           uint8_t width = DEFAULT_WIDTH, 
                           uint8_t height = DEFAULT_HEIGHT,
                           uint8_t address = DEFAULT_ADDRESS);
    
    ~SSD1306Display();
    
    esp_err_t initialize();

    // Flip display orientation (upside down)
    void set_flipped(bool flipped);
    
    void clear();
    void display();
    void turn_on();
    void turn_off();
    
    // misc drawing methods
    void draw_string(int16_t x, int16_t y, const char* text, bool color = true, uint8_t size = 1);
    void draw_string(int16_t x, int16_t y, const std::string& text, bool color = true, uint8_t size = 1);
    void draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, bool color = true);
    void draw_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, bool color = true);
    void fill_rectangle(int16_t x, int16_t y, int16_t width, int16_t height, bool color = true);
    
    // Utility functions
    bool initialized() const { return _initialized; }
    uint8_t width() const { return _width; }
    uint8_t height() const { return _height; }
};
