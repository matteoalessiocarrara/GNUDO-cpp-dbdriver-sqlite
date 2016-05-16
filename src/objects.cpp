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

# include "dbdefs.hpp"
# include "objects.hpp"


using namespace gnudo::sqlite;


		

Task::Task(const std::uint64_t id, ::sqlite::database &db): __id(id), __sqlitedb(db)
{
}


std::uint64_t
Task::getId() const
{
	return __id;
}


std::string
Task::getTitle() const
{
	__sqlitedb	<< " SELECT title FROM " << GNUDO_SQLITE_TASKS_TABLE 
				<< " WHERE id = " << getId() << ";";
	// FIXME Return
}


void
Task::setTitle(const std::string title)
{
	__sqlitedb 	<< " UPDATE " << GNUDO_SQLITE_TASKS_TABLE 
				<< " SET title = " << title
				<< " WHERE id = " << getId() << ";";
}


std::string
Task::getDescription() const
{
		__sqlitedb	<< " SELECT description FROM " << GNUDO_SQLITE_TASKS_TABLE 
					<< " WHERE id = " << getId() << ";";
	// FIXME Return
}


void
Task::setDescription(const std::string desc)
{
	__sqlitedb 	<< " UPDATE " << GNUDO_SQLITE_TASKS_TABLE 
				<< " SET description = " << desc
				<< " WHERE id = " << getId() << ";";
}


std::time_t
Task::getCreationTime() const
{
	__sqlitedb	<< " SELECT ctime FROM " << GNUDO_SQLITE_TASKS_TABLE 
				<< " WHERE id = " << getId() << ";";
	// FIXME Return
}


std::time_t
Task::getModificationTime() const
{
	__sqlitedb	<< " SELECT mtime FROM " << GNUDO_SQLITE_TASKS_TABLE 
				<< " WHERE id = " << getId() << ";";
	// FIXME Return
}


bool 
Task::isCompleted() const
{
	__sqlitedb	<< " SELECT compelted FROM " << GNUDO_SQLITE_TASKS_TABLE 
				<< " WHERE id = " << getId() << ";";
	// FIXME Return
}


void
Task::setStatus(const bool isCompleted)
{
	__sqlitedb 	<< " UPDATE " << GNUDO_SQLITE_TASKS_TABLE 
				<< " SET completed = " << isCompleted
				<< " WHERE id = " << getId() << ";";	
}


void
Task::setModificationTime(const std::time_t time)
{
	__sqlitedb 	<< " UPDATE " << GNUDO_SQLITE_TASKS_TABLE 
				<< " SET mtime = " << time
				<< " WHERE id = " << getId() << ";";	
}
