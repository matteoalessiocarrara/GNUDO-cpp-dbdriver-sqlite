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
		namespace dbdefs
		{
			using std::string;
		  
			
			namespace tables
			{
				const string tasks = "tasks";
				const string priorityLevels = "priority_levels";
			}
			
			
			namespace columns
			{
				namespace task
				{
					const string id = "id";
					const string title = "title"; 
					const string description = "description";
					const string creationTime = "ctime";
					const string modificationTime = "mtime";
					const string completed = "completed";
					const string priority = "priority"; 
				}
				
				namespace prioritylevel
				{
					const string name = "name";
					const string color = "color";
					const string priority = "priority";
				}
			}
		 
		}
	}
}


# endif // ifndef GNUDO_SQLITE_DBDEFS_HPP

