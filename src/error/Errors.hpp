/*
** EPITECH PROJECT, 2022
** indie
** File description:
** Errors
*/

#ifndef ERRORS_HPP_
    #define ERRORS_HPP_

	#include <exception>
	#include <string>

namespace Error {
	class IndieError : std::exception {
		public:
            IndieError(const std::string &comp, const std::string &msg);
            const char *what() const noexcept override;
        private:
            std::string _msg;
            std::string _comp;
	};
	class DropDownErrorSelectedButtonNotFound : public IndieError {
		public:
			DropDownErrorSelectedButtonNotFound(const std::string &comp, const std::string &msg);
	};
}

#endif /* !ERRORS_HPP_ */