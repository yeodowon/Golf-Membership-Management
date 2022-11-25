cmake_minimum_required(VERSION 3.0.0)

project(GolfMembership_Management)

add_executable(${PROJECT_NAME}
    ./src/main.cpp
    ./src/Golf_membership_manager.cpp
    ./src/app/Listener/Listener.cpp
    ./src/app/Controller/Controller.cpp
    ./src/app/Members_entity/Members_entity.cpp
    ./src/app/Members_manage_service/Members_manage_service.cpp
    ./src/app/Views/Views.cpp
    ./src/hw/rfid/mfrc522.cpp
    ./src/hw/rfid/Card_reader.cpp
    ./src/hw/spi/SPI.cpp
    ./src/hw/Monitor/Monitor.cpp
    ./src/hw/Button/Button.cpp
    ./src/hw/Button/Manage_button.cpp
    ./src/hw/LCD/LCD.cpp
    ./src/hw/I2C/I2C.cpp
    ./src/hw/Led/Led.cpp
    ./src/hw/Tcp_server/Tcp_server.cpp
    ./src/hw/Tcp_server/Com_dev.cpp
    ./src/hw/Sg90/Sg90.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./src
    ./src/app/Listener
    ./src/app/Controller
    ./src/app/Model
    ./src/app/Members_entity
    ./src/app/Members_manage_service
    ./src/app/Views
    ./src/hw/rfid
    ./src/hw/spi
    ./src/hw/Monitor
    ./src/hw/Button
    ./src/hw/LCD
    ./src/hw/I2C
    ./src/hw/Led
    ./src/hw/Tcp_server
    ./src/hw/Sg90
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    -lwiringPi
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)