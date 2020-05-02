#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <iostream>
#include <string>

using namespace std;

/**
 * @brief FileUnknow Class
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

		/**
		 * @brief Prints object
		 * 
		 * @param os 
		 * @param obj 
		 * @return ostream& 
		 */
		friend ostream& operator <<(ostream& os, const FileUnkown& obj);
};



/**
 * @brief ObjectNotFound Class
 * 
 */
class ObjectNotFound {
	private:

		int id;
		string objectName;

	public:

		/**
		 * @brief Construct a new Object Not Found object
		 * 
		 * @param id 
		 * @param objectName 
		 */
		ObjectNotFound(int id, string objectName) {
			this->id = id;
			this->objectName = objectName;
		}

		/**
		 * @brief Get the Object Name object
		 * 
		 * @return string 
		 */
		string getObjectName() const;

		/**
		 * @brief Get the Id object
		 * 
		 * @return int 
		 */
		int getId() const;
		
		/**
		 * @brief Prints object
		 * 
		 * @param os 
		 * @param obj 
		 * @return ostream& 
		 */
		friend ostream& operator <<(ostream& os, const ObjectNotFound& obj);
};

/**
 * @brief MaxBorrowsLimit
 * 
 */
class MaxBorrowsLimit {
	private:

		int id;
		string name;

	public:

		/**
		 * @brief Construct a new Max Borrows Limit object
		 * 
		 * @param id 
		 * @param name 
		 */
		MaxBorrowsLimit(int id, string name) {
			this->id = id;
			this->name = name;
		}

		/**
		 * @brief Print object
		 * 
		 * @param os 
		 * @param obj 
		 * @return ostream& 
		 */
		friend ostream& operator <<(ostream& os, const MaxBorrowsLimit& obj);
};

/**
 * @brief NoCopiesAvailable Class
 * 
 */
class NoCopiesAvailable {
	private:

		int id;
		string name;

	public:

		/**
		 * @brief Construct a new No Copies Available object
		 * 
		 * @param id 
		 * @param name 
		 */
		NoCopiesAvailable(int id, string name) {
			this->id = id;
			this->name = name;
		}

		/**
		 * @brief Print object
		 * 
		 * @param os 
		 * @param obj 
		 * @return ostream& 
		 */
		friend ostream& operator <<(ostream& os, const NoCopiesAvailable& obj);
};

/**
 * @brief BorrowsToDelivered
 * 
 */
class BorrowsToDelivered {
	private:

		int borrows;
		string name;
	public:

		/**
		 * @brief Construct a new Borrows To Delivered object
		 * 
		 * @param borrows 
		 * @param name 
		 */
		BorrowsToDelivered(int borrows, string name) {
			this->borrows = borrows;
			this->name = name;
		}

		/**
		 * @brief Prints object
		 * 
		 * @param os 
		 * @param obj 
		 * @return ostream& 
		 */
		friend ostream& operator <<(ostream& os, const BorrowsToDelivered& obj);
};

#endif