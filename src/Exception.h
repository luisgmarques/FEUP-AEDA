#pragma once

#include <iostream>
#include <string>

using namespace std;


/**
 * @brief 
 * 
 */
class FileUnkown {
    private:

	string fileName;

    public:

	/**
	 * @brief Construct a new File Unkonw object
	 * 
	 * @param fileName 
	 */
	FileUnkown(string fileName) : fileName(fileName) {};

	/**
	 * @brief Get the File Name object
	 * 
	 * @return string 
	 */
	string getFileName() const{
        return fileName;
    }
};




class ObjectNotFound {
	private:

	int id;
	string objectName;

	public:

	ObjectNotFound(int id, string objectName) {
		this->id = id;
		this->objectName = objectName;
	}
};