#ifndef defutility
#define defutility
#include <fstream>
#include <iostream>
#include <vector>

#include "../donjon/donjon.hpp"
#include "tmxlite/Map.hpp"

/**
 * @brief Finds the index of a value in a vector.
 *
 * @param vec The vector to search in.
 * @param value The value to find.
 * @return The index of the value if found, -1 otherwise.
 */
int findInVector(std::vector<char> vec, char value);

/**
 * @brief Reads the content of a file and returns it as a 2D vector of characters.
 *
 * @param file The input file stream.
 * @return The 2D vector of characters representing the file content.
 */
std::vector<std::vector<char>> getListOfFile(std::ifstream &file);

/**
 * @brief Calculates the width of a 2D vector.
 *
 * @param list The input 2D vector.
 * @return The width of the vector.
 */
int width(std::vector<std::vector<char>> list);

/**
 * @brief Calculates the height of a 2D vector.
 *
 * @param list The input 2D vector.
 * @return The height of the vector.
 */
int height(std::vector<std::vector<char>> list);

/**
 * @brief Gets the character at the specified position in a 2D vector.
 *
 * @param list The input 2D vector.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @return The character at the specified position.
 */
char getCharAt(std::vector<std::vector<char>> list, int x, int y);

/**
 * @brief Returns a random element from a vector of strings.
 *
 * @param vec The input vector of strings.
 * @return A random element from the vector.
 */
std::string getRandomElement(std::vector<std::string> vec);

/**
 * @brief Counts the number of occurrences of a value in a vector.
 *
 * @param vec The input vector.
 * @return The number of occurrences of the value.
 */
int getNumverInList(std::vector<char> vec);

/**
 * @brief Gets the property with the specified name from a vector of properties.
 *
 * @param vec The input vector of properties.
 * @param name The name of the property to find.
 * @return The property with the specified name.
 */
tmx::Property getPropertyFromName(std::vector<tmx::Property> vec, std::string name);

/**
 * @brief Checks if a value exists in the second element of a vector of pairs.
 *
 * @param vec The input vector of pairs.
 * @param value The value to check.
 * @return True if the value exists in the second element of any pair, false otherwise.
 */
bool isInSecondVector(std::vector<std::pair<Node *, std::string>> vec, std::string value);

/**
 * @brief Merges two vectors of tmx::Object into a single vector.
 *
 * @param vec1 The first vector of tmx::Object.
 * @param vec2 The second vector of tmx::Object.
 * @return The merged vector of tmx::Object.
 */
std::vector<tmx::Object> mergeVectors(std::vector<tmx::Object> vec1, std::vector<tmx::Object> vec2);
int getSeedFromFile(std::string name);

int compterLettres(const std::string& texte);

/**
 * @brief Checks if a point is inside a bounding box.
 *
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param object The bounding box object.
 * @return True if the point is inside the bounding box, false otherwise.
 */
bool isPointInBox(int x, int y, tmx::Object object);

/**
 * @brief Checks if two bounding boxes intersect.
 *
 * @param object1 The first bounding box object.
 * @param object2 The second bounding box object.
 * @return True if the bounding boxes intersect, false otherwise.
 */
bool isBoxInBox(tmx::Object object1, tmx::Object object2);

/**
 * @brief Checks if a pair of tmx::Object and std::string is empty.
 *
 * @param pair The input pair.
 * @return True if the pair is empty, false otherwise.
 */
bool isEmpty(std::pair<tmx::Object, std::string> pair);

/**
 * @brief Checks if a string value exists in the second element of any pair in a vector of pairs.
 *
 * @param list The input vector of pairs.
 * @param value The string value to check.
 * @return A pair of tmx::Object and std::string if the value exists, an empty pair otherwise.
 */
std::pair<tmx::Object, std::string> isInList(std::vector<std::pair<tmx::Object, std::string>> list, std::string value);

#endif