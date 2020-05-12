
set(APP_BIN     ${CMAKE_PROJECT_NAME}_app)
set(UTILS_BIN   ${CMAKE_PROJECT_NAME}_utils)
set(DRIVERS_BIN ${CMAKE_PROJECT_NAME}_drivers)
set(SYS_BIN     ${CMAKE_PROJECT_NAME}_sys)
set(PORT_BIN    ${CMAKE_PROJECT_NAME}_port)

add_subdirectory(app)
add_subdirectory(utils)
add_subdirectory(drivers)
add_subdirectory(sys)
add_subdirectory(port/${PORT})