/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

# ifndef GNUDO_SQLITE_DBDEFS_HPP
# define GNUDO_SQLITE_DBDEFS_HPP

# include <string>


namespace gnudo
{
	namespace sqlite
	{
		namespace dbarch
		{
		  using std::string;
		  
		  namespace tables
		  {
			   const string TASKS = "tasks";
			   const string PRIORITY_LEVELS = "priority_levels";
		  }
		 
		}
	}
}


# endif // ifndef GNUDO_SQLITE_DBDEFS_HPP
