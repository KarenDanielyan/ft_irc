/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaniely <kdaniely@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:14:27 by kdaniely          #+#    #+#             */
/*   Updated: 2024/10/23 17:27:25 by kdaniely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <ctime>
# include <cstdlib>

void	log(std::string const & message);

class ReplyException : public std::exception
{
	private:
		std::string message;
	public:
		ReplyException(const std::string& msg): message(msg) {}
		virtual ~ReplyException() throw() {}
		const char* what() const throw()
		{
			return message.c_str();
		}
};

#endif
