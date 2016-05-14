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

# include <cstdint>
# include <vector>
# include <ctime>


namespace gnudodb
{
	namespace objects
	{
		class Category
		{
			public:
				void getName();
				void setName();
				void getSubcategories();
				void setSubcategories();
		};

		class Priority
		{
			public:
				void getName();
				void setName();
				void getColor();
				void setColor();
		};

		class Task
		{
			public:
				void getCreationTime();
				void getModificationTime();
				void getDependencies();
				void setDependencies();
				void getCategories();
				void setCategories();
				void getPriority();
				void setPriority();
				void getTitle();
				void setTitle();
				void getDescription();
				void setDescription();
				void isCompleted();
				void setCompleted();

			protected:
				void setModificationTime();
		};
	}
}
