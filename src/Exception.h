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

		friend ostream& operator <<(ostream& os, const FileUnkown& obj);
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

		string getObjectName() const;

		int getId() const;
		
		friend ostream& operator <<(ostream& os, const ObjectNotFound& obj);
};

class MaxBorrowsLimit {
	private:
		int id;
		string name;

	public:
		MaxBorrowsLimit(int id, string name) {
			this->id = id;
			this->name = name;
		}

		friend ostream& operator <<(ostream& os, const MaxBorrowsLimit& obj);
};

class NoCopiesAvailable {
	private:
		int id;
		string name;

	public:
		NoCopiesAvailable(int id, string name) {
			this->id = id;
			this->name = name;
		}

		friend ostream& operator <<(ostream& os, const NoCopiesAvailable& obj);
};

class BorrowsToDelivered {
	private:
		int borrows;
		string name;
	public:
		BorrowsToDelivered(int borrows, string name) {
			this->borrows = borrows;
			this->name = name;
		}

		friend ostream& operator <<(ostream& os, const BorrowsToDelivered& obj);
};